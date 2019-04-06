#include "QCalculator.h"

QCalculator::QCalculator(){}

bool QCalculator::construct()
{
    m_ui = QCalCulatorUI::NewInstance();

    if(m_ui!=NULL)
        m_ui->setCalculator(&m_cal);   // question: how to connect  QCalculatorUI to QCalculatoDec?

    return (m_ui!=NULL);
}

QCalculator* QCalculator::NewInstance()
{
    QCalculator* ret = new QCalculator(); // for QCalculatorUI is two phase construct, QCalculator is also
                                            // two phase construct

    if((ret==NULL) || !ret->construct() )
    {
        delete ret;
        ret = NULL;
    }

    return ret;
}

void QCalculator::show()
{
    m_ui->show();
}

QCalculator::~QCalculator()
{
    delete m_ui;
}




