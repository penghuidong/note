#include "MyLineEdit.h"
#include <QEvent>
#include <QKeyEvent>
#include <QDebug>

MyLineEdit::MyLineEdit(QWidget *parent) :
    QLineEdit(parent)
{
}


bool MyLineEdit::event(QEvent *e)
{
    if(e->type()==QEvent::KeyPress)
        qDebug() << "MyLineEdit::event";
    return QLineEdit::event(e);
}

void MyLineEdit::keyPressEvent(QKeyEvent *e)
{
    qDebug() << "MyLineEdit::KeyPressEvent";
    QLineEdit::keyPressEvent(e);
    e->ignore();
}
