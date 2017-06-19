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
    // Image scales to a square with the side equal max value of width/height

    QImageReader imageReader(m_path);
    QSize originalSize(imageReader.size());

    if((originalSize.width() == 0) || (originalSize.height() == 0))
    {
        return;
    }

    int squareSide = (width() > height()) ? width() : height();

    QSize scaledSize(originalSize);
    scaledSize.scale(squareSide, squareSide, Qt::KeepAspectRatio);

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
