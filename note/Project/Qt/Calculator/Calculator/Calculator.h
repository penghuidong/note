#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "CalculatorDec.h"
#include "CalculatorUI.h"

class Calculator{
protected:
  CalculatorUI* m_ui;  //two phace construct

  CalculatorDec m_cal;

  Calculator();

  bool construct();

public:
  static Calculator* newInstance();

  void show();

  ~Calculator();
};

#endif // CALCULATOR_H
