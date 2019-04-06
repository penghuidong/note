#include "LoginDialog.h"
#include <QDebug>

LoginDialog::LoginDialog(QWidget* parent) :
      QDialog(parent, Qt::WindowCloseButtonHint),  userLabel(this),
      pwdLabel(this), userEdit(this), pwdEdit(this), loginBtn(this),
      cancelBtn(this)
{
  userLabel.setText("user");
  userLabel.move(20, 30);
  userLabel.resize(60, 25);

  userEdit.move(85, 30);
  userEdit.resize(180, 25);

  pwdLabel.setText("password");
  pwdLabel.move(20, 65);
  pwdLabel.resize(60, 25);

  pwdEdit.move(85, 65);
  pwdEdit.resize(180, 25);
  pwdEdit.setEchoMode(QLineEdit::Password);

  cancelBtn.setText("cancel");
  cancelBtn.move(85, 110);
  cancelBtn.resize(85, 30);

  loginBtn.setText("login");
  loginBtn.move(180, 110);
  loginBtn.resize(85, 30);

  setWindowTitle("login");
  setFixedSize(285, 170);

  connect(&loginBtn, SIGNAL(clicked()), this, SLOT(loginBtnClicked()));
  connect(&cancelBtn, SIGNAL(clicked()), this, SLOT(cancelBtnClicked()));
}

void LoginDialog::loginBtnClicked()
{
  qDebug() << "loginBtnClicked() begin";
  m_user = userEdit.text().trimmed();
  m_pwd = pwdEdit.text();
  done(Accepted);
  qDebug() << "loginBtnClicked() end";
}

void LoginDialog::cancelBtnClicked()
{
  qDebug() << "cancelBtnClicked() begin";
  done(Rejected);
  qDebug() << "cancelBtnClicked() end";
}



QString LoginDialog::getUser(){return m_user;}

QString LoginDialog::getPwd(){ return m_pwd;}

LoginDialog::~LoginDialog(){}
