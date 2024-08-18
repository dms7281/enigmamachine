#include "rotor.h"

#include <array>
#include <QDebug>
#include <random>
#include <boost/signals2.hpp>

void Rotor::keyboardInput(char key){
    Rotor::key = key;
    //qInfo() << Rotor::key << " in qt creator. straight up \"jorking it\". and by \"it\", haha, well. let's justr say. My pointerr";

    rotateRotor();
}

void Rotor::rotateRotor(){
    // qInfo() << Rotor::currentIndex;
    // qInfo() << currentIndex % 26;
    // qInfo() << wiring[currentIndex];

    currentIndex++;
    notchIndex++;

    qInfo() << "Rotor " << this << " wiring: " << wiring[currentIndex];

    if (currentIndex % 26 == 0) {
        currentIndex = 0;
        qInfo() << "Full rotor rotation";
    }

    if (notchIndex % 26 == 0) {
        node->next->currentIndex++;
        qInfo() << "Rotate next rotor";
    }
}


Rotor::Rotor(const int startingPoint, const int notchPoint, Node* nextRotor) : notchPoint(notchPoint) {
    std::array<char, 26> alphabet = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                                     'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

    std::random_device rd;
    std::mt19937 s(rd());

    std::shuffle(alphabet.begin(), alphabet.end(), s);

    Rotor::wiring = alphabet;
    Rotor::currentIndex = startingPoint;
    //qInfo() << "After init: " << currentIndex;

    notchIndex = Rotor::notchPoint + currentIndex;

    node = new Node(currentIndex);
    node->next = nextRotor;
    //node->notchIndex = notchIndex;
    qInfo() << "After init: " << currentIndex;
}

Rotor::Rotor(std::array<char, 26>& wiring, const int startingPoint, const int notchPoint) : notchPoint(notchPoint) {
    Rotor::wiring = wiring;
    Rotor::currentIndex = startingPoint;

    notchIndex = Rotor::notchPoint + currentIndex;

    node = new Node(notchIndex);
}
