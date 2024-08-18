#ifndef ROTORS_H
#define ROTORS_H

#include <QWidget>
#include <QFrame>
#include <QPushButton>
#include <QHBoxLayout>
#include <QComboBox>

inline QComboBox* createRotorSettingBox(){
    QComboBox* comboBox = new QComboBox();
    comboBox->addItems({"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"});
    return comboBox;
}

inline QFrame* createDividerLine(){
    QFrame* line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    return line;
}

struct Rotor {
    int position;
    int notchIndex;
    int ringSetting;
    std::string wiring;

    Rotor(int position, int notchIndex, int ringSetting, std::string wiring)
        : position(position), notchIndex(notchIndex), ringSetting(ringSetting), wiring(wiring) /*, next(nullptr)*/ {}
};

struct RotorConfiguration {
    std::string wiring;
    char notch;
};

static const int maxRotorCount = 5;
static const int maxReflectorCount = 5;

static const std::array<RotorConfiguration, maxRotorCount> wireConfigs = {{
    {"EKMFLGDQVZNTOWYHXUSPAIBRCJ", 'Q'},
    {"AJDKSIRUXBLHWTMCQGZNPYFVOE", 'E'},
    {"BDFHJLCPRTXVZNYEIWGAKMUSQO", 'V'},
    {"ESOVPZJAYQUIRHXLNFTGKDCMWB", 'J'},
    {"VZBRGITYUPSDNHLXAWMJQOFECK", 'Z'}
}};

static const std::array<std::string, maxReflectorCount> reflectorConfigs = {
    "LEYJVCNIXWPBQMDRTAKZGFUHOS",
    "FSOKANUERHMBTIYCWLQPZXVGJD",
    "EJMZALYXVBWFCRQUONTSPIKHGD",
    "YRUHQSLDPXNGOKMIEBFZCWVJAT",
    "FVPJIAOYEDRZXWGCTKUQSBNMHL"
};

class Rotors : public QWidget
{
    Q_OBJECT

public:
    explicit Rotors(QWidget *parent = nullptr);

private:
    Rotor* createNewRotor(int startPosition, char notch, int ringSetting, std::string wiring);
    void rotateRotor(Rotor* r);

    int rCount = 0;
    std::vector<Rotor*> forRotors;
    std::vector<Rotor*> revRotors;
    std::string reflector;

    QPushButton* addRotor;
    QComboBox* reflectorSetting;
    QWidget* rotorVWidget;
    QHBoxLayout* rotorLayout;

signals:
    void keyOutput(char c);
    void rotorsChanged();
    void rotorRotated(Rotor* r);

public slots:
    void encryptKey(char key);

private slots:
    void createRotorWidget();
    void updateReversedRotors();
};

#endif // ROTORS_H
