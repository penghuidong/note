#include "Widget.h"
#include <QColorDialog>
#include <QInputDialog>
#include <QDebug>

Widget::Widget(QWidget *parent)
  : QWidget(parent), colorDialogBtn(this), inputDialogBtn(this)
{
  colorDialogBtn.setText("color dialog");
  colorDialogBtn.move(20, 20);
  colorDialogBtn.resize(160, 30);

  inputDialogBtn.setText("input dialog");
  inputDialogBtn.move(20, 70);
  inputDialogBtn.resize(160, 30);

  resize(200, 120);
  setFixedSize(200, 120);
  connect(&colorDialogBtn, SIGNAL(clicked()), this, SLOT(colorDialogBtnClicked()));
  connect(&inputDialogBtn, SIGNAL(clicked()), this, SLOT(inputDialogBtnClicked()));
}

void Widget::colorDialogBtnClicked(){
  QColorDialog dlg(this);

  dlg.setWindowTitle("color editor");
  dlg.setCurrentColor(QColor(100, 111,222));
  if(dlg.exec()==QColorDialog::Accepted){
    QColor color = dlg.selectedColor();
    qDebug() << color;
    qDebug() << color.red();
    qDebug() << color.green();
    qDebug() << color.blue();
    qDebug() << color.hue();
    qDebug() << color.saturation();
    qDebug() << color.value();
  }
}

void Widget::inputDialogBtnClicked(){
  QInputDialog dlg(this);
  dlg.setWindowTitle("input test");
  dlg.setLabelText("pelase input an integer:");
  dlg.setInputMode(QInputDialog::IntInput);
  if(dlg.exec()==QInputDialog::Accepted){
    qDebug() << dlg.intValue();
  }
}


Widget::~Widget(){}
