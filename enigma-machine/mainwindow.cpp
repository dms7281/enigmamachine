#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "keyboard.h"
#include "plugboard.h"

#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    layout = new QVBoxLayout(centralWidget);

    rotors = new Rotors();
    keyboard = new Keyboard();
    plugboard = new Plugboard();
    lightBulbs = new LightBulbs();


    // QPalette pal = QPalette();
    // pal.setColor(QPalette::Window, Qt::darkBlue);
    //rotors->setPalette(pal);

    layout->addWidget(rotors);
    rotors->setAutoFillBackground(true);
    layout->addWidget(lightBulbs);
    layout->addWidget(keyboard);
    layout->addWidget(plugboard);

    centralWidget->setLayout(layout);
}

MainWindow::~MainWindow()
{
    delete ui;
}
