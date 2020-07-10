#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>

class Widget : public QWidget{
  Q_OBJECT
private:
  QPushButton fontDialogBtn;
  QPushButton progressDialogBtn;
  QPushButton printDialogBtn;

private slots:
  void fontDialogBtnClicked();
  void progressDialogBtnClicked();
  void printDialogBtnClicked();

public:
  Widget(QWidget *parent = 0);
  ~Widget();
};

#endif // WIDGET_H
