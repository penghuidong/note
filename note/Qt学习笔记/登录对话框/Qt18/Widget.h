#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>

class Widget : public QWidget{
  Q_OBJECT
private:
  QPushButton testBtn;

private slots:
  void testBtnClicked();
public:
  Widget(QWidget *parent = 0);
  ~Widget();
};

#endif // WIDGET_H
