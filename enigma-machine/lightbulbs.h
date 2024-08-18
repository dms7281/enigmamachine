#ifndef LIGHTBULBS_H
#define LIGHTBULBS_H

#include <QWidget>
#include <QLabel>

class LightBulbs : public QWidget
{
    Q_OBJECT
public:
    explicit LightBulbs(QWidget *parent = nullptr);

private:
    QChar* key;
    QLabel* outputLabel;

signals:

public slots:
    void keyInput(char key);
};

#endif // LIGHTBULBS_H
