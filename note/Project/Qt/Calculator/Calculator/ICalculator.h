#ifndef ICALCULATOR_H_
#define ICALCULATOR_H_

#include <QString>

class ICalculator{
public:
  virtual bool expression(const QString& exp) = 0;

  virtual QString result() = 0;
};

#endif // ICALCULATOR_H
