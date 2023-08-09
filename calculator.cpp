#include "calculator.h"
#include "ui_calculator.h"

// Some variables that we will need.

double calculatorValue = 0.0;
bool addTrigger = false;
bool subtractTrigger = false;
bool multiplicationTrigger = false;
bool divideTrigger = false;
bool percentTrigger = false;
bool squareTrigger = false; // Square here is ^2

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);

    ui->Display->setText(QString::number(calculatorValue));
    QPushButton *numButtons[10]; // Number buttons
    for(int i = 0; i < 10; ++i)
    {
        QString buttonName = "Button" + QString::number(i);
        numButtons[i] = Calculator::findChild<QPushButton *>(buttonName);
        connect(numButtons[i], SIGNAL(released()), this, SLOT(numPressed())); // Number pressing

    }

    // Math buttons, equal button, sign button and clear button functions
    connect(ui->Add, SIGNAL(released()), this, SLOT(mathButtonPressed()));
    connect(ui->Subtract, SIGNAL(released()), this, SLOT(mathButtonPressed()));
    connect(ui->Multiply, SIGNAL(released()), this, SLOT(mathButtonPressed()));
    connect(ui->Divide, SIGNAL(released()), this, SLOT(mathButtonPressed()));
    connect(ui->Percent, SIGNAL(released()), this, SLOT(mathButtonPressed()));
    connect(ui->Square, SIGNAL(released()), this, SLOT(mathButtonPressed()));
    connect(ui->Equal, SIGNAL(released()), this, SLOT(equalButton()));
    connect(ui->ChangeSign, SIGNAL(released()), this, SLOT(changeSign()));
    connect(ui->Clear, SIGNAL(released()), this, SLOT(clear()));

}

Calculator::~Calculator()
{
    delete ui;
}

// Functions

void Calculator::numPressed()
{
    QPushButton *Button = (QPushButton *)sender();
    QString buttonValue = Button->text();
    QString displayValue = ui->Display->text();

    // If numbers were pressed show them in display

    if ((displayValue.toDouble() == 0) || (displayValue.toDouble() == 0.0))
        ui->Display->setText(buttonValue); // If it's 0 show the number pressed
    else
    {
        QString newValue = displayValue + buttonValue;  // If not concatenate them
        double doubleNewValue = newValue.toDouble();
        ui->Display->setText(QString::number(doubleNewValue, 'g', 16)); // Maximum of 16 digits before it hits exponents
    }
}

void Calculator::mathButtonPressed()
{
    // Math buttons
    divideTrigger = false;
    multiplicationTrigger = false;
    addTrigger = false;
    subtractTrigger = false;
    percentTrigger = false;
    squareTrigger = false;
    QString displayValue =  ui->Display->text();
    calculatorValue = displayValue.toDouble();
    QPushButton *button = (QPushButton *)sender();
    QString buttonValue = button->text();

    // If a button was pressed the trigger will be set to true then we fill the display with the said operation

    if(QString::compare(buttonValue, "/", Qt::CaseInsensitive) == 0)
    {
        divideTrigger = true;
        ui->Display->setText(displayValue + " / ");
    }
    else if (QString::compare(buttonValue, "-", Qt::CaseInsensitive) == 0)
    {
        subtractTrigger = true;
        ui->Display->setText(displayValue + " - ");
    }
    else if (QString::compare(buttonValue, "+", Qt::CaseInsensitive) == 0)
    {
        addTrigger = true;
        ui->Display->setText(displayValue + " + ");
    }
    else if (QString::compare(buttonValue, "*", Qt::CaseInsensitive) == 0)
    {
        multiplicationTrigger = true;
        ui->Display->setText(displayValue + " * ");
    }
    else if (QString::compare(buttonValue, "%", Qt::CaseInsensitive) == 0)
    {
        percentTrigger = true;
        ui->Display->setText(displayValue + " % ");
    }
    else if (QString::compare(buttonValue, "^2", Qt::CaseInsensitive) == 0)
    {
        squareTrigger = true;
        ui->Display->setText(displayValue + " ^ 2 ");
    }
}

void Calculator::equalButton()
{
    double result = 0.0;
    QString displayValue = ui->Display->text();
    double doubleDisplayValue = displayValue.toDouble();

    // If any of the triggers were activated we will start the calculations

    if (addTrigger || subtractTrigger || multiplicationTrigger || divideTrigger || percentTrigger || squareTrigger)
    {
        if (addTrigger)
            result = calculatorValue + doubleDisplayValue;
        else if (subtractTrigger)
            result = calculatorValue - doubleDisplayValue;
        else if (multiplicationTrigger)
            result = calculatorValue * doubleDisplayValue;
        else if (divideTrigger)
            result = calculatorValue / doubleDisplayValue;
        else if (percentTrigger)
            result = calculatorValue * 0.01;
        else if (squareTrigger)
            result = calculatorValue * calculatorValue;
    }
    ui->Display->setText(QString::number(result)); // Display the result
}

void Calculator::changeSign()
{
    // Took some help with this
    QString displayValue = ui->Display->text();
    QRegExp reg("[-]?[0-9.]*");

    if (reg.exactMatch(displayValue)) // If true simply multiply the number by -1 then show it on display
    {
        double doubleDisplayValue = displayValue.toDouble();
        double doubleDisplayValueSign = -1 * doubleDisplayValue;
        ui->Display->setText((QString::number(doubleDisplayValue)));
    }
}

// Clear the screen
void Calculator::clear()
{
    ui->Display->clear();
}
