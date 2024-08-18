#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "rotors.h"
#include "keyboard.h"
#include "plugboard.h"
#include "lightbulbs.h"

#include <QMainWindow>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Rotors* rotors;
    Keyboard* keyboard;
    Plugboard* plugboard;
    LightBulbs* lightBulbs;
    QVBoxLayout *layout;

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
