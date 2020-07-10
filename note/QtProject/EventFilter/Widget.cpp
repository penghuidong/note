#include "Widget.h"
#include <QDebug>
#include <QEvent>
#include <QKeyEvent>


Widget::Widget(QWidget *parent)
    : QWidget(parent),myLineEdit(this)
{
    myLineEdit.installEventFilter(this);  //????????
}

bool Widget::event(QEvent *e)
{
    if(e->type()==QEvent::KeyPress)
        qDebug() << "Widget::event";
    return QWidget::event(e);
}

void Widget::keyPressEvent(QKeyEvent *e)
{
    qDebug() << "Widget::KeyPressEvent";
    QWidget::keyPressEvent(e);
}

bool Widget::eventFilter(QObject *obj, QEvent *ev)
{
    bool ret = true; //filted

    if(obj==&myLineEdit&&ev->type()==QEvent::KeyPress)
    {
        qDebug()<<"Widget::eventFilter";
        QKeyEvent* evt = dynamic_cast<QKeyEvent*>(ev);
        switch(evt->key())
        {
        case Qt::Key_0:
        case Qt::Key_1:
        case Qt::Key_2:
        case Qt::Key_3:
        case Qt::Key_4:
        case Qt::Key_5:
        case Qt::Key_6:
        case Qt::Key_7:
        case Qt::Key_8:
        case Qt::Key_9:
            ret = false;
            break;
        default:
            break;
        }
    }
    else
    {
        ret = QWidget::eventFilter(obj, ev);
    }
    return ret;
}



Widget::~Widget()
{
    
}
