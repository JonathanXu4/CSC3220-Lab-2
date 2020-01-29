#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Menu options
    this->setWindowTitle("Mint Paradise");

    ui->roomSize->addItem("Choose your room size");
    ui->roomSize->addItem("Queen");
    ui->roomSize->addItem("King");

    ui->roomView->addItem("Choose your room view");
    ui->roomView->addItem("Standard");
    ui->roomView->addItem("Atrium");

    ui->cost->setText("Please fill out all information");

    ui->cardType->addItem("Choose your credit card");
    ui->cardType->addItem("American Express");
    ui->cardType->addItem("Visa");
    ui->cardType->addItem("Master Card");
    ui->cardType->addItem("Discover");

    ui->month->addItem("January");
    ui->month->addItem("February");
    ui->month->addItem("March");
    ui->month->addItem("April");
    ui->month->addItem("May");
    ui->month->addItem("June");
    ui->month->addItem("July");
    ui->month->addItem("August");
    ui->month->addItem("September");
    ui->month->addItem("October");
    ui->month->addItem("November");
    ui->month->addItem("December");

    ui->year->addItem("2019");
    ui->year->addItem("2020");
    ui->year->addItem("2021");
    ui->year->addItem("2022");
    ui->year->addItem("2023");
    ui->year->addItem("2024");
    ui->year->addItem("2025");
    ui->year->addItem("2026");

    ui->mintLabel->setPixmap(QPixmap ("../roomReservation/Pictures/mint.png").scaled(150,150,Qt::KeepAspectRatio));

    // Initializes values to defaults so they aren't null
    parkingNeeded = false;
    numNights = 1;
    card = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

// room size menu selected
void MainWindow::on_roomSize_activated(int index)
{
    roomSize = index;
    calculate();
}

// room view menu selected
void MainWindow::on_roomView_activated(int index)
{
    roomView = index;
    calculate();
}

// number of nights changed
void MainWindow::on_nights_valueChanged(int index)
{
    numNights = index;
    calculate();
}

// parking checkbox changed
void MainWindow::on_checkBox_stateChanged(int index)
{
    parkingNeeded = index;
    calculate();
}

// Calculates the estimated total cost
void MainWindow::calculate()
{
    double total = roomCalc();
    if (total > 13)
    {
        if (parkingNeeded)
            total += 12.75;
        ui->cost->setText(numToString(total * numNights));
        valid = true;
    } else {
        ui->cost->setText("Please fill out all information");
        valid = false;
    }
}

// Calculates the cost of the room
// Also sets the maximum number of guests
int MainWindow::roomCalc()
{
    if (roomSize == 1)
    {
        maxGuests = 4;
        if (roomView == 1)
        {
            return 284;
        } else if (roomView == 2)
        {
            return 290;
        }
    } else if (roomSize == 2)
    {
        maxGuests = 3;
        if (roomView == 1)
        {
            return 325;
        } else if (roomView == 2)
        {
            return 350;
        }
    }
    return 0;
}

// Page 1 next button
// Checks to see if all information is filled out
// before allowing the user to enter the next page
// Also loads all information for that page when clicked
void MainWindow::on_next1_clicked()
{
    if (valid && ui->name->toPlainText().length() > 0 &&
            (ui->adults->value() + ui->children->value()) <= maxGuests)
    {
        ui->stackedWidget->setCurrentIndex(1);
        total = 15;
        total += 1.15 * roomCalc();
        ui->room->setText(numToString(roomCalc() * numNights));
        ui->tax->setText(numToString(roomCalc() * 0.15 * numNights));
        if (parkingNeeded)
        {
            ui->parkingFee->setText(numToString(12.75 * numNights));
            total += 12.75;
        } else
        {
            ui->parkingFee->setText("$0.00");
        }
        ui->resortFee->setText(numToString(15 * numNights));
        total *= numNights;
        ui->Total->setText(numToString(total));
    }

}

// Page 2 back button
void MainWindow::on_back2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

