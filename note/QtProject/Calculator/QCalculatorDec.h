#ifndef QCALCULATORDEC_H
#define QCALCULATORDEC_H

#include <QString>
#include <QStack>
#include <QQueue>
#include "ICalculator.h"

class QCalculatorDec : public ICalcualtor
{
protected:
    QString m_exp;
    QString m_result;

    bool isDigitOrDot(QChar c);
    bool isSymbol(QChar c);
    bool isSign(QChar c);
    bool isOperator(QString s);
    bool isNumber(QString s);
    bool isLeft(QString s);
    bool isRight(QString s);
    int priority(QString s);
    bool match(QQueue<QString>& exp);
    QString calculate(QQueue<QString>& exp);  //cal the below function to calculate
    QString calculate(QString l, QString op, QString r);//the truly function to calculate
    bool transform(QQueue<QString>& exp, QQueue<QString>& output);
    QQueue<QString> split(const QString& exp);

public:
    QCalculatorDec();
    ~QCalculatorDec();
    bool expression(const QString &exp);// implement base class function
    QString expression();
    QString result();  // implement base class function

};


#endif // QCALCULATORDEC_H
