#ifndef CALCULATORDEC_H
#define CALCULATORDEC_H

#include <QString>
#include <QStack>
#include <QQueue>
#include <cfloat>
#include "ICalculator.h"
class CalculatorDec : public ICalculator{
protected:
  QString m_exp;

  QString m_result;

protected:
  bool isDigitOrDot(QChar c);

  bool isSymbol(QChar c);

  bool isSign(QChar c);

  bool isNumber(QString s);

  bool isOperatro(QString s);

  bool isLeft(QString s);

  bool isRight(QString s);

  int priority(QString s);

  QQueue<QString> split(const QString& exp);

  bool match(QQueue<QString>& exp);

  bool transform(QQueue<QString>& exp, QQueue<QString>& output);

  QString calculate(QQueue<QString>& exp);

  QString calculate(QString& l, QString& op,QString& r);
public:
  CalculatorDec();

  ~CalculatorDec();

  bool expression(const QString& exp);

  QString expression();

  QString result();
};


#endif // CALCULATORDEC_H
