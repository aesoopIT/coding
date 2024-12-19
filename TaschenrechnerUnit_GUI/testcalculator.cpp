#include "testcalculator.h"

void TestCalculator::testAddition()
{
    MainWindow calc;
    QCOMPARE(calc.parseExpression("2+3"), 5.0);
}

void TestCalculator::testSubtraction()
{
    MainWindow calc;
    QCOMPARE(calc.parseExpression("5-2"), 3.0);
}

void TestCalculator::testMultiplication()
{
    MainWindow calc;
    QCOMPARE(calc.parseExpression("4*3"), 12.0);
}

void TestCalculator::testDivision()
{
    MainWindow calc;
    QCOMPARE(calc.parseExpression("9/3"), 3.0);
}

void TestCalculator::testSquareRoot()
{
    MainWindow calc;
    QCOMPARE(calc.parseExpression("√16"), 4.0);
    QCOMPARE(calc.parseExpression("√9"), 3.0);
    QCOMPARE(calc.parseExpression("√0"), 0.0);
}
