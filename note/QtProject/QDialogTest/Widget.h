#ifndef WIDGET_H
#define WIDGET_H

#include <QtGui/QWidget>
#include <QPushButton>

class Widget : public QWidget
{
    Q_OBJECT
private:
    QPushButton SimpleMsgBtn;
    QPushButton CustonMsgBtn;
    QPushButton OpenFileBtn;
    QPushButton SaveFileBtn;
private slots:
    void SimpleMsgBtn_clicked();
    void CustonMsgBtn_clicked();
    void OpenFileBtn_clicked();
    void SaveFileBtn_clicked();

public:
    Widget(QWidget* parent = 0);
    ~Widget();
};


#endif // WIDGET_H
