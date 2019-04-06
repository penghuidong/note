#include <QtGui/QApplication>
#include "QCalculator.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCalculator* cal = QCalculator::NewInstance();
    int ret = -1;

    if( cal!= NULL )
    {
        cal->show();
        ret = a.exec();
        delete cal;
    }
    return ret;
}
