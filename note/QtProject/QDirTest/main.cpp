#include <QtCore/QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QFileInfoList>
#include <QDebug>

void test_dir()
{
    const char* PATH = "/home/a/project/QDirTest";
    QDir dir;

    if(!dir.exists(PATH))
        dir.mkdir(PATH);

    if(dir.exists(PATH))
    {
        dir.cd(PATH);
        QStringList list = dir.entryList();

        for(int i=0; i<list.count(); i++)
            qDebug() << list[i];
    }
}

unsigned int calculate_size(QString path)
{
    QFileInfo info(path);
    unsigned int ret = 0;

    if(info.isFile())
        ret = info.size();
    else if(info.isDir())
    {
        QDir dir(path);
        QFileInfoList list = dir.entryInfoList();
        for(int i=0; i<list.count(); i++)
            if( list[i].fileName()!="." && list[i].fileName()!=".." )
            {
                ret += calculate_size(list[i].absoluteFilePath());
            }
    }

    return ret;
}



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    test_dir();

    qDebug() << calculate_size("/home/a/project/QDirTest");
    
    return a.exec();
}
