#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QStackedLayout>


class Widget : public QWidget{
  Q_OBJECT
private:
  QPushButton preBtn;
  QPushButton nextBtn;
  QLabel flab1;
  QLabel flab2;
  QLabel flab3;
  QLabel flab4;
  QLineEdit slineEdit;
  QPushButton tpushbutton1;
  QPushButton tpushbutton2;
  QStackedLayout slayout;

  void initControl();
  QWidget* get1stPage();
  QWidget* get2ndPage();
  QWidget* get3rnPage();
private slots:
  void onPreBtnClicked();
  void onNextBtnClicked();

public:
  Widget(QWidget *parent = 0);
  ~Widget();
};

#endif // WIDGET_H
