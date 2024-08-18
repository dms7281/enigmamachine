#ifndef PLUGBOARD_H
#define PLUGBOARD_H

#include <QPushButton>
#include <QWidget>
#include <QHBoxLayout>
#include <bits/stdc++.h>

class Plugboard : public QWidget
{
    Q_OBJECT
public:
    explicit Plugboard(QWidget *parent = nullptr);



private:
    //enum States {Open_Plug, Waiting};
    char plugboard(char key);

    std::string output;

    char keyPress;
    bool plugOpen;

    std::unordered_map<char, std::pair<QPushButton*, QPushButton*>> plugboardMap;


    char currKey;
    char prevKey;
    QPushButton* currSender;
    QPushButton* prevSender;

    QHBoxLayout* l1;
    QPushButton* q_plug;
    QPushButton* w_plug;
    QPushButton* e_plug;
    QPushButton* r_plug;
    QPushButton* t_plug;
    QPushButton* z_plug;
    QPushButton* u_plug;
    QPushButton* i_plug;
    QPushButton* o_plug;

    QHBoxLayout* l2;
    QPushButton* a_plug;
    QPushButton* s_plug;
    QPushButton* d_plug;
    QPushButton* f_plug;
    QPushButton* g_plug;
    QPushButton* h_plug;
    QPushButton* j_plug;
    QPushButton* k_plug;

    QHBoxLayout* l3;
    QPushButton* p_plug;
    QPushButton* y_plug;
    QPushButton* x_plug;
    QPushButton* c_plug;
    QPushButton* v_plug;
    QPushButton* b_plug;
    QPushButton* n_plug;
    QPushButton* m_plug;
    QPushButton* l_plug;

    QVBoxLayout* mainLayout;

    QPalette open;
    QPalette closed;
    QPalette def;

signals:
    void keyOutput(char key);
    void rotorOutput(char key);

public slots:
    void keyInput(char key);
    void rotorInput(char key);

private slots:
    void plugboardManager();
};

#endif // PLUGBOARD_H
