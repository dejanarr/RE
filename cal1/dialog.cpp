#include "dialog.h"
#include "ui_dialog.h"

//dodela vrednosti za konkretne pinove
const int RS=3;
const int EN=14;
const int D0=4;
const int D1=12;
const int D2=13;
const int D3=6;

// Inicijalizacija matricne tastature
void Dialog::setupKeypad() {
    wiringPiSetup();

    for (int i = 0; i < 4; i++) {
        pinMode(rowPins[i], OUTPUT);
        digitalWrite(rowPins[i], HIGH);
    }

    for (int i = 0; i < 4; i++) {
        pinMode(colPins[i], INPUT);
        pullUpDnControl(colPins[i], PUD_UP);
    }
}

char Dialog::getKey() {
    for (int i = 0; i < 4; i++) {
        digitalWrite(rowPins[i], LOW);

        for (int j = 0; j < 4; j++) {
            if (digitalRead(colPins[j]) == LOW) {
                while(digitalRead(colPins[j]) == LOW);
                digitalWrite(rowPins[i],HIGH);

                return keys[i][j];
            }
        }

        digitalWrite(rowPins[i], HIGH);

    }

    return '\0'; // Nema pritisnutih tastera
}

int lcd_h;

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

}

Dialog::~Dialog()
{
    delete ui;
}



void Dialog::on_radioButton_clicked(bool checked)
{

    if(wiringPiSetup() == -1)
        exit(1);

    lcd_h = lcdInit (2, 16, 4, RS, EN, D0, D1, D2, D3, D0, D1, D2, D3);

    setupKeypad();

    bool result = false;
    float num = 0;
    float rez = 0;

    while(1) {


        if (checked) {
            char key = getKey();

            if (key != '\0') {

                if (key == '#') result = true;

                if (key >= '0' && key <= '9') {
                    if (num == 0) {
                        num = key - '0';
                    } else
                        num = (num*10) + key - '0';
                    lcdClear(lcd_h);
                    lcdPrintf(lcd_h, "%.0f", num);
                }

                if (key == '*') {
                    num = 0;
                    result = false;

                    lcdClear(lcd_h);
                    lcdPosition(lcd_h, 0, 0);
                    lcdPrintf(lcd_h, "RESTART");

                    delay(2000);

                    lcdClear(lcd_h);

                    break;
                }

                if (key == 'A' || key == 'B' || key == 'C' || key == 'D') {
                    lcdPosition(lcd_h,0,0);
                    lcdPrintf(lcd_h,"Invalid");
                    lcdPosition(lcd_h,0,1);
                    lcdPrintf(lcd_h, "operation");
                }
            }

            if (result == true) {
                rez = num * num;
                lcdClear(lcd_h);
                lcdPosition(lcd_h, 0, 0);
                lcdPrintf(lcd_h, "%.0f na kv", num);
                lcdPosition(lcd_h, 0, 1);
                lcdPrintf(lcd_h, "=%.0f", rez);

                num = 0;
                rez = 0;

                result = false;

            }

        }
    }
}

void Dialog::on_radioButton_2_clicked(bool checked)
{
    if(wiringPiSetup() == -1)
            exit(1);

    lcd_h = lcdInit (2, 16, 4, RS, EN, D0, D1, D2, D3, D0, D1, D2, D3);

    setupKeypad();

    float num1 = 0;
    float num2 = 0;
    float number = 0;
    char action = '\0';
    bool result = false;
    float rez = 0;

     while(1) {

        if (checked) {
            char key = getKey();

            if (key != '\0') {
                if (key >= '0' && key <='9') {
                    if (number == 0)
                        number = key - '0';
                    else
                        number = (number*10) + key - '0';

                    lcdClear(lcd_h);

                    lcdPosition(lcd_h, 0, 0);
                    lcdPrintf(lcd_h, "%.0f", number);
                }

                if (key == '#') {
                    num2 = number;
                    result = true;
                    lcdPrintf(lcd_h, "=");
                }

                if (key == '*') {
                    number = 0;
                    num1 = 0;
                    num2 = 0;
                    result = false;

                    lcdClear(lcd_h);
                    lcdPosition(lcd_h, 0, 0);
                    lcdPrintf(lcd_h, "RESTART");

                    delay(2000);

                    lcdClear(lcd_h);

                    break;
                }

                if (key == 'A' || key == 'B' || key == 'C' || key == 'D') {
                    num1 = number;
                    number = 0;
                    if (key == 'A') action = '+';
                    if (key == 'B') action = '-';
                    if (key == 'C') action = '*';
                    if (key == 'D') action = '/';

                    lcdPosition(lcd_h, 0, 1);
                    lcdPrintf(lcd_h, "%c", action);

                    delay(100);
                }

                if (action == '+') rez = num1 + num2;
                if (action == '-') rez = num1 - num2;
                if (action == '*') rez = num1 * num2;
                if (action == '/') rez = num1 / num2;

                if (result == true) {
                    lcdPosition(lcd_h, 0, 0);
                    lcdPrintf(lcd_h, "%.0f", num1);
                    lcdPrintf(lcd_h, "%c", action);
                    lcdPrintf(lcd_h, "%.0f", num2);
                    lcdPosition(lcd_h, 0, 1);
                    lcdPrintf(lcd_h, "= %.2f", rez);

                    number = 0;
                    num1 = 0;
                    num2 = 0;
                    result = false;

                }
            }
        }
    }
}



