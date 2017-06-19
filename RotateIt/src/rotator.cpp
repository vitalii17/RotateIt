#include "rotator.h"
#include <qmath.h>
#include <QPainter>
#include <QDir>
#include <QDebug>

Rotator::Rotator(QObject *parent) : QObject(parent), m_angle(0), m_exifEnabled(false)
{

}

QImage Rotator::rotate(QImage &image, qreal angle,
                      bool smoothPixmapTransformHint)
{
    QImage resultImage;
    if(!image.isNull())
    {
        //Source https://rsdn.org/forum/alg/3797164.all
        //With my optimizations
        qreal angle_rad = qAbs((M_PI / 180) * angle);
        qreal cos_angle = qCos(angle_rad);
        qreal sin_angle = qSin(angle_rad);
        qreal cos_2angle = qCos(2 * angle_rad);

        int cut_width  = 0;
        int cut_height = 0;

        if((angle >= 90) && (angle < 180))
        {
            angle_rad = qAbs((M_PI / 180) * (angle - 90));
            cos_angle = qCos(angle_rad);
            sin_angle = qSin(angle_rad);
            cos_2angle = qCos(2 * angle_rad);

            cut_width = static_cast<int>(
                        (image.height() * cos_angle -
                         image.width() * sin_angle) / cos_2angle);

            cut_height = static_cast<int>(
                        (image.width() * cos_angle -
                         image.height() * sin_angle) / cos_2angle);
        }
        else if((angle >= -180) && (angle < -90))
        {
            angle_rad = qAbs((M_PI / 180) * (angle + 90));
            cos_angle = qCos(angle_rad);
            sin_angle = qSin(angle_rad);
            cos_2angle = qCos(2 * angle_rad);

            cut_width = static_cast<int>(
                        (image.height() * cos_angle -
                         image.width() * sin_angle) / cos_2angle);

            cut_height = static_cast<int>(
                        (image.width() * cos_angle -
                         image.height() * sin_angle) / cos_2angle);
        }
        else if((angle >= 180) && (angle < 270))
        {
            angle_rad = qAbs((M_PI / 180) * (angle - 180));
            cos_angle = qCos(angle_rad);
            sin_angle = qSin(angle_rad);
            cos_2angle = qCos(2 * angle_rad);

            cut_width = static_cast<int>(
                        (image.width() * cos_angle -
                         image.height() * sin_angle) / cos_2angle);

            cut_height = static_cast<int>(
                        (image.height() * cos_angle -
                         image.width() * sin_angle) / cos_2angle);
        }
        else if((angle >= -270) && (angle < -180))
        {
            angle_rad = qAbs((M_PI / 180) * (angle + 180));
            cos_angle = qCos(angle_rad);
            sin_angle = qSin(angle_rad);
            cos_2angle = qCos(2 * angle_rad);

            cut_width = static_cast<int>(
                        (image.width() * cos_angle -
                         image.height() * sin_angle) / cos_2angle);

            cut_height = static_cast<int>(
                        (image.height() * cos_angle -
                         image.width() * sin_angle) / cos_2angle);
        }
        else if((angle >= 270) && (angle < 360))
        {
            angle_rad = qAbs((M_PI / 180) * (angle - 270));
            cos_angle = qCos(angle_rad);
            sin_angle = qSin(angle_rad);
            cos_2angle = qCos(2 * angle_rad);

            cut_width = static_cast<int>(
                        (image.height() * cos_angle -
                         image.width() * sin_angle) / cos_2angle);

            cut_height = static_cast<int>(
                        (image.width() * cos_angle -
                         image.height() * sin_angle) / cos_2angle);
        }
        else if((angle >= -360) && (angle < -270))
        {
            angle_rad = qAbs((M_PI / 180) * (angle + 270));
            cos_angle = qCos(angle_rad);
            sin_angle = qSin(angle_rad);
            cos_2angle = qCos(2 * angle_rad);

            cut_width = static_cast<int>(
                        (image.height() * cos_angle -
                         image.width() * sin_angle) / cos_2angle);

            cut_height = static_cast<int>(
                        (image.width() * cos_angle -
                         image.height() * sin_angle) / cos_2angle);
        }
        else
        {
            cut_width = static_cast<int>(
                        (image.width() * cos_angle -
                         image.height() * sin_angle) / cos_2angle);

            cut_height = static_cast<int>(
                        (image.height() * cos_angle -
                         image.width() * sin_angle) / cos_2angle);
        }

        if(cut_width <= 1)
        {
            cut_width = 1;
        }
        if(cut_height <= 1)
        {
            cut_height = 1;
        }

        QRect cutRect(image.width() / 2 - cut_width / 2,
                      image.height() / 2 - cut_height / 2,
                      cut_width, cut_height);

        resultImage = QImage(cutRect.size(), QImage::Format_ARGB32_Premultiplied);

        QPainter painter(&resultImage);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setRenderHint(QPainter::SmoothPixmapTransform,
                              smoothPixmapTransformHint);
        painter.setRenderHint(QPainter::HighQualityAntialiasing);
        painter.translate(resultImage.width() / 2, resultImage.height() / 2);
        painter.rotate(angle);
        painter.translate(-resultImage.width() / 2, -resultImage.height() / 2);
        painter.translate(QPoint(cut_width / 2 - image.width() / 2,
                                 cut_height / 2 - image.height() / 2));
        painter.drawImage(0, 0, image);
    }
    return resultImage;
}

qreal Rotator::angle() const
{
    return m_angle;
}

void Rotator::setAngle(qreal angle)
{
    if(m_angle != angle)
    {
        m_angle = angle;
    }
}

int Rotator::quality() const
{
    return m_quality;
}

void Rotator::setOutputImagePath(QString &path)
{
    m_outputImagePath = path;
}

void Rotator::setSpth(bool hint)
{
    m_spth = hint;
}

bool Rotator::spth() const
{
    return m_spth;
}

void Rotator::setExifEnabled(bool exifEn)
{
    if(m_exifEnabled != exifEn)
    {
        m_exifEnabled = exifEn;
    }
}

bool Rotator::exifEnabled() const
{
    return m_exifEnabled;
}

void Rotator::setQuality(int quality)
{
    if(m_quality != quality)
    {
        m_quality = quality;
    }
}

void Rotator::process()
{
    if(!m_inputImagePath.isEmpty())
    {
        QImage image = QImage(m_inputImagePath).
                convertToFormat(QImage::Format_ARGB32_Premultiplied);

        image = rotate(image, angle(), spth());

        bool saveReturnCode;
        saveReturnCode = image.save(m_outputImagePath, 0, quality());

        if(saveReturnCode)
        {   
            if(m_exifEnabled)
            {
                try
                {
                    ExifTools::copyExif(m_inputImagePath, m_outputImagePath);
                }
                catch(Exiv2::Error &error)
                {
                    qDebug() << "Error! Exception in Exiv2: code" << error.code();
                    qDebug() << "Error! Exception in Exiv2: what" << error.what();
                }
            }
        }
        else{}
    }
    emit finished();
}

void Rotator::setInputImagePath(QString path)
{
    m_inputImagePath = path;
}

void Rotator::setInputImage(QImage &image)
{
    m_inputImage = image;
}

void Rotator::setPreviewImage(const QImage &arg)
{
    m_previewImage = arg;
}
