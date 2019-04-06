#include "Widget.h"
#include <QDebug>
#include <QFontDialog>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QProgressDialog>
#include <QTextDocument>

Widget::Widget(QWidget *parent): QWidget(parent), fontDialogBtn(this),
      progressDialogBtn(this), printDialogBtn(this)
{
  fontDialogBtn.setText("font dialog");
  fontDialogBtn.move(20, 20);
  fontDialogBtn.resize(160, 30);

  progressDialogBtn.setText("progress dialog");
  progressDialogBtn.move(20, 70);
  progressDialogBtn.resize(160, 30);

  printDialogBtn.setText("print dialog");
  printDialogBtn.move(20, 120);
  printDialogBtn.resize(160, 30);

  resize(200, 170);
  setFixedSize(200, 170);

  connect(&fontDialogBtn, SIGNAL(clicked()), this, SLOT(fontDialogBtnClicked()));
  connect(&progressDialogBtn, SIGNAL(clicked()), this, SLOT(progressDialogBtnClicked()));
  connect(&printDialogBtn, SIGNAL(clicked()), this, SLOT(printDialogBtnClicked()));
}

void Widget::fontDialogBtnClicked(){
  QFontDialog dlg(this);
  dlg.setWindowTitle("font dialog test");
  dlg.setCurrentFont(QFont("Courier New", 10, QFont::Bold));
  if(dlg.exec()==QFontDialog::Accepted){
    qDebug() << dlg.selectedFont();
  }
}

void Widget::progressDialogBtnClicked(){
  QProgressDialog dlg(this);

  dlg.setWindowTitle("updating...");
  dlg.setLabelText("downloading update from server...");
  dlg.setMinimum(0);
  dlg.setMaximum(100);
  dlg.setValue(10);

  // create a new thread
  dlg.exec();
}

void Widget::printDialogBtnClicked(){
  QPrintDialog dlg(this);
  dlg.setWindowTitle("print dialog test");
  if(dlg.exec()==QPrintDialog::Accepted){
    QPrinter* p = dlg.printer();
    QTextDocument td;
    td.setHtml("<h1>print html object test</h1>");
    p->setOutputFileName("D:\\text.pdf");
    td.print(p);
  }
}

Widget::~Widget(){}
