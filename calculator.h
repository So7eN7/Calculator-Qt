#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Calculator; }
QT_END_NAMESPACE

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private:
    Ui::Calculator *ui;

// Our functions for the calculator
private slots:
    void numPressed();
    void mathButtonPressed();
    void equalButton();
    void changeSign();
    void clear();

};
#endif // CALCULATOR_H
