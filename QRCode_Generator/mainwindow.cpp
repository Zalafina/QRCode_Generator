#include "mainwindow.h"
#include "ui_mainwindow.h"

static const QString SAVE_TO_PNG(QString("Save imagefile to\nQRCode.png"));
static const QString SAVE_TO_JPG(QString("Save imagefile to\nQRCode.jpg"));
static const QString SAVE_TO_BMP(QString("Save imagefile to\nQRCode.bmp"));

MainWindow::MainWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->label->setScaledContents(true);
    if ((ui->label->pixmap() != NULL)
            && (ui->label->pixmap()->isNull() != true)){
        ui->saveFileButton->setEnabled(true);
    }
    else{
        ui->saveFileButton->setEnabled(false);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_generateButton_pressed()
{
    bool image_loadfailure = false;
    bool invalid_qrimage = false;

    QByteArray tempstring = ui->lineEdit->text().toLatin1().constData();
    //qDebug("InputString : %s", tempstring.constData());

    QRController* controller = new QRController(tempstring.constData(), eclMedium, 250, 250, evAuto);

    vector<char> tempBitmapArray;
    bool result;
    result = controller->SaveToByteArray(tempBitmapArray);

    if (true == result){
        QByteArray tempQArray(tempBitmapArray.data(), tempBitmapArray.size());

        QPixmap QRCodeBitmap;
        bool loadresult = false;
        loadresult = QRCodeBitmap.loadFromData(tempQArray, "BMP");

        if (true == loadresult){
            //qDebug("QRCodeImage Load Complete.");

            ui->label->setPixmap(QRCodeBitmap);
        }
        else{
            image_loadfailure = true;
            //QMessageBox::warning(this, tr("QRCode_Generator"), tr("QRCodeImage Load Failure."));
            //qDebug("QRCodeImage Load Failed!!!");
        }
    }
    else{
        invalid_qrimage = true;
        ui->label->setPixmap(QPixmap());
        //QMessageBox::warning(this, tr("QRCode_Generator"), tr("Invalid QRCodeImage."));
    }

    if ((ui->label->pixmap() != NULL)
            && (ui->label->pixmap()->isNull() != true)){
        ui->saveFileButton->setEnabled(true);
    }
    else{
        ui->saveFileButton->setEnabled(false);
    }

    delete controller;

    if (true == image_loadfailure){
        QMessageBox::warning(this, tr("QRCode_Generator"), tr("QRCodeImage Load Failure."));
    }
    else if (true == invalid_qrimage){
        QMessageBox::warning(this, tr("QRCode_Generator"), tr("Invalid QRCodeImage."));
    }
    else{
        // do nothing.
    }
}

void MainWindow::on_saveFileButton_pressed()
{
    QByteArray tempstring = ui->lineEdit->text().toLatin1().constData();

    QRController* controller = new QRController(tempstring.constData(), eclMedium, 250, 250, evAuto);

    vector<char> tempBitmapArray;
    controller->SaveToByteArray(tempBitmapArray);
    QByteArray tempQArray(tempBitmapArray.data(), tempBitmapArray.size());

    QPixmap QRCodeBitmap;
    bool loadresult = false;
    loadresult = QRCodeBitmap.loadFromData(tempQArray, "BMP");

    if (true == loadresult){
        //qDebug("QRCodeImage Load Complete.");

        ui->label->setPixmap(QRCodeBitmap);

        QString imageType = ui->comboBox->currentText();

        QString filetypeStr;
        if (imageType == QString("BMP")){
            filetypeStr = QString(".bmp");
        }
        else if (imageType == QString("JPG")){
            filetypeStr = QString(".jpg");
        }
        else if (imageType == QString("PNG")){
            filetypeStr = QString(".png");
        }
        else{
            filetypeStr = QString(".bmp");
        }

        bool saveResult;
        QString savefileName = QString("QRCode") + filetypeStr;
        saveResult = QRCodeBitmap.save(savefileName);

        if (true == saveResult){
            qDebug().nospace().noquote() << "Save QRCode to " << imageType << " file success.";
        }
        else{
            qDebug().nospace().noquote() << "Save QRCode to " << imageType << " file failure.";
        }
    }
    else{
        //qDebug("QRCodeImage Load Failed!!!");
    }

    delete controller;
}

void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    QString savetofile_buttonStr;

    QString filetypeStr;
    if (arg1 == QString("BMP")){
        savetofile_buttonStr = SAVE_TO_BMP;
    }
    else if (arg1 == QString("JPG")){
        savetofile_buttonStr = SAVE_TO_JPG;
    }
    else if (arg1 == QString("PNG")){
        savetofile_buttonStr = SAVE_TO_PNG;
    }
    else{
        savetofile_buttonStr = SAVE_TO_PNG;
    }

    ui->saveFileButton->setText(savetofile_buttonStr);
}
