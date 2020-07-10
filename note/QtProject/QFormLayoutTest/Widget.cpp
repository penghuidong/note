#include "Widget.h"
#include <QFormLayout>
#include <QLineEdit>

Widget::Widget(QWidget *parent)
    : QWidget(parent, Qt::WindowCloseButtonHint)
{
    QLineEdit* userName = new QLineEdit();
    QLineEdit* passWord = new QLineEdit();
    QLineEdit* Email = new QLineEdit();
    QFormLayout* layout = new QFormLayout();

    layout->addRow("userName:", userName);
    layout->addRow("password", passWord);;
    layout->addRow("Email", Email);
    layout->setSpacing(10);

    layout->setLabelAlignment(Qt::AlignCenter);

    setWindowTitle("FTP");
    setLayout(layout);
}

Widget::~Widget()
{
    
}
