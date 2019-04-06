#include "Widget.h"
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>


Widget::Widget(QWidget *parent)
    : QWidget(parent), SimpleMsgBtn(this), CustonMsgBtn(this), OpenFileBtn(this), SaveFileBtn(this)
{
    SimpleMsgBtn.setText("Simple Message Dialog");
    SimpleMsgBtn.move(20, 20);
    SimpleMsgBtn.resize(160, 30);

    CustonMsgBtn.setText("Custon Message Dialog");
    CustonMsgBtn.move(20, 70);
    CustonMsgBtn.resize(160, 30);

    OpenFileBtn.setText("Open File Dialog");
    OpenFileBtn.move(20, 120);
    OpenFileBtn.resize(160, 30);

    SaveFileBtn.setText("Save File Dialog");
    SaveFileBtn.move(20, 170);
    SaveFileBtn.resize(160, 30);

    resize(200, 220);
    setFixedSize(200, 220);

    connect(&SimpleMsgBtn, SIGNAL(clicked()), this, SLOT(SimpleMsgBtn_clicked()));
    connect(&CustonMsgBtn, SIGNAL(clicked()), this, SLOT(CustonMsgBtn_clicked()));
    connect(&OpenFileBtn, SIGNAL(clicked()), this, SLOT(OpenFileBtn_clicked()));
    connect(&SaveFileBtn, SIGNAL(clicked()), this, SLOT(SaveFileBtn_clicked()));
}

void Widget::SimpleMsgBtn_clicked()
{
    QMessageBox msg(this);
    msg.setText("This is a message dialog");
    msg.exec();
}

void Widget::CustonMsgBtn_clicked()
{
    QMessageBox msg(this);

    msg.setWindowTitle("Window Title");
    msg.setText("This is a detail message dialog");
    msg.setIcon(QMessageBox::Information);
    msg.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel | QMessageBox::YesAll);

    if( msg.exec() == QMessageBox::Ok)
        qDebug() << "Ok button is clicked";

}

void Widget::SaveFileBtn_clicked()
{
    QFileDialog dlg(this);

    dlg.setAcceptMode(QFileDialog::AcceptSave);
    dlg.setFilter("Text(*.txt)");
    dlg.setFileMode(QFileDialog::ExistingFiles);

    if(dlg.exec()==QFileDialog::Accepted)
    {
        QStringList fs = dlg.selectedFiles();
        for(int i=0; i<fs.count(); i++)
            qDebug() << fs[i];
    }
}

void Widget::OpenFileBtn_clicked()
{
    QFileDialog dlg(this);

    dlg.setAcceptMode(QFileDialog::AcceptOpen);
    dlg.setFilter("Text (*.txt)");
    dlg.setFileMode(QFileDialog::ExistingFiles);

    if(dlg.exec()==QFileDialog::Accepted)
    {
        QStringList fs = dlg.selectedFiles();
        for(int i=0; i<fs.count(); i++)
            qDebug() << fs[i];
    }
}



Widget::~Widget(){}








