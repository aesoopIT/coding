#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Ui::MainWindow* getUi();
    double parseExpression(const QString &expr);

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void onButtonClicked();
    void onEqualButtonClicked();
    void onClearButtonClicked();
    void onWurzelButtonClicked();

private:
    Ui::MainWindow *ui;
    QString expression;


    double ausdruck(const QString &expr, int &pos);
    double summand(const QString &expr, int &pos);
    double factor(const QString &expr, int &pos);
    double zahl(const QString &expr, int &pos);
};

#endif // MAINWINDOW_H
