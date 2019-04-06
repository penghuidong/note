#-------------------------------------------------
#
# Project created by QtCreator 2019-03-04T04:45:52
#
#-------------------------------------------------

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = Calculator
TEMPLATE = app
CONFIG += C++11
QMAKE_CXXFLAGS += -std=c++11
SOURCES += \
    main.cpp \
    CalculatorUI.cpp \
    CalculatorDec.cpp \
    Calculator.cpp

HEADERS  += \
    CalculatorUI.h \
    CalculatorDec.h \
    Calculator.h \
    ICalculator.h
