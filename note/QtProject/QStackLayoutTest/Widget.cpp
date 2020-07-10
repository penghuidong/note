#include "Widget.h"
#include <QStackedLayout>
#include <QHBoxLayout>
#include <QtCore>

Widget::Widget(QWidget *parent)
    : QWidget(parent), btn1(this), btn2(this), btn3(this), btn4(this)
{
    initControl();
}

void Widget::initControl()
{
    QStackedLayout* stlayout = new QStackedLayout();
    QHBoxLayout* hlayout = new QHBoxLayout();
    QWidget* widget = new QWidget();
    QTimer* timer = new QTimer();

    btn1.setText("Button 1");
    btn2.setText("Button 2");
    btn3.setText("Button 3");
    btn4.setText("Button 4");

    btn2.setParent(widget);
    btn3.setParent(widget);

    hlayout->addWidget(&btn2);
    hlayout->addWidget(&btn3);

    widget->setLayout(hlayout);

    stlayout->addWidget(&btn1);
    stlayout->addWidget(widget);
    stlayout->addWidget(&btn4);

    stlayout->setCurrentIndex(0);

    setLayout(stlayout);

    connect(timer, SIGNAL(timeout()), this, SLOT(timerTimeout()) );
    timer->start(2000);
}


void Widget::timerTimeout()
{
    QStackedLayout* slayout = dynamic_cast<QStackedLayout*>(layout());

    if(slayout!=NULL)
    {
        int index = (slayout->currentIndex() + 1) % slayout->count();
        slayout->setCurrentIndex(index);
    }
}

Widget::~Widget()
{

}
