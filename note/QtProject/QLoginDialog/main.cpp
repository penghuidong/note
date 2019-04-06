#include <QtGui/QApplication>
#include "QLoginDialog.h"

int main(int argc, char** argv)
{
    QApplication a(argc, argv);

    QLogingDialog loginDialog;
    loginDialog.show();

    return a.exec();
}
