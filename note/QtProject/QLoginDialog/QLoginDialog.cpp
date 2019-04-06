#include "QLoginDialog.h"

QLogingDialog::QLogingDialog(QWidget *parent) : QDialog(parent, Qt::WindowCloseButtonHint),
    userLabel(this), pwdLabel(this), userEdit(this), pwdEdit(this),  CancelButton(this),LogInButton(this)
{
    userLabel.setText("User ID:");
    userLabel.move(20, 30);
    userLabel.resize(60, 25);

    userEdit.move(85, 30);
    userEdit.resize(180, 25);

    pwdLabel.setText("Password:");
    pwdLabel.move(20, 65);
    pwdLabel.resize(60, 25);

    pwdEdit.move(85, 65);
    pwdEdit.resize(180, 25);
    pwdEdit.setEchoMode(QLineEdit::Password);

    CancelButton.setText("Cancel");
    CancelButton.move(85, 110);
    CancelButton.resize(85, 30);

    LogInButton.setText("Login");
    LogInButton.move(180, 110);
    LogInButton.resize(85, 30);

    setWindowTitle("Login");
    setFixedSize(285, 170);

    connect(&LogInButton, SIGNAL(clicked()), this, SLOT(Loing_Clicked()));
    connect(&CancelButton, SIGNAL(clicked()), this, SLOT(Cancel_Clicked()));
}

void QLogingDialog::Loing_Clicked()
{
    m_user = userEdit.text().trimmed();
    m_pwd = pwdEdit.text();

    done(Accepted);
}

void QLogingDialog::Cancel_Clicked()
{
    done(Rejected);
}

QString QLogingDialog::getPwd()
{
    return m_pwd;
}

QString QLogingDialog::getUser()
{
    return m_user;
}

QLogingDialog::~QLogingDialog(){}

