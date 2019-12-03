#include <QDebug>
#include "qrcode_generator.h"

#ifdef Q_OS_WINDOWS
static const QString DLL_NAME("qrencode.dll");
QLibrary *QRCodeGenerator::m_qrencodelib = Q_NULLPTR;

extern "C"
{
    typedef QRcode* (*Func_QRcode_encodeString)(const char *string, int version, QRecLevel level, QRencodeMode hint, int casesensitive);
}
#endif

QRCodeGenerator::QRCodeGenerator(QObject *parent) : QObject(parent)
{

}

#ifdef Q_OS_WINDOWS
void QRCodeGenerator::Initialize()
{
    if (Q_NULLPTR == m_qrencodelib){
        m_qrencodelib = new QLibrary(DLL_NAME);
        bool loadResult = m_qrencodelib->load();

        if (true == loadResult){
            qDebug() << "QRCode_Generator:" << DLL_NAME << "load success.";
        }
        else{
            qDebug() << "QRCode_Generator:" << DLL_NAME << "load failure!!!";
        }
    }
}

void QRCodeGenerator::Deinitialize()
{
    if (m_qrencodelib != Q_NULLPTR){
        m_qrencodelib->unload();
        delete m_qrencodelib;
    }
}
#endif

bool QRCodeGenerator::GeneratePixmapFromText(QString &text, QPixmap &pixmap, int width, int height)
{
    bool result = false;
    if ((false == text.isEmpty())
            && (width == height)
            && (width > 0)
            && (height > 0)){
        QRcode *qrcode;
#ifdef Q_OS_WINDOWS
        if (m_qrencodelib != Q_NULLPTR){
            Func_QRcode_encodeString QRcode_encodeStringFunc = (Func_QRcode_encodeString)m_qrencodelib->resolve("QRcode_encodeString");
            if (!QRcode_encodeStringFunc)
            {
                qDebug("Can not get QRcode_encodeString() function pointer");
                return false;
            }
            qrcode = QRcode_encodeStringFunc(text.toUtf8().constData(), 0, QR_ECLEVEL_H, QR_MODE_8, 1);
        }
        else{
            qDebug("qrencode library pointer null !!! ");
            return false;
        }

#else
        qrcode = QRcode_encodeString(text.toUtf8().constData(), 0, QR_ECLEVEL_H, QR_MODE_8, 1);

#endif
        qint32 qrcode_width = qrcode->width > 0 ? qrcode->width : 1;
        double scale_x = static_cast<double>(width) / static_cast<double>(qrcode_width);
        double scale_y = static_cast<double>(height) / static_cast<double>(qrcode_width);
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

