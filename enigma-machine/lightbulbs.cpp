#include "lightbulbs.h"

#include <QLabel>
#include <QHBoxLayout>

LightBulbs::LightBulbs(QWidget *parent)
    : QWidget{parent}
{
    QHBoxLayout* textLayout = new QHBoxLayout(this);

    textLayout->addStretch(1);
    outputLabel = new QLabel();
    outputLabel->setStyleSheet("font: 24pt");
    textLayout->addWidget(outputLabel);
    textLayout->addStretch(1);
}

void LightBulbs::keyInput(char key){
    QString output = outputLabel->text() += key;
    outputLabel->setText(output);
    outputLabel->adjustSize();
}
