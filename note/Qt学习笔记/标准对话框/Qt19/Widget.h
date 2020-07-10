#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>

class Widget : public QWidget{
  Q_OBJECT
private:
  QPushButton simgleMsgBtn;
  QPushButton customMsgBtn;
  QPushButton openFileBtn;
  QPushButton saveFileBtn;

private slots:
  void simpleMsgBtnClicked();

  void customMsgBtnClicked();

  void openFileBtnClicked();

  void saveFileBtnClicked();

public:
  Widget(QWidget *parent = 0);
  ~Widget();
};

#endif // WIDGET_H