// Converts doubles into strings with two significant figures
// and leading with $.
QString MainWindow::numToString(double num)
{
    if (num == 0)
        return "$0.00";
    num = qRound(num * 100);
    QString numb = QString::number(num);
    QChar last = numb.at(numb.length() - 1);
    QChar last2 = numb.at(numb.length() - 2);
    QString fin = "$";
    for (int i = 0; i < numb.length() - 2; i++)
    {
        fin += numb.at(i);
    }
    return fin + "." + last2 + last;
}

// Adjusts images and options based on the credit card issuer chosen
void MainWindow::on_cardType_activated(int index)
{
    card = index;
    if (index == 1)
    {
        ui->cc4->hide();
        ui->imageLabel->setPixmap(QPixmap ("../roomReservation/Pictures/americanexpress.png").scaled(100,100,Qt::KeepAspectRatio));
    } else
    {
        ui->cc4->show();
    }
    if (index == 2)
        ui->imageLabel->setPixmap(QPixmap ("../roomReservation/Pictures/visa.png").scaled(100,100,Qt::KeepAspectRatio));
    else if (index == 3)
        ui->imageLabel->setPixmap(QPixmap ("../roomReservation/Pictures/mastercard.png").scaled(100,100,Qt::KeepAspectRatio));
    else if (index == 4)
        ui->imageLabel->setPixmap(QPixmap ("../roomReservation/Pictures/discover.png").scaled(100,100,Qt::KeepAspectRatio));
}

// These 4 functions set the max length of the credit card number boxes
void MainWindow::on_cc2_textChanged()
{
    if (card == 1)
    {
        if (ui->cc2->toPlainText().length() > 6)
            ui->cc2->textCursor().deletePreviousChar();
    } else
    {
        if (ui->cc2->toPlainText().length() > 4)
            ui->cc2->textCursor().deletePreviousChar();
    }
}

void MainWindow::on_cc3_textChanged()
{
    if (card == 1)
    {
        if (ui->cc3->toPlainText().length() > 5)
            ui->cc3->textCursor().deletePreviousChar();
    } else
    {
        if (ui->cc3->toPlainText().length() > 4)
            ui->cc3->textCursor().deletePreviousChar();
    }
}

void MainWindow::on_cc1_textChanged()
{
    if (ui->cc1->toPlainText().length() > 4)
        ui->cc1->textCursor().deletePreviousChar();
}

void MainWindow::on_cc4_textChanged()
{
    if (ui->cc4->toPlainText().length() > 4)
        ui->cc4->textCursor().deletePreviousChar();
}

// Page 2 next button. Only checks that the credit card is
// valid for the selected type
void MainWindow::on_next2_clicked()
{
    if (card == ui->cc1->toPlainText().front().digitValue() - 2 &&
            ui->cc1->toPlainText().front().digitValue() != 2)
    {
        ui->stackedWidget->setCurrentIndex(2);
        ui->Duration3->setText(QString::number(numNights));
        if (roomSize == 1) {
            if (roomView == 1)
            {
                ui->RoomType3->setText("Queen Standard");
            } else
            {
                ui->RoomType3->setText("Queen Atrium");
            }
        } else
        {
            if (roomView == 1)
            {
                ui->RoomType3->setText("King Standard");
            } else
            {
                ui->RoomType3->setText("King Atrium");
            }
        }
        ui->StartDate3->setText(ui->date->dateTime().toString());
        if (parkingNeeded)
            ui->ParkingNeeded3->setText("Yes");
        else
            ui->ParkingNeeded3->setText("No");
        ui->Adults3->setText(QString::number(ui->adults->value()));
        ui->Children3->setText(QString::number(ui->children->value()));
        if (card == 1)
        {
            ui->CreditCardNumber3->setText("xxxx-xxxxxx-" + ui->cc3->toPlainText());
        } else
        {
            ui->CreditCardNumber3->setText("xxxx-xxxx-xxxx-" + ui->cc4->toPlainText());
        }
        ui->Total3->setText(numToString(total));
    }
}

// Page 3 back button
void MainWindow::on_back3_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

// Final button, goes to the final page
void MainWindow::on_next3_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    ui->endCard->setPixmap(QPixmap ("../roomReservation/Pictures/resort.png").scaled(800,460,Qt::KeepAspectRatio));
}

// closes the program
void MainWindow::on_next4_clicked()
{
    close();
}
