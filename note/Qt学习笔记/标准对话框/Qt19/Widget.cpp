#include "Widget.h"
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>

Widget::Widget(QWidget *parent) : QWidget(parent), simgleMsgBtn(this),
    customMsgBtn(this), openFileBtn(this), saveFileBtn(this)
{
  simgleMsgBtn.setText("simple message dialog");
  simgleMsgBtn.move(20, 20);
  simgleMsgBtn.resize(160, 30);

  customMsgBtn.setText("custom message dialog");
  customMsgBtn.move(20, 70);
  customMsgBtn.resize(160, 30);

  openFileBtn.setText("open file dialog");
  openFileBtn.move(20, 120);
  openFileBtn.resize(160, 30);

  saveFileBtn.setText("save file dialog");
  saveFileBtn.move(20, 170);
  saveFileBtn.resize(160, 30);

  resize(200, 220);
  setFixedSize(200, 200);

  connect(&simgleMsgBtn, SIGNAL(clicked()), this, SLOT(simpleMsgBtnClicked()));
  connect(&customMsgBtn, SIGNAL(clicked()), this, SLOT(customMsgBtnClicked()));
  connect(&openFileBtn, SIGNAL(clicked()), this, SLOT(openFileBtnClicked()));
  connect(&saveFileBtn, SIGNAL(clicked()), this, SLOT(saveFileBtnClicked()));
}

void Widget::simpleMsgBtnClicked(){
  QMessageBox msg(this);
  msg.setText("this is a message dialog");
  msg.exec();
}

void Widget::customMsgBtnClicked(){
  QMessageBox msg(this);
  msg.setWindowTitle("this is a detail message dialog");
  msg.setIcon(QMessageBox::Information);
  msg.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel |
      QMessageBox::YesAll);
  if(msg.exec()==QMessageBox::Ok){
    qDebug() << "ok button is clicked";
  }
}

void Widget::openFileBtnClicked(){
  QFileDialog dlg(this);
  dlg.setAcceptMode(QFileDialog::AcceptOpen);
  dlg.setNameFilter("Text(*.txt)");
  dlg.setFileMode(QFileDialog::ExistingFiles);
  if(dlg.exec() ==QFileDialog::Accepted){
    QStringList fs = dlg.selectedFiles();
    for(int i=0; i<fs.count(); i++){
      qDebug() << fs[i];
    }
  }
}

void Widget::saveFileBtnClicked(){
  QFileDialog dlg(this);
  dlg.setAcceptMode(QFileDialog::AcceptSave);
  dlg.setNameFilter("Text(*.txt)");
  if(dlg.exec()==QFileDialog::Accepted){
    QStringList fs = dlg.selectedFiles();
    for(int i=0; i<fs.count(); i++){
      qDebug() << fs[i];
    }
  }
}

Widget::~Widget(){}
