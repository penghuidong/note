#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>

class Widget : public QWidget{
  Q_OBJECT

private:
  QPushButton testBtn1;
  QPushButton testBtn2;
  QPushButton testBtn3;
  QPushButton testBtn4;

  void initControl();
  void testVBoxLayout();
  void testHBoxLayout();
  void testVHBoxLayout();

public:
  Widget(QWidget *parent = 0);
  ~Widget();
};

#endif // WIDGET_H
