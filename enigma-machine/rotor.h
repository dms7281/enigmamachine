#ifndef ROTOR_H
#define ROTOR_H

#include <array>

struct Node {
    int currentIndex;
    char keyPress;
    Node* next;

    Node(int value) : currentIndex(value), next(nullptr) {}
};

class Rotor
{
public:
    Rotor(const int startingPoint, const int notchPoint, Node* nextRotor);
    Rotor(std::array<char, 26>& wiring, const int startingPoint, const int notchPoint);

    void keyboardInput(char key);

    Node* node;

private:
    char key;
    std::array<char, 26> wiring;
    const int notchPoint;
    int currentIndex;
    int notchIndex;

    void rotateRotor(); // Contains the logic to shift the current index and keep track of the notch location
};

#endif // ROTOR_H
