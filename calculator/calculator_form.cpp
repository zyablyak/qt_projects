#include "calculator_form.hpp"

#include <QWidget>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QJSEngine> 

CalculatorForm::CalculatorForm(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("Калькулятор");
    setFixedSize(300, 400);

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    display = new QLineEdit(this);
    display->setReadOnly(true);
    display->setFixedHeight(50);
    display->setStyleSheet("font-size: 24px;");
    mainLayout->addWidget(display);

    QGridLayout *buttonsLayout = new QGridLayout();

    const QStringList buttons = {
        "7", "8", "9", "/",
        "4", "5", "6", "*",
        "1", "2", "3", "-",
        "C", "0", "=", "+"
    };

    int row = 0;
    int col = 0;
    for (const QString &text : buttons) {
        QPushButton *button = new QPushButton(text, this);
        button->setFixedSize(60, 60);
        button->setStyleSheet("font-size: 18px;");

        connect(button, &QPushButton::clicked, this, [this, text](){
            onButtonClick(text);
        });

        buttonsLayout->addWidget(button, row, col);
        col++;
        if (col > 3) {
            col = 0;
            row++;
        }
    }

    mainLayout->addLayout(buttonsLayout);
}

void CalculatorForm::onButtonClick(const QString &text)
{
    if (text == "C") {
        display->clear();
    } else if (text == "=") {

        QJSEngine engine;
        QJSValue result = engine.evaluate(display->text());

        if (result.isError()) {
            display->setText("Ошибка");
        } else {
            display->setText(result.toString());
        }
    } else {
        display->setText(display->text() + text);
    }
}