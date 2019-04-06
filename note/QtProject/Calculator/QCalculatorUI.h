#ifndef QCALCULATORUI_H
#define QCALCULATORUI_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

#include "ICalculator.h"

class QCalCulatorUI : public QWidget
{
    Q_OBJECT
private:
    QLineEdit* m_edit;
    QPushButton* m_buttons[20];
    ICalcualtor* m_cal;

    QCalCulatorUI();
    bool construct();

private slots:
    void onButtonClicked();

public:
    static QCalCulatorUI* NewInstance();
    void show();
    void setCalculator(ICalcualtor* cal);
    ICalcualtor* getCalculator();
    ~QCalCulatorUI();
};

#endif // QCALCULATORUI_H
