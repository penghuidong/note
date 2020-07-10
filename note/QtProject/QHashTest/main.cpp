#include <QtCore/QCoreApplication>
#include <QHash>
#include <QHashIterator>
#include <QDebug>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QHash<QString, int> hash;

    hash["key 2"] = 2;
    hash["key 0"] = 0;
    hash["key 1"] = 1;

    QList<QString> klist = hash.keys();
    for(int i=0; i<klist.count(); i++)
        qDebug() << klist[i];

    QList<int> vlist = hash.values();
    for(int i=0; i<vlist.count(); i++)
        qDebug() << vlist[i];

    hash.insert("key 3", 3);

    QHash<QString,int>::const_iterator i;

    for(i=hash.begin(); i!=hash.end(); i++)
        qDebug() << i.key() << i.value();
    
    return a.exec();
}
