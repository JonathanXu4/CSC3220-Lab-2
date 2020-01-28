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
    bool parkingNeeded;
    bool valid;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void calculate();

private slots:
    void on_roomSize_activated(int index);

    void on_roomView_activated(int index);

    void on_nights_valueChanged(int arg1);

    void on_checkBox_stateChanged(int arg1);

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    int roomCalc();

    QString numToString(double num);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
