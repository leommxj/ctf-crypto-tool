#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QClipboard>
#include <QInputDialog>
#include <QMessageBox>
#include <QStringList>
#include <QDebug>
#include "tools.h"

//解决中文乱码
//------------------------------------------
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
//------------------------------------------

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

void MainWindow::on_hexEncode_triggered()
{
    QString input =ui->inputEdit->toPlainText();
    QByteArray inputByte(input.toUtf8().toHex());
    ui->outputEdit->setText(inputByte);
}

void MainWindow::on_hexDecode_triggered()
{
    QString input =ui->inputEdit->toPlainText();
    QByteArray inputByte(QByteArray::fromHex(input.toUtf8()));
    ui->outputEdit->setText(inputByte);
}

void MainWindow::on_copyInput_clicked()
{
    QClipboard* clipboard = QApplication::clipboard();
    clipboard->setText(ui->inputEdit->toPlainText());
}

void MainWindow::on_copyOutput_clicked()
{
    QClipboard* clipboard = QApplication::clipboard();
    clipboard->setText(ui->outputEdit->toPlainText());
}

void MainWindow::on_exchangeIO_clicked()
{
    QString temp = ui->inputEdit->toPlainText();
    ui->inputEdit->setText(ui->outputEdit->toPlainText());
    ui->outputEdit->setText(temp);
}

void MainWindow::on_railDecode_triggered()
{
    bool isRail;
    QString rail = QInputDialog::getText(NULL,QString("分栏数"),"请输入单个数或范围(eg.3-5)",QLineEdit::Normal,"",&isRail);
    if(!isRail)return;
    QStringList railList = rail.split("-");
    int len = railList.length();
    QString input = ui->inputEdit->toPlainText();
    QString result;
    int inputLen = input.count();
    int rails_start,rails_end;
    if(len==1){
        rails_start = railList.at(0).toInt();
        rails_end = rails_start;

    }else if(len==2){
        rails_start = railList.at(0).toInt();
        rails_end = railList.at(1).toInt();
    }else{
        return;
    }
    for(int rails=rails_start;rails<=rails_end;rails++){
        result.append(QString().sprintf("分 %d 栏",rails));
        QStringList r;
        int lineLen = inputLen/rails;
        if(inputLen%rails!=0){
            lineLen+=1;
            result.append("(不对齐)");
        }
        result.append("时结果为：\n");
        qDebug()<<lineLen<<rails<<(lineLen%rails);
        for(int i=0;i<rails;i++){
            r.append(input.mid(i*lineLen,lineLen));
        }
        qDebug()<<"what?"<<r;
        for(int i=0;i<lineLen;i++){
            for(int j=0;j<rails;j++){
                qDebug()<<"shit"<<i<<","<<j;
                if(r.at(j).count()>i)
                result.append(r.at(j).at(i));
            }
        }
        result.append("\n");
    }
    ui->outputEdit->setText(result);

}


void MainWindow::on_classicalCaesarDecrypt_triggered()
{
    QString input = ui->inputEdit->toPlainText();
    QString result;
    Tools* tools = Tools::GetInstance();
    for(int i=1;i<=26;i++){
        result.append(tools->caesarDecode(input,i));
        result.append("\n");
    }
    ui->outputEdit->setText(result);
}

void MainWindow::on_vigenereDecrypt_triggered()
{
    Tools* tools = Tools::GetInstance();
    bool isKey;
    QString key = QInputDialog::getText(NULL,"请输入key","仅限26个英文字母 eg.caesar",QLineEdit::Normal,"",&isKey);
    QString result;
    QString input = ui->inputEdit->toPlainText();
    QString::iterator keyIt = key.begin();
    int i,upper=QChar('A').toLatin1(),lower=QChar('a').toLatin1();
    for(QString::iterator it = input.begin();it!=input.end();it++){

        if(keyIt==key.end())keyIt=key.begin();
        if(keyIt->isUpper())i=keyIt->toLatin1()-upper;
        else if(keyIt->isLower())i=keyIt->toLatin1()-lower;
        result.append(tools->caesarDecode(QString(it->unicode()),i));
        keyIt++;

    }
    ui->outputEdit->setText(result);
}
