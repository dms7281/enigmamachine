#include "plugboard.h"

auto getChar = [](QPushButton * button){
    if(button){
        return button->text().toStdString()[0];
    }
    return '\0';
};

void Plugboard::plugboardManager(){
    currSender = qobject_cast<QPushButton*>(sender());

    //prevSender = qobject_cast<QPushButton*>(sender());
    //qInfo() << currSender->text().toStdString()[0];
    //qInfo() << keyPress;
    if(!currSender) return;
    if(keyPress == getChar(currSender) && plugOpen) return;

    keyPress = getChar(currSender);

    if(plugboardMap.count(keyPress) == 1){
        plugboardMap[keyPress].first->setPalette(def);
        plugboardMap[keyPress].second->setPalette(def);

        qInfo() << getChar(plugboardMap[keyPress].first);
        qInfo() << getChar(plugboardMap[keyPress].second);

        char firstKey = getChar(plugboardMap[keyPress].first);
        char secondKey = getChar(plugboardMap[keyPress].second);

        plugboardMap.erase(firstKey);
        plugboardMap.erase(secondKey);

        qInfo() << "Removed Key " << keyPress;
        return;
    }


    if(!plugOpen){
        plugOpen = true;
        qInfo() << "Plug Open: " << keyPress;
        currSender->setPalette(open);
        prevSender = currSender;

        prevKey = keyPress;
    } else {
        plugOpen = false;
        qInfo() << "Plug Closed: " << keyPress;
        currSender->setPalette(closed);
        prevSender->setPalette(closed);

        //qInfo() << keyPress << " " << prevKey;
        plugboardMap.emplace(keyPress, std::make_pair(currSender, prevSender));
        plugboardMap.emplace(prevKey, std::make_pair(currSender, prevSender));

        //prevKey = keyPress;
    }

    for(const auto& entry : plugboardMap){
        qInfo() << "Key: " << entry.first << "Pair: " << getChar(entry.second.first) << " " << getChar(entry.second.second);
    }


    // To-Do: Make it so each open and close chars become a pair, either char in a pair cant be used for another pair at the same time,
    // these pairs are checked for each char the rotor passes

}

void Plugboard::keyInput(char key){
    emit keyOutput(plugboard(key));
}

void Plugboard::rotorInput(char key){
    emit rotorOutput(plugboard(key));
}

char Plugboard::plugboard(char key){
    if(plugboardMap.count(key) == 1){
        qInfo() << "Plugboard Active";
        key = getChar(key != getChar(plugboardMap[key].first) ? plugboardMap[key].first : plugboardMap[key].second);
    }

    return key;
    // output += key;
    // qInfo() << output;
}

Plugboard::Plugboard(QWidget *parent)
    : QWidget{parent}
{
    plugOpen = false;

    q_plug = new QPushButton("Q");
    w_plug = new QPushButton("W");
    e_plug = new QPushButton("E");
    r_plug = new QPushButton("R");
    t_plug = new QPushButton("T");
    z_plug = new QPushButton("Z");
    u_plug = new QPushButton("U");
    i_plug = new QPushButton("I");
    o_plug = new QPushButton("O");
    a_plug = new QPushButton("A");
    s_plug = new QPushButton("S");
    d_plug = new QPushButton("D");
    f_plug = new QPushButton("F");
    g_plug = new QPushButton("G");
    h_plug = new QPushButton("H");
    j_plug = new QPushButton("J");
    k_plug = new QPushButton("K");
    p_plug = new QPushButton("P");
    y_plug = new QPushButton("Y");
    x_plug = new QPushButton("X");
    c_plug = new QPushButton("C");
    v_plug = new QPushButton("V");
    b_plug = new QPushButton("B");
    n_plug = new QPushButton("N");
    m_plug = new QPushButton("M");
    l_plug = new QPushButton("L");

    l1 = new QHBoxLayout();
    l2 = new QHBoxLayout();
    l3 = new QHBoxLayout();

    l1->addWidget(q_plug);
    l1->addWidget(w_plug);
    l1->addWidget(e_plug);
    l1->addWidget(r_plug);
    l1->addWidget(t_plug);
    l1->addWidget(z_plug);
    l1->addWidget(u_plug);
    l1->addWidget(i_plug);
    l1->addWidget(o_plug);

    l2->addWidget(a_plug);
    l2->addWidget(s_plug);
    l2->addWidget(d_plug);
    l2->addWidget(f_plug);
    l2->addWidget(g_plug);
    l2->addWidget(h_plug);
    l2->addWidget(j_plug);
    l2->addWidget(k_plug);

    l3->addWidget(p_plug);
    l3->addWidget(y_plug);
    l3->addWidget(x_plug);
    l3->addWidget(c_plug);
    l3->addWidget(v_plug);
    l3->addWidget(b_plug);
    l3->addWidget(n_plug);
    l3->addWidget(m_plug);
    l3->addWidget(l_plug);

    mainLayout = new QVBoxLayout(this);

    mainLayout->addLayout(l1);
    mainLayout->addLayout(l2);
    mainLayout->addLayout(l3);

    open.setColor(QPalette::Button, QColor(Qt::red));
    closed.setColor(QPalette::Button, QColor(Qt::green));
    def = q_plug->palette();

    connect(q_plug, &QPushButton::clicked, this, &Plugboard::plugboardManager);
    connect(w_plug, &QPushButton::clicked, this, &Plugboard::plugboardManager);
    connect(e_plug, &QPushButton::clicked, this, &Plugboard::plugboardManager);
    connect(r_plug, &QPushButton::clicked, this, &Plugboard::plugboardManager);
    connect(t_plug, &QPushButton::clicked, this, &Plugboard::plugboardManager);
    connect(z_plug, &QPushButton::clicked, this, &Plugboard::plugboardManager);
    connect(u_plug, &QPushButton::clicked, this, &Plugboard::plugboardManager);
    connect(i_plug, &QPushButton::clicked, this, &Plugboard::plugboardManager);
    connect(o_plug, &QPushButton::clicked, this, &Plugboard::plugboardManager);

    connect(a_plug, &QPushButton::clicked, this, &Plugboard::plugboardManager);
    connect(s_plug, &QPushButton::clicked, this, &Plugboard::plugboardManager);
    connect(d_plug, &QPushButton::clicked, this, &Plugboard::plugboardManager);
    connect(f_plug, &QPushButton::clicked, this, &Plugboard::plugboardManager);
    connect(g_plug, &QPushButton::clicked, this, &Plugboard::plugboardManager);
    connect(h_plug, &QPushButton::clicked, this, &Plugboard::plugboardManager);
    connect(j_plug, &QPushButton::clicked, this, &Plugboard::plugboardManager);
    connect(k_plug, &QPushButton::clicked, this, &Plugboard::plugboardManager);

    connect(p_plug, &QPushButton::clicked, this, &Plugboard::plugboardManager);
    connect(y_plug, &QPushButton::clicked, this, &Plugboard::plugboardManager);
    connect(x_plug, &QPushButton::clicked, this, &Plugboard::plugboardManager);
    connect(c_plug, &QPushButton::clicked, this, &Plugboard::plugboardManager);
    connect(v_plug, &QPushButton::clicked, this, &Plugboard::plugboardManager);
    connect(b_plug, &QPushButton::clicked, this, &Plugboard::plugboardManager);
    connect(n_plug, &QPushButton::clicked, this, &Plugboard::plugboardManager);
    connect(m_plug, &QPushButton::clicked, this, &Plugboard::plugboardManager);
    connect(l_plug, &QPushButton::clicked, this, &Plugboard::plugboardManager);

}
