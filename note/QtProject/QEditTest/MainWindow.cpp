#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),lineEdit(this), plainEdit(this),textEdit(this)
{
    resize(600, 420);

    lineEdit.move(20, 20);
    lineEdit.resize(560, 100);
    lineEdit.insert("QLineEdit");
    lineEdit.insert("\n");
    lineEdit.insert("<img src=\"/home/a/project/QEditTest/D.T.png\" /img>");

    plainEdit.move(20, 130);
    plainEdit.resize(560, 130);
    plainEdit.insertPlainText("QPlainTextEdit");
    plainEdit.insertPlainText("\n");
    plainEdit.insertPlainText("<img src=\"/home/a/project/QEditTest/D.T.png\" /img>");

    textEdit.move(20, 270);
    textEdit.resize(560, 130);
    textEdit.insertPlainText("QTextEdit");
    textEdit.insertPlainText("\n");
    textEdit.insertHtml("<img src=\"/home/a/project/QEditTest/D.T.png\" /img>");
}

MainWindow::~MainWindow()
{
    
}
