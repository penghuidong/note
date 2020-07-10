#include <QApplication>
#include "Calculator.h"
#include <QDebug>

int main(int argc, char** argv){
  QApplication a(argc, argv);
  Calculator* cal = Calculator::newInstance();
  int ret = -1;
  if(cal!=nullptr){
    cal->show();
    ret = a.exec();
    delete cal;
  }
  return ret;
}
