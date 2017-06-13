#include "resizer.h"

#include <QImageReader>

#include <QDebug>

Resizer::Resizer(QObject *parent) : QObject(parent)
{

}

int Resizer::width() const
{
    return m_width;
}

int Resizer::height() const
{
    return m_height;
}

void Resizer::process()
{
    QImageReader imageReader(m_path);

    QSize originalSize(imageReader.size());
    QSize scaledSize = originalSize;

    if((originalSize.width() || originalSize.height()) == 0)
    {
        return;
    }

//    qDebug() << "!!!!!!!!!" << originalSize.width() / width() <<
//                originalSize.height() / height();

    // Source form coefficient
    double kfs = static_cast<double>(originalSize.width()) /
                 static_cast<double>(originalSize.height());

    // Destination form coefficient
    double kfd = static_cast<double>(width()) /
                 static_cast<double>(height());

    double scaleFactor = 1.0;

    if(kfs > kfd)
    {
        scaleFactor = static_cast<double>(width()) /
                static_cast<double>(originalSize.width());
        scaledSize.setWidth(width());
        scaledSize.setHeight(originalSize.height() * scaleFactor);
        //qDebug() << "kfs > kfd";
    }
    else
    {
        scaleFactor = static_cast<double>(height()) /
                static_cast<double>(originalSize.height());
        scaledSize.setWidth(originalSize.width() * scaleFactor);
        scaledSize.setHeight(height());
        //qDebug() << "kfs < kfd";
    }

//    qDebug() << "Original size: " << originalSize;
//    qDebug() << "Scaled size: " << scaledSize;
//    qDebug() << "kfs =" << kfs;
//    qDebug() << "kfd =" << kfd;

    imageReader.setScaledSize(scaledSize);
    imageReader.read(&m_outputImage);

    m_outputImage = m_outputImage.convertToFormat(QImage::Format_ARGB32_Premultiplied);

    emit finished();
    emit finished(m_outputImage);
}

void Resizer::setInputImagePath(QString path)
{
    m_path = path;
}

void Resizer::setWidth(int width)
{
    if(m_width != width)
    {
        m_width = width;
    }
}

void Resizer::setHeight(int height)
{
    if(m_height != height)
    {
        m_height = height;
    }
}
