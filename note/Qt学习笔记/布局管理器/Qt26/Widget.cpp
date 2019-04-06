#include "Widget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFormLayout>
#include <QDebug>

QWidget* Widget::get1stPage()
{
  QWidget* ret = new QWidget;
  QGridLayout* layout = new QGridLayout;
  flab1.setText("this");
  flab2.setText("is");
  flab3.setText("1st");
  flab4.setText("page");
  layout->addWidget(&flab1, 0, 0);
  layout->addWidget(&flab2, 0, 1);
  layout->addWidget(&flab3, 1, 0);
  layout->addWidget(&flab4, 1, 1);
  ret->setLayout(layout);
  return ret;
}

QWidget* Widget::get2ndPage()
{
  QWidget* ret =  new QWidget;
  QFormLayout* layout = new QFormLayout;
  slineEdit.setText("this is 2rd page");
  layout->addRow("hint", &slineEdit);
  ret->setLayout(layout);
  return ret;
}

QWidget* Widget::get3rnPage()
{
  QWidget* ret = new QWidget;
  QVBoxLayout* layout = new QVBoxLayout;
  tpushbutton1.setText("this is ");
  tpushbutton2.setText("3rd page");
  layout->addWidget(&tpushbutton1);
  layout->addWidget(&tpushbutton2);
  ret->setLayout(layout);
  return ret;
}

void Widget::initControl()
{
  QVBoxLayout* vlayout = new QVBoxLayout;
  QHBoxLayout* hlayout = new QHBoxLayout;
  preBtn.setText("pre page");
  preBtn.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  preBtn.setMinimumSize(160, 30);
  nextBtn.setText("next page");
  nextBtn.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  nextBtn.setMinimumSize(160, 30);

  connect(&preBtn, SIGNAL(clicked()), this, SLOT(onPreBtnClicked()));
  connect(&nextBtn, SIGNAL(clicked()), this, SLOT(onNextBtnClicked()));

  hlayout->addWidget(&preBtn);
  hlayout->addWidget(&nextBtn);
  slayout.addWidget(get1stPage());
  slayout.addWidget(get2ndPage());
  slayout.addWidget(get3rnPage());

  vlayout->addLayout(&slayout);
  vlayout->addLayout(hlayout);

  setLayout(vlayout);
}


Widget::Widget(QWidget *parent)
  : QWidget(parent)
{
  initControl();
}

void Widget::onPreBtnClicked()
{
  int index = ((slayout.currentIndex()-1) + 3) % 3;
  slayout.setCurrentIndex(index);
}
void Widget::onNextBtnClicked()
{
  int index = ((slayout.currentIndex()+1)) % 3;
  slayout.setCurrentIndex(index);
}

Widget::~Widget(){}
