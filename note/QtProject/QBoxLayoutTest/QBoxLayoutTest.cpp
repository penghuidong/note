#include "QBoxLayoutTest.h"
#include<QHBoxLayout>



Widget::Widget(QWidget *parent) : QWidget(parent), btn1(this), btn2(this), btn3(this), btn4(this)
{
    btn1.setText("Button1");
    btn2.setText("Button2");
    btn3.setText("Button3");
    btn4.setText("Button4");

    btn1.setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    btn2.setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    btn3.setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    btn4.setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    //hLayout();
    //vLayout();

    nestLayout();
}


void Widget::hLayout()
{
    QHBoxLayout* hLay = new QHBoxLayout();

    hLay->addWidget(&btn1);
    hLay->addWidget(&btn2);
    hLay->addWidget(&btn3);
    hLay->addWidget(&btn4);

    hLay->setStretch(0, 1);
    hLay->setStretch(1, 2);
    hLay->setStretch(2, 3);
    hLay->setStretch(3, 4);


    setLayout(hLay);
}

void Widget::vLayout()
{
    QVBoxLayout* vLay = new QVBoxLayout();

    vLay->addWidget(&btn1);
    vLay->addWidget(&btn2);
    vLay->addWidget(&btn3);
    vLay->addWidget(&btn4);

    vLay->setStretch(0, 1);
    vLay->setStretch(1, 2);
    vLay->setStretch(2, 4);
    vLay->setStretch(3, 8);

    setLayout(vLay);

}

void Widget::nestLayout()
{
    QVBoxLayout* vlay1 = new QVBoxLayout();
    vlay1->addWidget(&btn1);
    vlay1->addWidget(&btn2);
    QVBoxLayout* vlay2 = new QVBoxLayout();
    vlay2->addWidget(&btn3);
    vlay2->addWidget(&btn4);
    QHBoxLayout* nestLay = new QHBoxLayout();
    nestLay->addLayout(vlay1);
    nestLay->addLayout(vlay2);

    nestLay->setStretchFactor(vlay1, 1);
    nestLay->setStretchFactor(vlay2, 2);

    setLayout(nestLay);
}

Widget::~Widget()
{

}
