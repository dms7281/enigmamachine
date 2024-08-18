#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>


class Keyboard : public QWidget{

    Q_OBJECT

public:
    Keyboard(QWidget *parent = nullptr);

private:
    QHBoxLayout* l1;
    QPushButton* q_key;
    QPushButton* w_key;
    QPushButton* e_key;
    QPushButton* r_key;
    QPushButton* t_key;
    QPushButton* z_key;
    QPushButton* u_key;
    QPushButton* i_key;
    QPushButton* o_key;

    QHBoxLayout* l2;
    QPushButton* a_key;
    QPushButton* s_key;
    QPushButton* d_key;
    QPushButton* f_key;
    QPushButton* g_key;
    QPushButton* h_key;
    QPushButton* j_key;
    QPushButton* k_key;

    QHBoxLayout* l3;
    QPushButton* p_key;
    QPushButton* y_key;
    QPushButton* x_key;
    QPushButton* c_key;
    QPushButton* v_key;
    QPushButton* b_key;
    QPushButton* n_key;
    QPushButton* m_key;
    QPushButton* l_key;

    QVBoxLayout* mainLayout;


public slots:
    void keyPressed();

signals:
    void keyOutput(char keyPress);


private:
};

#endif // KEYBOARD_H
