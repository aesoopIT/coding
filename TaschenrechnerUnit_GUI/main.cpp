#ifdef TEST_MODE
#include "testcalculator.h"
#include <QTest>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    TestCalculator test;
    return QTest::qExec(&test, argc, argv);
}
#else
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow w;
    w.show();
    return app.exec();
}
#endif
