#include "Widget.h"
#include <QGridLayout>

Widget::Widget(QWidget *parent)
    : QWidget(parent), btn1(this), btn2(this), btn3(this), btn4(this)
{
    btn1.setText("Button1");
    btn2.setText("Button2");
    btn3.setText("Button3");
    btn4.setText("Button4");

    btn1.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    btn2.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    btn3.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    btn4.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

   // layout1();
    layout2();

}


void Widget::layout1()
{
    QGridLayout* lay1 = new QGridLayout();

    lay1->addWidget(&btn1, 0, 0);
    lay1->addWidget(&btn2, 0, 1);
    lay1->addWidget(&btn3, 1, 0);
    lay1->addWidget(&btn4, 1, 1);


    lay1->setColumnStretch(0, 1);
    lay1->setColumnStretch(1, 2);
    lay1->setRowStretch(0, 1);
    lay1->setRowStretch(1, 2);

    setLayout(lay1);

}

void Widget::layout2()
{
    QGridLayout* lay2 = new QGridLayout();

    lay2->addWidget(&btn1, 0, 0, 2, 1);
    lay2->addWidget(&btn2, 0, 1, 2, 1);
    lay2->addWidget(&btn3, 2, 0, 1, 2);
    lay2->addWidget(&btn4, 3, 0, 1, 2);

    setLayout(lay2);
}



Widget::~Widget()
{

}
