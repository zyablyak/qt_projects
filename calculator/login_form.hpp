#ifndef LOGINFORM_HPP
#define LOGINFORM_HPP

#include <QDialog>

class QLineEdit;
class QPushButton;

class LoginForm : public QDialog
{
    Q_OBJECT

public:
    explicit LoginForm(QWidget *parent = nullptr);

private slots:
    void checkLogin();

private:
    QLineEdit *usernameInput;
    QLineEdit *passwordInput;
    QPushButton *loginButton;
};

#endif 