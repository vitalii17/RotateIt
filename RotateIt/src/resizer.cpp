#include "resizer.h"

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
    m_outputImage = QImage(m_path).
            scaled(width(), height(), Qt::KeepAspectRatio).
            convertToFormat(QImage::Format_ARGB32_Premultiplied);
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
