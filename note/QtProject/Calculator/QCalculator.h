#ifndef QCALCULATOR_H
#define QCALCULATOR_H

#include "QCalculatorDec.h"
#include "QCalculatorUI.h"

class QCalculator
{
protected:
    QCalCulatorUI* m_ui;  // two phase construct, memory from heap, so use pointer
    QCalculatorDec m_cal;

    QCalculator();
    bool construct();

public:
    static QCalculator* NewInstance();
    void show();
    ~QCalculator();
};


#endif // QCALCULATOR_H
