#include "login_form.hpp"

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QMessageBox>

LoginForm::LoginForm(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Окно входа");
    setFixedSize(300, 150);

    QLabel *usernameLabel = new QLabel("Логин:", this);
    usernameInput = new QLineEdit(this);
    usernameInput->setPlaceholderText("Введите 'login'");

    QLabel *passwordLabel = new QLabel("Пароль:", this);
    passwordInput = new QLineEdit(this);
    passwordInput->setEchoMode(QLineEdit::Password);
    passwordInput->setPlaceholderText("Введите 'admin'");

    loginButton = new QPushButton("Войти", this);

    QGridLayout *layout = new QGridLayout(this); 
    layout->addWidget(usernameLabel, 0, 0);
    layout->addWidget(usernameInput, 0, 1);
    layout->addWidget(passwordLabel, 1, 0);
    layout->addWidget(passwordInput, 1, 1);
    layout->addWidget(loginButton, 2, 0, 1, 2);


    connect(loginButton, &QPushButton::clicked, this, &LoginForm::checkLogin);
}

void LoginForm::checkLogin()
{
    if (usernameInput->text() == "login" && passwordInput->text() == "admin") {

        accept();
    } else {

        QMessageBox::warning(this, "Ошибка", "Неверный логин или пароль!");
    }
}
