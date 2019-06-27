#ifndef QRCODE_GENERATOR_H
#define QRCODE_GENERATOR_H

#include <QObject>
#include <QPainter>
#include "qrencode.h"

class QRCodeGenerator : public QObject
{
public:
    explicit QRCodeGenerator(QObject *parent = 0);

    static bool GeneratePixmapFromText(QString &text, QPixmap &pixmap, int width, int height);
signals:

public slots:
};

#endif // QRCODE_GENERATOR_H
