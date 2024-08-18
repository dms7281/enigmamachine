#include "keyboard.h"

#include <QPushButton>
#include <QObject>
#include <QVBoxLayout>

void Keyboard::keyPressed(){
    QPushButton* key_press = qobject_cast<QPushButton*>(sender());
    if(key_press) {
        emit keyOutput(key_press->text().toStdString()[0]);
    }
}


Keyboard::Keyboard(QWidget *parent) : QWidget(parent) {
    q_key = new QPushButton("Q");
    w_key = new QPushButton("W");
    e_key = new QPushButton("E");
    r_key = new QPushButton("R");
    t_key = new QPushButton("T");
    z_key = new QPushButton("Z");
    u_key = new QPushButton("U");
    i_key = new QPushButton("I");
    o_key = new QPushButton("O");
    a_key = new QPushButton("A");
    s_key = new QPushButton("S");
    d_key = new QPushButton("D");
    f_key = new QPushButton("F");
    g_key = new QPushButton("G");
    h_key = new QPushButton("H");
    j_key = new QPushButton("J");
    k_key = new QPushButton("K");
    p_key = new QPushButton("P");
    y_key = new QPushButton("Y");
    x_key = new QPushButton("X");
    c_key = new QPushButton("C");
    v_key = new QPushButton("V");
    b_key = new QPushButton("B");
    n_key = new QPushButton("N");
    m_key = new QPushButton("M");
    l_key = new QPushButton("L");

    l1 = new QHBoxLayout();
    l2 = new QHBoxLayout();
    l3 = new QHBoxLayout();

    l1->addWidget(q_key);
    l1->addWidget(w_key);
    l1->addWidget(e_key);
    l1->addWidget(r_key);
    l1->addWidget(t_key);
    l1->addWidget(z_key);
    l1->addWidget(u_key);
    l1->addWidget(i_key);
    l1->addWidget(o_key);

    l2->addWidget(a_key);
    l2->addWidget(s_key);
    l2->addWidget(d_key);
    l2->addWidget(f_key);
    l2->addWidget(g_key);
    l2->addWidget(h_key);
    l2->addWidget(j_key);
    l2->addWidget(k_key);

    l3->addWidget(p_key);
    l3->addWidget(y_key);
    l3->addWidget(x_key);
    l3->addWidget(c_key);
    l3->addWidget(v_key);
    l3->addWidget(b_key);
    l3->addWidget(n_key);
    l3->addWidget(m_key);
    l3->addWidget(l_key);

    mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(l1);
    mainLayout->addLayout(l2);
    mainLayout->addLayout(l3);

    connect(q_key, &QPushButton::clicked, this, &Keyboard::keyPressed);
    connect(w_key, &QPushButton::clicked, this, &Keyboard::keyPressed);
    connect(e_key, &QPushButton::clicked, this, &Keyboard::keyPressed);
    connect(r_key, &QPushButton::clicked, this, &Keyboard::keyPressed);
    connect(t_key, &QPushButton::clicked, this, &Keyboard::keyPressed);
    connect(z_key, &QPushButton::clicked, this, &Keyboard::keyPressed);
    connect(u_key, &QPushButton::clicked, this, &Keyboard::keyPressed);
    connect(i_key, &QPushButton::clicked, this, &Keyboard::keyPressed);
    connect(o_key, &QPushButton::clicked, this, &Keyboard::keyPressed);

    connect(a_key, &QPushButton::clicked, this, &Keyboard::keyPressed);
    connect(s_key, &QPushButton::clicked, this, &Keyboard::keyPressed);
    connect(d_key, &QPushButton::clicked, this, &Keyboard::keyPressed);
    connect(f_key, &QPushButton::clicked, this, &Keyboard::keyPressed);
    connect(g_key, &QPushButton::clicked, this, &Keyboard::keyPressed);
    connect(h_key, &QPushButton::clicked, this, &Keyboard::keyPressed);
    connect(j_key, &QPushButton::clicked, this, &Keyboard::keyPressed);
    connect(k_key, &QPushButton::clicked, this, &Keyboard::keyPressed);

    connect(p_key, &QPushButton::clicked, this, &Keyboard::keyPressed);
    connect(y_key, &QPushButton::clicked, this, &Keyboard::keyPressed);
    connect(x_key, &QPushButton::clicked, this, &Keyboard::keyPressed);
    connect(c_key, &QPushButton::clicked, this, &Keyboard::keyPressed);
    connect(v_key, &QPushButton::clicked, this, &Keyboard::keyPressed);
    connect(b_key, &QPushButton::clicked, this, &Keyboard::keyPressed);
    connect(n_key, &QPushButton::clicked, this, &Keyboard::keyPressed);
    connect(m_key, &QPushButton::clicked, this, &Keyboard::keyPressed);
    connect(l_key, &QPushButton::clicked, this, &Keyboard::keyPressed);
}
