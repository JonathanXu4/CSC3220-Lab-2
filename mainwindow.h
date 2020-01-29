#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QString customerName;
    int roomSize;
    int roomView;
    int numNights;
    int maxGuests;
    int card;
    bool parkingNeeded;
    bool valid;
    double total;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void calculate();

private slots:
    void on_roomSize_activated(int index);

    void on_roomView_activated(int index);

    void on_nights_valueChanged(int arg1);

    void on_checkBox_stateChanged(int arg1);

    void on_next1_clicked();

    void on_back2_clicked();

    int roomCalc();

    QString numToString(double num);

    void on_cardType_activated(int index);

    void on_cc2_textChanged();

    void on_cc3_textChanged();

    void on_cc1_textChanged();

    void on_cc4_textChanged();

    void on_next2_clicked();

    void on_back3_clicked();

    void on_next3_clicked();

    void on_next4_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
