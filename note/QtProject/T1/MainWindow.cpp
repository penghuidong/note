#include "MainWindow.h"
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QDebug>
#include <QList>
#include <QUrl>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setAcceptDrops(true);
}


void MainWindow::dragEnterEvent(QDragEnterEvent *e)
{
    if(e->mimeData()->hasUrls())
        e->acceptProposedAction();
    else
        e->ignore();
}

void MainWindow::dropEvent(QDropEvent *e)
{
    if(e->mimeData()->hasUrls())
    {
        QList<QUrl> list = e->mimeData()->urls();
        for(int i=0; i<list.count(); i++)
            qDebug() << list[i].toLocalFile();
    }
    else
    {
        e->ignore();
    }
}

MainWindow::~MainWindow()
{
    
}
