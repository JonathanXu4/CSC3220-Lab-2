#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->roomSize->addItem("Choose your room size");
    ui->roomSize->addItem("Queen");
    ui->roomSize->addItem("King");

    ui->roomView->addItem("Choose your room view");
    ui->roomView->addItem("Standard");
    ui->roomView->addItem("Atrium");

    ui->cost->setText("Please fill out all information");


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_roomSize_activated(int index)
{
    roomSize = index;
    calculate();
}

void MainWindow::on_roomView_activated(int index)
{
    roomView = index;
    calculate();
}

void MainWindow::on_nights_valueChanged(int index)
{
    numNights = index;
    calculate();
}

void MainWindow::on_checkBox_stateChanged(int index)
{
    parkingNeeded = index;
    calculate();
}

void MainWindow::calculate()
{
    double total = 0;
    if (roomSize == 1)
    {
        if (roomView == 1)
        {
            total += 284;
        } else if (roomView == 2)
        {
            total += 290;
        }
    } else if (roomSize == 2)
    {
        if (roomView == 1)
        {
            total += 325;
        } else if (roomView == 2)
        {
            total += 350;
        }
    }
    if (total > 13)
    {
        if (parkingNeeded)
        {
            total += 12.75;
            ui->cost->setText("$" + QString::number(total));
        } else {
            ui->cost->setText("$" + QString::number(total) + ".00");
        }
        valid = true;
    } else {
        ui->cost->setText("Please fill out all information");
        valid = false;
    }
}

void MainWindow::on_pushButton_clicked()
{
    if (valid)
        ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
