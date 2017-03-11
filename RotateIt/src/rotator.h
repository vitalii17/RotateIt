#ifndef ROTATOR_H
#define ROTATOR_H

#include <QObject>
#include <QImage>
#include "exiftools.h"

class Rotator : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal angle       READ angle       WRITE setAngle)
    Q_PROPERTY(bool  exifEnabled READ exifEnabled WRITE setExifEnabled)

public:

    explicit Rotator(QObject *parent = 0);

    static QImage rotate(QImage &image, qreal angle,
                         bool smoothPixmapTransformHint = false);

    qreal angle() const;
    void setAngle(qreal angle);

    void setQuality(int quality);
    int quality() const;

    void setOutputImagePath(QString &path);

    void setSpth(bool hint);
    bool spth() const;

    void setExifEnabled(bool exifEn);
    bool exifEnabled() const;

signals:

    void finished(QImage outputImage);
    void finished();

public slots:

    void process();
    void setInputImagePath(QString path);
    void setInputImage(QImage &image);
    void setPreviewImage(const QImage &arg);

private:

    qreal   m_angle;
    QImage  m_inputImage;
    QImage  m_previewImage;
    QString m_inputImagePath;
    QString m_outputImagePath;
    int     m_quality;
    bool    m_spth;
    bool    m_exifEnabled;
};

#endif // ROTATOR_H
