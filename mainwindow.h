#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_textReverse_triggered();

    void on_toUpper_triggered();

    void on_toLower_triggered();

    void on_exchangeLowerUpper_triggered();

    void on_base64Encode_triggered();

    void on_base64Decode_triggered();

    void on_base32Encode_triggered();

    void on_base32Decode_triggered();

    void on_hexEncode_triggered();

    void on_hexDecode_triggered();

    void on_copyInput_clicked();

    void on_copyOutput_clicked();

    void on_exchangeIO_clicked();

    void on_railDecode_triggered();

    void on_classicalCaesarDecrypt_triggered();

    void on_vigenereDecrypt_triggered();

    void on_delSpace_triggered();

    void on_URLencode_triggered();

    void on_URLdecode_triggered();

    void on_baconDecodeAB_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
