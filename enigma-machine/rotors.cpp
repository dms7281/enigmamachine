 #include "rotors.h"

#include <QDebug>
#include <QWidget>
#include <QLabel>
#include <QComboBox>

// Constructor, initialize layout and add button, connect add button to creating a new rotor, connect rotors changing signal to updating reverse rotors vector
Rotors::Rotors(QWidget *parent) : QWidget(parent){
    addRotor = new QPushButton("+");
    reflectorSetting = new QComboBox();
    reflectorSetting->addItems({"Beta", "Gamma", "Reflector A", "Reflector B", "Reflector C"});
    rotorLayout = new QHBoxLayout(this);
    rotorLayout->addWidget(reflectorSetting);
    rotorLayout->addWidget(addRotor);
    rotorLayout->addStretch(1);

    connect(addRotor, &QPushButton::clicked, this, &Rotors::createRotorWidget);

    connect(this, &Rotors::rotorsChanged, this, &Rotors::updateReversedRotors);

    connect(reflectorSetting, &QComboBox::currentIndexChanged, this, [this]() {
        Rotors::reflector = reflectorConfigs[reflectorSetting->currentIndex()];
    });

    // Default reflector is UKW-B
    Rotors::reflector = "YRUHQSLDPXNGOKMIEBFZCWVJAT";
}
// Create a new rotor and push it into forRotor vector
Rotor* Rotors::createNewRotor(int startPosition, char notch, int ringSetting, std::string wiring){
    forRotors.push_back(new Rotor(startPosition, int(notch)-65+1, ringSetting, wiring));
    emit rotorsChanged();
    //qInfo() << "Creating rotor. Starting Position:" << forRotors.back()->position << "Notch Index:" << forRotors.back()->notchIndex << "Wiring:" << forRotors.back()->wiring;
    return forRotors.back();
}
// Rotate rotor position and if rotor equals notch position, recursivly rotate next rotor
void Rotors::rotateRotor(Rotor* r){
    if (r == nullptr) return;

    r->position++;

    if(r->position % 26 == 0){
        r->position = 0;
    }

    //qInfo() << "Rotor Rotated:" << r->wiring << "Position:" << r->position;
    emit rotorRotated(r);

    // If at notch position, rotate the next rotor
    //int notch = (r->notchIndex + r->ringSetting) % 26;
    if (r->position == r->notchIndex) {
        //qInfo() << "Notch hit, rotate next";
        rotateRotor(forRotors[std::find(forRotors.begin(), forRotors.end(), r) - forRotors.begin() + 1]);
    }
}
// Encrypt inputed charIndex (0-26, represents letter in alphabet)
void Rotors::encryptKey(char key){
    int charIndex = key - 65;
    if(rCount == 0){
        charIndex = reflector[charIndex] - 65;
        emit keyOutput(char(charIndex + 65));
        return;
    }
    // Check if any rotors (that aren't front or back) are eligible to double step
    for(int i = 1; i < forRotors.size()-1; i++){
        //int notch = (forRotors[i]->notchIndex + forRotors[i]->ringSetting) % 26;
        if(forRotors[i]->position == forRotors[i]->notchIndex ){
            //qInfo() << "Double Step";
            rotateRotor(forRotors[i]);
        }
    }

    // Rotate first rotor (will recursively rotate i+1 rotors if notch and position are equal)
    rotateRotor(forRotors.front());

    for(Rotor* r : forRotors){
        int offsetPos = (r->position - r->ringSetting + 26) % 26;
        charIndex = (r->wiring[(charIndex + offsetPos) % 26] - 65);
        charIndex = ((charIndex - offsetPos + 26) % 26);
        //qInfo() << char(charIndex + 65);
    }

    charIndex = reflector[charIndex] - 65;
    //qInfo() << char(charIndex + 65);

    for(Rotor* r : revRotors){
        int offsetPos = (r->position - r->ringSetting + 26) % 26;
        charIndex = ((charIndex + offsetPos) % 26);
        int charPos = std::find(r->wiring.begin(), r->wiring.end(), char(charIndex + 65)) - r->wiring.begin();
        charIndex = (charPos - offsetPos + 26) % 26;
        //qInfo() << char(charIndex + 65);
    }

    emit keyOutput(char(charIndex + 65));
}
// Create widget to represent rotor and to manipulate created rotor
void Rotors::createRotorWidget(){
    if(rCount == maxRotorCount) return; // If the current number of widgets is equal to the max number of rotors allowed (5 rotors)
    rCount++;

    // Initialize a new rotor with default values and add it to forRotors
    Rotor* rotor = createNewRotor(0, wireConfigs[0].notch, 0, wireConfigs[0].wiring); // Returns index of rotor, will be stored to initialize forRotor[i] widget

    // Sets up the rotor widget

    QWidget* newRotorWidget = new QWidget();
    QVBoxLayout* newRotorLayout = new QVBoxLayout();
    newRotorWidget->setLayout(newRotorLayout);

    QComboBox* typeSetting = new QComboBox();
    typeSetting->addItems({"I", "II", "III", "IV", "V"});
    newRotorLayout->addWidget(typeSetting);

    newRotorLayout->addWidget(new QLabel(QString::fromStdString("Ring Setting")));
    QComboBox* ringSetting = createRotorSettingBox(); // Creates combo box containing the alphabet
    newRotorLayout->addWidget(ringSetting);

    newRotorLayout->addWidget(createDividerLine());

    QLabel* nextIndex = new QLabel(QChar('B'));
    nextIndex->setAlignment(Qt::AlignHCenter);
    newRotorLayout->addWidget(nextIndex);

    QComboBox* startSetting = createRotorSettingBox();
    newRotorLayout->addWidget(startSetting);

    QLabel* prevIndex = new QLabel(QChar('Z'));
    prevIndex->setAlignment(Qt::AlignHCenter);
    newRotorLayout->addWidget(prevIndex);

    newRotorLayout->addWidget(createDividerLine());

    QPushButton* delRWidgetButton = new QPushButton("-");
    newRotorLayout->addWidget(delRWidgetButton);

    rotorLayout->removeItem(rotorLayout->itemAt(rotorLayout->count() - 1));
    rotorLayout->removeItem(rotorLayout->itemAt(0));
    rotorLayout->removeWidget(addRotor);
    rotorLayout->insertWidget(0, reflectorSetting);
    rotorLayout->insertWidget(1, newRotorWidget);
    rotorLayout->addWidget(addRotor);
    rotorLayout->addStretch(1);

    // If widget delete button is clicked, delete entire widget and delete rotor in forRotors
    connect(delRWidgetButton, &QPushButton::clicked, this, [this, rotor, newRotorWidget]() {
        forRotors.erase(std::remove(forRotors.begin(), forRotors.end(), rotor), forRotors.end());
        rCount--;
        delete newRotorWidget;
        emit rotorsChanged();
    });

    // If a new value is selected in rotor type cbox, change the matching rotor to the selected type
    connect(typeSetting, &QComboBox::currentIndexChanged, [rotor, typeSetting]() {
        int i = typeSetting->currentIndex();
        if(i > wireConfigs.size()-1) return;
        rotor->wiring = wireConfigs[i].wiring;
        rotor->notchIndex = int(wireConfigs[i].notch)-65+1;
        //qInfo() << "Rotor" << i << "Wiring:" << rotor->wiring << "Notch Point:" << rotor->notchIndex;
    });

    // If a new value is selected in start position cbox, change the matching rotor start position to the selected letter
    connect(startSetting, &QComboBox::currentIndexChanged, this, [rotor, startSetting, prevIndex, nextIndex]() {
        rotor->position = startSetting->currentIndex();
        nextIndex->setText(QChar((rotor->position + 1) % 26 + 65));
        prevIndex->setText(QChar((rotor->position + 25) % 26 + 65));
    });

    // If a new value is selected in ring setting cbox, change the matching rotor ring setting to the selected letter
    connect(ringSetting, &QComboBox::currentIndexChanged, [rotor, ringSetting]() {
        rotor->ringSetting = ringSetting->currentIndex();
    });

    // If a rotor is rotated, update the selected index of the start setting cbox
    // Doing this will also trigger the changeRotorStart slot
    connect(this, &Rotors::rotorRotated, this, [this, rotor, startSetting](Rotor* r) {
        if(rotor != r) return;
        startSetting->setCurrentIndex(r->position);
    });
}
// When rotors are changed (added or deleted) update the reverse rotor vector
void Rotors::updateReversedRotors(){
    revRotors = forRotors;
    std::reverse(revRotors.begin(), revRotors.end());
}
