#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <lcd.h>
#include <stdbool.h>
#include <unistd.h>
#include <cmath>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();


private slots:
    void setupKeypad();
    char getKey();


    void on_radioButton_clicked(bool checked);

    void on_radioButton_2_clicked(bool checked);

    void on_radioButton_3_clicked(bool checked);

    //void on_radioButton_4_clicked(bool checked);

    void on_radioButton_4_clicked(bool checked);

private:
    Ui::Dialog *ui;

    // Definisanje pinova za matricnu tastaturu
    int rowPins[4] = {26,27,28,29};  // GPIO pinovi za redove
    int colPins[4] = {8,9,7,0}; // GPIO pinovi za kolone
    const char keys[4][4] = {
        {'1', '2', '3', 'A'},
        {'4', '5', '6', 'B'},
        {'7', '8', '9', 'C'},
        {'*', '0', '#', 'D'}
    };


};
#endif // DIALOG_H
