#include <QApplication>
#include "login_form.hpp"
#include "calculator_form.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    LoginForm loginForm;

    if (loginForm.exec() == QDialog::Accepted) {
        CalculatorForm calculator;
        calculator.show();
        
        return app.exec();
    }

    return 0;
}