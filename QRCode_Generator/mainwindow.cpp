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

    //ui->qrcodepixmapLabel->setScaledContents(true);
    if ((ui->qrcodepixmapLabel->pixmap() != NULL)
            && (ui->qrcodepixmapLabel->pixmap()->isNull() != true)){
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

    int qrcode_width = ui->qrcodepixmapLabel->width();
    int qrcode_height = ui->qrcodepixmapLabel->height();
    QRController* controller = new QRController(ui->lineEdit->text().toUtf8().constData(), eclMedium, qrcode_width, qrcode_height, evAuto);
    int suitablepixlength = 0;
    bool checkresult = controller->getSuitablePixLength(suitablepixlength);
    if (true == checkresult){
        delete controller;
        controller = new QRController(ui->lineEdit->text().toUtf8().constData(), eclMedium, suitablepixlength, suitablepixlength, evAuto);
#ifdef DEBUG_LOGOUT_ON
        qDebug("Resize QRCode pixlength from (%d) to (%d)", qrcode_width, suitablepixlength);
#endif
    }
    else{
        qDebug("Resize QRCode to suitablepixlength failure!!!");
    }

    vector<char> tempBitmapArray;
    bool result;
    result = controller->SaveToByteArray(tempBitmapArray);

    if (true == result){
        QByteArray tempQArray(tempBitmapArray.data(), tempBitmapArray.size());

        QPixmap QRCodeBitmap;
        bool loadresult = false;
        loadresult = QRCodeBitmap.loadFromData(tempQArray, "BMP");

        if (true == loadresult){
#ifdef DEBUG_LOGOUT_ON
            qDebug("QRCodeImage width(%d) height(%d) Load Complete.", QRCodeBitmap.width(), QRCodeBitmap.height());
#endif

            ui->qrcodepixmapLabel->setPixmap(QRCodeBitmap);
        }
        else{
            image_loadfailure = true;
            //QMessageBox::warning(this, tr("QRCode Generator"), tr("QRCodeImage Load Failure."));
            //qDebug("QRCodeImage Load Failed!!!");
        }
    }
    else{
        invalid_qrimage = true;
        ui->qrcodepixmapLabel->setPixmap(QPixmap());
        //QMessageBox::warning(this, tr("QRCode Generator"), tr("Invalid QRCodeImage."));
    }

    if ((ui->qrcodepixmapLabel->pixmap() != NULL)
            && (ui->qrcodepixmapLabel->pixmap()->isNull() != true)){
        ui->saveFileButton->setEnabled(true);
    }
    else{
        ui->saveFileButton->setEnabled(false);
    }

    delete controller;

    if (true == image_loadfailure){
        QMessageBox::warning(this, tr("QRCode Generator"), tr("QRCodeImage Load Failure."));
    }
    else if (true == invalid_qrimage){
        QMessageBox::warning(this, tr("QRCode Generator"), tr("Invalid QRCodeImage."));
    }
    else{
        // do nothing.
    }
}

void MainWindow::on_saveFileButton_pressed()
{
#if 0
    QByteArray tempstring = ui->lineEdit->text().toLatin1().constData();

    QRController* controller = new QRController(tempstring.constData(), eclMedium, 250, 250, evAuto);

    vector<char> tempBitmapArray;
    controller->SaveToByteArray(tempBitmapArray);
    QByteArray tempQArray(tempBitmapArray.data(), tempBitmapArray.size());

    QPixmap QRCodeBitmap;
    bool loadresult = false;
    loadresult = QRCodeBitmap.loadFromData(tempQArray, "BMP");

    delete controller;

    if (true == loadresult){
        //qDebug("QRCodeImage Load Complete.");

        ui->qrcodepixmapLabel->setPixmap(QRCodeBitmap);

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
            QMessageBox::information(this, tr("QRCode Generator"), QString("Save to ") + savefileName + QString(" success"));

#ifdef DEBUG_LOGOUT_ON
            qDebug().nospace().noquote() << "Save QRCode to " << imageType << " file success.";
#endif
        }
        else{
            QMessageBox::warning(this, tr("QRCode Generator"), QString("Save to ") + savefileName + QString(" failure"));

#ifdef DEBUG_LOGOUT_ON
            qDebug().nospace().noquote() << "Save QRCode to " << imageType << " file failure.";
#endif
        }
    }
    else{
        QMessageBox::warning(this, tr("QRCode Generator"), tr("QRCodeImage Load Failure!!!"));
        //qDebug("QRCodeImage Load Failed!!!");
    }
#else
    if ((ui->qrcodepixmapLabel->pixmap() != NULL)
            && (ui->qrcodepixmapLabel->pixmap()->isNull() != true)){
        const QPixmap *QRCodePixmap = ui->qrcodepixmapLabel->pixmap();

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
        saveResult = QRCodePixmap->save(savefileName);

        if (true == saveResult){
            QMessageBox::information(this, tr("QRCode Generator"), QString("Save to ") + savefileName + QString(" success"));
        }
        else{
            QMessageBox::warning(this, tr("QRCode Generator"), QString("Save to ") + savefileName + QString(" failure"));
        }
    }
    else{
        QMessageBox::warning(this, tr("QRCode Generator"), tr("Invalid QRCode Image"));
    }
#endif

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
