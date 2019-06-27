#include "qrcode_generator.h"

QRCodeGenerator::QRCodeGenerator(QObject *parent) : QObject(parent)
{

}

bool QRCodeGenerator::GeneratePixmapFromText(QString &text, QPixmap &pixmap, int width, int height)
{
    bool result = false;
    if ((false == text.isEmpty())
            && (width == height)
            && (width > 0)
            && (height > 0)){
        QRcode *qrcode;
        qrcode = QRcode_encodeString(text.toUtf8().constData(), 0, QR_ECLEVEL_H, QR_MODE_8, 1);
        qint32 qrcode_width = qrcode->width > 0 ? qrcode->width : 1;
        double scale_x = (double)width / (double)qrcode_width;
        double scale_y =(double) height /(double) qrcode_width;
        QImage mainimg=QImage(width,height,QImage::Format_ARGB32);
        QPainter painter(&mainimg);
        QColor background(Qt::white);
        painter.setBrush(background);
        painter.setPen(Qt::NoPen);
        painter.drawRect(0, 0, width, height);
        QColor foreground(Qt::black);
        painter.setBrush(foreground);
        for( qint32 y = 0; y < qrcode_width; y ++)
        {
            for(qint32 x = 0; x < qrcode_width; x++)
            {
                unsigned char b = qrcode->data[y * qrcode_width + x];
                if(b & 0x01)
                {
                    QRectF r(x * scale_x, y * scale_y, scale_x, scale_y);
                    painter.drawRects(&r, 1);
                }
            }
        }
        pixmap = QPixmap::fromImage(mainimg);

        if (false == pixmap.isNull()){
            result = true;
        }
    }

    return result;
}

