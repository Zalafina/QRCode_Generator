#ifndef QRCODE_GENERATOR_H
#define QRCODE_GENERATOR_H

#include <QObject>
#include <QPainter>
#ifdef Q_OS_WINDOWS
#include <QLibrary>
#endif
#include "qrencode.h"

class QRCodeGenerator : public QObject
{
public:
    explicit QRCodeGenerator(QObject *parent = 0);

#ifdef Q_OS_WINDOWS
    static void Initialize();
    static void Deinitialize();
#endif
    static bool GeneratePixmapFromText(QString &text, QPixmap &pixmap,
                                       int width, int height);
signals:

public slots:
private:
#ifdef Q_OS_WINDOWS
    static QLibrary *m_qrencodelib;
#endif
};

#endif // QRCODE_GENERATOR_H