void Dialog::on_radioButton_3_clicked(bool checked)
{
    if(wiringPiSetup() == -1)
            exit(1);

    lcd_h = lcdInit (2, 16, 4, RS, EN, D0, D1, D2, D3, D0, D1, D2, D3);

    setupKeypad();

    float num = 0;
    bool result = false;
    float rez = 0;

    while(1) {

       if (checked) {
           char key = getKey();

           if (key != '\0') {
               if (key >= '0' && key <='9') {
                   if (num == 0)
                       num = key - '0';
                   else
                       num = (num*10) + key - '0';

                   lcdClear(lcd_h);

                   lcdPosition(lcd_h, 0, 0);
                   lcdPrintf(lcd_h, "%.0f", num);
               }

               if (key == '*') {
                   num = 0;
                   result = false;

                   lcdClear(lcd_h);
                   lcdPosition(lcd_h, 0, 0);
                   lcdPrintf(lcd_h, "RESTART");

                   delay(2000);

                   lcdClear(lcd_h);

                   break;
               }

               if (key == '#') {
                   result = true;
               }

               if (key == 'A' || key == 'B' || key == 'C' || key == 'D') {
                   lcdPosition(lcd_h,0,0);
                   lcdPrintf(lcd_h,"Invalid");
                   lcdPosition(lcd_h, 0, 1);
                   lcdPrintf(lcd_h, "operation");
               }

               if (result == true) {
                   rez = sqrt(num);
                   lcdClear(lcd_h);
                   lcdPosition(lcd_h, 0, 0);
                   lcdPrintf(lcd_h, "koren iz %.0f", num);
                   lcdPosition(lcd_h, 0, 1);
                   lcdPrintf(lcd_h, "=%.2f", rez);

                   num = 0;
                   rez = 0;

                   result = false;
               }
            }
        }
     }
}


void Dialog::on_radioButton_4_clicked(bool checked)
{
    if(wiringPiSetup() == -1)
            exit(1);

    lcd_h = lcdInit (2, 16, 4, RS, EN, D0, D1, D2, D3, D0, D1, D2, D3);

    setupKeypad();

    float num1 = 0;
    float num2 = 0;
    float number = 0;
    bool result = false;
    float rez0 = 0;
    float rez = 0;
    char action;

     while(1) {

        if (checked) {
            char key = getKey();

            if (key != '\0') {
                if (key >= '0' && key <='9') {
                    if (number == 0)
                        number = key - '0';
                    else
                        number = (number*10) + key - '0';

                    lcdClear(lcd_h);

                    lcdPosition(lcd_h, 0, 0);
                    lcdPrintf(lcd_h, "%.0f", number);
                }

                if (key == '#') {
                    num2 = number;
                    result = true;
                    lcdPrintf(lcd_h, "=");
                }

                if (key == '*') {
                    number = 0;
                    num1 = 0;
                    num2 = 0;
                    result = false;

                    lcdClear(lcd_h);
                    lcdPosition(lcd_h, 0, 0);
                    lcdPrintf(lcd_h, "RESTART");

                    delay(2000);

                    lcdClear(lcd_h);

                    break;
                }

                if (key == 'A') {
                    num1 = number;
                    number = 0;
                    action = '+';
                    lcdPrintf(lcd_h, "i");
                }

                if (key == 'B' || key == 'C' || key == 'D') {
                    lcdPosition(lcd_h, 0, 0);
                    lcdPrintf(lcd_h,"Invalid");
                    lcdPosition(lcd_h, 0, 1);
                    lcdPrintf(lcd_h, "operation");
                }

                if (action == '+') rez0 = num1 + num2;

                if (key == '#') {
                    result = true;
                    rez = rez0 / 2;
                }


                if (result == true) {
                    //rez = rez0/2;
                    lcdPosition(lcd_h, 0, 0);
                    lcdPrintf(lcd_h, "Aritm. sredina");
                    lcdPosition(lcd_h, 0, 1);
                    lcdPrintf(lcd_h, "%.0f,%.0f=%.2f", num1, num2, rez);

                    number = 0;
                    num1 = 0;
                    num2 = 0;
                    result = false;

                }
            }
        }
    }

}
