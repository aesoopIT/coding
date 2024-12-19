#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QMessageBox>
#include <QKeyEvent>
#include <cctype>
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Verbindungen für Buttons
    connect(ui->button0, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
    connect(ui->button1, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
    connect(ui->button2, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
    connect(ui->button3, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
    connect(ui->button4, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
    connect(ui->button5, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
    connect(ui->button6, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
    connect(ui->button7, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
    connect(ui->button8, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
    connect(ui->button9, &QPushButton::clicked, this, &MainWindow::onButtonClicked);

    // Operatoren Verbinden
    connect(ui->buttonAdd, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
    connect(ui->buttonSubtract, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
    connect(ui->buttonMultiply, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
    connect(ui->buttonDivide, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
    connect(ui->buttonDot, &QPushButton::clicked, this, &MainWindow::onButtonClicked);

    connect(ui->buttonEqual, &QPushButton::clicked, this, &MainWindow::onEqualButtonClicked);
    connect(ui->buttonClear, &QPushButton::clicked, this, &MainWindow::onClearButtonClicked);
    connect(ui->buttonWurzel, &QPushButton::clicked, this, &MainWindow::onWurzelButtonClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

Ui::MainWindow *MainWindow::getUi()
{
    return ui;
}

void MainWindow::onButtonClicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (button) {
        expression += button->text();
        ui->label->setText(expression);
    }
}

void MainWindow::onEqualButtonClicked()
{
    try {
        int pos = 0;
        double result = parseExpression(expression);
        ui->label->setText(QString::number(result));
    } catch (const std::exception &e) {
        ui->label->setText("Error");
    }
}

void MainWindow::onClearButtonClicked()
{
    expression.clear();
    ui->label->clear();
}

void MainWindow::onWurzelButtonClicked()
{
    expression += "√";
    ui->label->setText(expression);
}

double MainWindow::parseExpression(const QString &expr)
{
    int pos = 0;
    return ausdruck(expr, pos);
}

double MainWindow::ausdruck(const QString &expr, int &pos)
{
    double result = summand(expr, pos);

    while (pos < expr.length()) {
        QChar op = expr[pos];
        if (op == '+') {
            pos++;
            result += summand(expr, pos);
        } else if (op == '-') {
            pos++;
            result -= summand(expr, pos);
        } else {
            break;
        }
    }
    return result;
}

double MainWindow::summand(const QString &expr, int &pos)
{
    double result = factor(expr, pos);

    while (pos < expr.length()) {
        QChar op = expr[pos];
        if (op == '*') {
            pos++;
            result *= factor(expr, pos);
        } else if (op == '/') {
            pos++;
            double divisor = factor(expr, pos);
            if (divisor == 0) throw std::runtime_error("Division durch 0");
            result /= divisor;
        } else {
            break;
        }
    }
    return result;
}

double MainWindow::factor(const QString &expr, int &pos)
{
    if (expr[pos] == '(') {
        pos++;
        double result = ausdruck(expr, pos);
        if (expr[pos] == ')') pos++;
        return result;
    } else if (expr.mid(pos, 1) == "√") {   // QString für Wurzel Symbol
        pos++;
        double value = factor(expr, pos);
        if (value < 0) throw std::runtime_error("Keine Wurzel von negativen Zahlen möglich.");
        return std::sqrt(value);

    }
    return zahl(expr, pos);
}

double MainWindow::zahl(const QString &expr, int &pos)
{
    QString num;
    while (pos < expr.length() && (expr[pos].isDigit() || expr[pos] == '.')) {
        num += expr[pos];
        pos++;
    }
    return num.toDouble();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();
    if ((key >= Qt::Key_0 && key <= Qt::Key_9) || key == Qt::Key_Plus || key == Qt::Key_Minus || key == Qt::Key_Asterisk || key == Qt::Key_Slash || key == Qt::Key_Period) {
        expression += event->text();
        ui->label->setText(expression);
    } else if (key == Qt::Key_Enter || key == Qt::Key_Return) {
        onEqualButtonClicked();
    } else if (key == Qt::Key_C) {
        onClearButtonClicked();
    } else if (key == Qt::Key_V) {
        onWurzelButtonClicked();
    } else {
        QMainWindow::keyPressEvent(event); // Standardverhalten für andere Tasten
    }
}
