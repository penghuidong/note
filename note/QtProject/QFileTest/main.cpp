#include <QtCore/QCoreApplication>
#include <QFile>
#include <QFileInfo>
#include <QDebug>
#include <QDateTime>

void write(QString f)
{
    QFile file(f);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        file.write("D.T.Software\n");
        file.write("Pdh\n");
        file.close();
    }
}


void read(QString f)
{
    QFile file(f);

    if( file.open(QIODevice::ReadOnly | QIODevice::Text) )
    {
        QByteArray ba = file.readLine();
        QString s(ba);
        qDebug() << s;
        file.close();
    }
}

void info(QString f)
{
    QFile file(f);
    QFileInfo info(file);

    if( file.open(QIODevice::WriteOnly) )

    qDebug() << info.exists();
    qDebug() << info.isFile();
    qDebug() << info.isReadable();
    qDebug() << info.isWritable();
    qDebug() << info.created();
    qDebug() << info.lastRead();
    qDebug() << info.lastModified();
    qDebug() << info.path();
    qDebug() << info.fileName();
    qDebug() << info.suffix();
    qDebug() << info.size();

}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
    write("/home/a/project/QFileTest/QFileTest.txt");
    read("/home/a/project/QFileTest/QFileTest.txt");
    info("/home/a/project/QFileTest/QFileTest.txt");

    return a.exec();
}
