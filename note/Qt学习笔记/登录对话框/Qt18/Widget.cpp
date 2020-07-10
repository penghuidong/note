#include "Widget.h"
#include "LoginDialog.h"
#include <QDebug>

Widget::Widget(QWidget *parent)
  : QWidget(parent), testBtn(this)
{
  testBtn.setText("test login dialog");
  setFixedSize(200, 50);
  connect(&testBtn, SIGNAL(clicked()), this, SLOT(testBtnClicked()));
}

void Widget::testBtnClicked()
{
  LoginDialog dlg;
  if(dlg.exec()==QDialog::Accepted){
    qDebug() << "user: " + dlg.getUser();
    qDebug() << "pwd: " + dlg.getPwd();
  }
}

Widget::~Widget(){}
