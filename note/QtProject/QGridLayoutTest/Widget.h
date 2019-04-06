#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>

class Widget : public QWidget
{
    Q_OBJECT
private:
    QPushButton btn1;
    QPushButton btn2;
    QPushButton btn3;
    QPushButton btn4;

    void layout1();
    void layout2();
public:
    Widget(QWidget* parent = 0);
    ~Widget();
};

#endif // WIDGET_H
