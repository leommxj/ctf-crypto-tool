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

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
