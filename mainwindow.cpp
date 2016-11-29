#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include "tools.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_textReverse_triggered()
{
    QString input = ui->inputEdit->toPlainText();
    QString output;
    for(QString::reverse_iterator it=input.rbegin();it!=input.rend();it++){
        output.append(it->unicode());
    }
    ui->outputEdit->setText(output);
}

void MainWindow::on_toUpper_triggered()
{
    QString input = ui->inputEdit->toPlainText();
    QString output;
    for(QString::iterator it=input.begin();it!=input.end();it++){
        output.append(it->toUpper());
    }
    ui->outputEdit->setText(output);
}

void MainWindow::on_toLower_triggered()
{
    QString input = ui->inputEdit->toPlainText();
    QString output;
    for(QString::iterator it=input.begin();it!=input.end();it++){
        output.append(it->toLower());
    }
    ui->outputEdit->setText(output);
}

void MainWindow::on_exchangeLowerUpper_triggered()
{
    QString input = ui->inputEdit->toPlainText();
    QString output;
    for(QString::iterator it=input.begin();it!=input.end();it++){
        if(it->isLower()){
            output.append(it->toUpper());
        }else if(it->isUpper()){
            output.append(it->toLower());
        }else{
            output.append(it->unicode());
        }
    }
    ui->outputEdit->setText(output);
}

void MainWindow::on_base64Encode_triggered()
{
    QString input = ui->inputEdit->toPlainText();
    QByteArray inputByte(input.toUtf8().toBase64());
    ui->outputEdit->setText(inputByte);
}

void MainWindow::on_base64Decode_triggered()
{
    QString input = ui->inputEdit->toPlainText();
    QByteArray inputByte(QByteArray::fromBase64(input.toUtf8()));
    ui->outputEdit->setText(inputByte);
}

void MainWindow::on_base32Encode_triggered()
{
    QString input = ui->inputEdit->toPlainText();
    Tools* tools = Tools::GetInstance();
    ui->outputEdit->setText(tools->base32encode(input));
}

void MainWindow::on_base32Decode_triggered()
{
    QString input = ui->inputEdit->toPlainText();
    Tools* tools = Tools::GetInstance();
    ui->outputEdit->setText(tools->base32decode(input));
}
