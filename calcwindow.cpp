#include "calcwindow.h"
#include "ui_calcwindow.h"
#include <math.h>

double calcVal = 0.0;
bool divOn = false;
bool mulOn = false;
bool subOn = false;
bool addOn = false;
bool powOn = false;

CalcWindow::CalcWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CalcWindow)
{
    ui->setupUi(this);
    ui->Display->setText( QString::number(calcVal) );

    QPushButton *num[10];
    for(int i=0;i<10;i++)
    {
        QString buttonName = "but" + QString::number(i);
        num[i] = CalcWindow::findChild<QPushButton *>(buttonName);
        connect( num[i], SIGNAL(released()), this, SLOT(NumPressed()));
    }
    connect(ui->butAdd, SIGNAL(released()), this, SLOT(ArithmaticPressed()));
    connect(ui->butSub, SIGNAL(released()), this, SLOT(ArithmaticPressed()));
    connect(ui->butMul, SIGNAL(released()), this, SLOT(ArithmaticPressed()));
    connect(ui->butDiv, SIGNAL(released()), this, SLOT(ArithmaticPressed()));
    connect(ui->butAns, SIGNAL(released()), this, SLOT(EqualPressed()));
    connect(ui->butPow, SIGNAL(released()), this, SLOT(ArithmaticPressed()));
    connect(ui->butClr, SIGNAL(released()), this, SLOT(ClearPressed()));
}

CalcWindow::~CalcWindow()
{
    delete ui;
}

void CalcWindow::NumPressed()
{

    QPushButton *button = (QPushButton *)sender();
    QString buttonValue = button->text();
    QString displayValue = ui->Display->text();

    if(addOn || subOn || divOn || mulOn || powOn)
    {}
    else
    {
        ui->label->setText("");
    }

    if( (displayValue.toDouble() == 0) || (displayValue.toDouble() == 0.0) )
    {
        ui->Display->setText(buttonValue);
    }
    else
    {
        QString n = displayValue + buttonValue;
        double newVal = n.toDouble();
        ui->Display->setText( QString::number(newVal, 'g', 10) );
    }
}

void CalcWindow::ArithmaticPressed()
{
    if(addOn || subOn || divOn || mulOn || powOn)
    {
        EqualPressed();
    }
    QString displayVal = ui->Display->text();
    calcVal = displayVal.toDouble();

    QPushButton *button = (QPushButton *)sender();
    QString buttonValue = button->text();

    if (QString::compare(buttonValue, "/", Qt::CaseInsensitive) == 0)
    {
        divOn = true;
    }
    else if (QString::compare(buttonValue, "*", Qt::CaseInsensitive) == 0)
    {
        mulOn = true;
    }
    else if (QString::compare(buttonValue, "-", Qt::CaseInsensitive) == 0)
    {
        subOn = true;
    }
    else if (QString::compare(buttonValue, "+", Qt::CaseInsensitive) == 0)
    {
        addOn = true;
    }
    else if (QString::compare(buttonValue, "^", Qt::CaseInsensitive) == 0)
    {
        powOn = true;
    }

    ui->Display->setText("");
    ui->label->setText( QString::number(calcVal) + " " + buttonValue );
}

void CalcWindow::EqualPressed()
{
    double sol = 0.0;
    QString displayVal = ui->Display->text();
    double doubleDV = displayVal.toDouble();

    if(addOn || subOn || mulOn || divOn || powOn)
    {
        if(addOn)
        {
            sol = calcVal + doubleDV;
        }
        else if(subOn)
        {
            sol = calcVal - doubleDV;
        }
        else if (mulOn)
        {
            sol = calcVal * doubleDV;
        }
        else if(divOn)
        {
            sol = calcVal / doubleDV;
        }
        else if(powOn)
        {
            sol = pow(calcVal,doubleDV);
        }
        else
        {

        }
        ui->Display->setText(QString::number(sol, 'g', 10));
        ui->label->setText( ui->label->text() + " " + displayVal );

        divOn = false;
        mulOn = false;
        subOn = false;
        addOn = false;
        powOn = false;
    }
}

void CalcWindow::ClearPressed()
{
    ui->Display->setText("");
    ui->label->setText("");
    calcVal = 0.0;
}
