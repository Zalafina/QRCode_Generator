#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QDialog>
#include "QRController.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_generateButton_pressed();

    void on_saveFileButton_pressed();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
