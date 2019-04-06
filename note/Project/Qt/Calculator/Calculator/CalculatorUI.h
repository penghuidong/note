#ifndef QCALCULATOR_H_
#define QCALCULATOR_H_

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include "ICalculator.h"

class CalculatorUI : public QWidget{
  Q_OBJECT
private:
  QLineEdit* m_edit;

  QPushButton* m_buttons[20];

  ICalculator* m_cal;

  CalculatorUI();

  bool construct();

private slots:
  void onButtonClicked();

public:
  static CalculatorUI* newInstance();

  void show();

  void setCalculator(ICalculator* cal);

  ICalculator* getCalculator();

  ~CalculatorUI();
};


#endif
