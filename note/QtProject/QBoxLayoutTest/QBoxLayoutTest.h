#ifndef WIDGET_H
#define WIDGET_H

#include <QPushButton>
#include <QWidget>


class Widget : public QWidget
{
    Q_OBJECT
private:
    QPushButton btn1;
    QPushButton btn2;
    QPushButton btn3;
    QPushButton btn4;

    void hLayout();
    void vLayout();
    void nestLayout();
public:
    Widget(QWidget* parent = 0);
    ~Widget();

};

#endif
