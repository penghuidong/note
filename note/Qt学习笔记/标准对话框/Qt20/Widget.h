#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>

class Widget : public QWidget{
  Q_OBJECT
private:
  QPushButton colorDialogBtn;
  QPushButton inputDialogBtn;

private slots:
  void colorDialogBtnClicked();
  void inputDialogBtnClicked();

public:
  Widget(QWidget *parent = 0);
  ~Widget();
};

#endif // WIDGET_H
