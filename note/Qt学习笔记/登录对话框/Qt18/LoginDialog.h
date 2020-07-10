#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QString>

class LoginDialog : public QDialog{
  Q_OBJECT
private:
  QLabel userLabel;
  QLabel pwdLabel;
  QLineEdit userEdit;
  QLineEdit pwdEdit;
  QPushButton loginBtn;
  QPushButton cancelBtn;
  QString m_user;
  QString m_pwd;

private slots:
  void loginBtnClicked();
  void cancelBtnClicked();

public:
  LoginDialog(QWidget* parent = nullptr);
  QString getUser();
  QString getPwd();
  ~LoginDialog();
};

#endif // LOGINDIALOG_H
