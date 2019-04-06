#ifndef QLOGINDIALOG_H
#define QLOGINDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>

class QLogingDialog : public QDialog
{
    Q_OBJECT
private:
    QLabel userLabel;
    QLabel pwdLabel;
    QLineEdit userEdit;
    QLineEdit pwdEdit;
    QPushButton CancelButton;
    QPushButton LogInButton;
    QString m_pwd;
    QString m_user;
private slots:
    void Loing_Clicked();
    void Cancel_Clicked();
public:
    QLogingDialog(QWidget* parent = 0);
    QString getUser();
    QString getPwd();
    ~QLogingDialog();
};


#endif // QLOGINDIALOG_H
