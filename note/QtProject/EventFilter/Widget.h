#ifndef WIDGET_H
#define WIDGET_H

#include <QtGui/QWidget>
#include "MyLineEdit.h"

class Widget : public QWidget
{
    Q_OBJECT
    MyLineEdit myLineEdit;
public:
    Widget(QWidget *parent = 0);
    bool event(QEvent *e);
    void keyPressEvent(QKeyEvent *e);
    bool eventFilter(QObject *obj, QEvent *ev);
    ~Widget();
};

#endif // WIDGET_H
