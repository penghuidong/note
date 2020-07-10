#include <QtCore/QCoreApplication>

#include <QDebug>

class MObj : public QObject
{
    QString m_name;
public:
    MObj(const QString& name)
    {
        m_name = name;
    }
    ~MObj(){}
};

void fcTest()
{
    QObject* p = new QObject();
    QObject* c1 = new QObject();
    QObject* c2 = new QObject();

    c1->setParent(p);
    c2->setParent(p);
    c1->setObjectName("I am c1");

    qDebug() << "c1->objectName(" << c1->objectName() << ")";
    qDebug() << "c2->objectName(" << c2->objectName() << ")";
}

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);

    fcTest();

    return a.exec();
}
