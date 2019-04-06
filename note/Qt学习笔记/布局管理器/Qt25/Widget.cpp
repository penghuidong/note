#include "Widget.h"
#include <QStackedLayout>
#include <QHBoxLayout>
#include <QtCore>
#include <QDebug>

Widget::Widget(QWidget *parent) : QWidget(parent),
    testBtn1(this), testBtn2(this), testBtn3(this), testBtn4(this)
{
  initControl();
}

void Widget::initControl()
{
  QStackedLayout* slayout = new QStackedLayout;
  QHBoxLayout* hlayout = new QHBoxLayout;
  QWidget* widget = new QWidget;
  QTimer* timer = new QTimer(this);

  testBtn1.setText("1st button");
  testBtn2.setText("2rd button");
  testBtn3.setText("3th button");
  testBtn4.setText("4th button");

  hlayout->addWidget(&testBtn2);
  hlayout->addWidget(&testBtn3);
  widget->setLayout(hlayout);

  slayout->addWidget(&testBtn1);
  slayout->addWidget(widget);
  slayout->addWidget(&testBtn4);

  setLayout(slayout);

  connect(timer, SIGNAL(timeout()), this, SLOT(timerTimeout()));

  timer->start(2000);
}

void Widget::timerTimeout()
{
  QStackedLayout* slayout = dynamic_cast<QStackedLayout*>(layout());
  if(slayout!=nullptr){
    int index = (slayout->currentIndex() + 1) % slayout->count();
    slayout->setCurrentIndex(index);
  }
}

Widget::~Widget()
{

}
