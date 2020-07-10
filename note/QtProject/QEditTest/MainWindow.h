#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QTextEdit>

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
    QLineEdit lineEdit;
    QPlainTextEdit plainEdit;
    QTextEdit textEdit;

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

#endif // MAINWINDOW_H
