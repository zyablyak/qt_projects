#ifndef CALCULATORFORM_HPP
#define CALCULATORFORM_HPP

#include <QMainWindow>

class QLineEdit;

class CalculatorForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit CalculatorForm(QWidget *parent = nullptr);

private slots:
    void onButtonClick(const QString &text);

private:
    QLineEdit *display;
};

#endif 