#ifndef TESTCALCULATOR_H
#define TESTCALCULATOR_H

#include <QObject>
#include <QtTest/QtTest>
#include "mainwindow.h"

class TestCalculator : public QObject
{
    Q_OBJECT

private slots:
    void testAddition();
    void testSubtraction();
    void testMultiplication();
    void testDivision();
    void testSquareRoot();
};
#endif // TESTCALCULATOR_H
