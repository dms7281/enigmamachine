#include "mainwindow.h"
//#include "rotor.h"
#include "rotors.h"

#include <QObject>
#include <QApplication>
#include <boost/signals2.hpp>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QObject::connect(w.keyboard, &Keyboard::keyOutput, w.plugboard, &Plugboard::keyInput);
    QObject::connect(w.plugboard, &Plugboard::keyOutput, w.rotors, &Rotors::encryptKey);
    QObject::connect(w.rotors, &Rotors::keyOutput, w.plugboard, &Plugboard::rotorInput);
    QObject::connect(w.plugboard, &Plugboard::rotorOutput, w.lightBulbs, &LightBulbs::keyInput);


    return a.exec();
}
