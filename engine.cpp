#include <QDebug>
#include <QPainter>
#include <qmath.h>

#include <QTime>  // For performance measurement

#include "engine.h"

Engine::Engine(QObject *parent) :
    QObject(parent)
{

}

void Engine::rotate(qreal angle)
{
//    if((state() == Engine::Passive) && (!m_inputPreviewImage.isNull()))
//    {
//        setState(Engine::Processing);
//        QThread *thread = new QThread();
//        Rotate *rotator = new Rotate();
//        rotator->setInputImage(m_inputPreviewImage);
//        rotator->setAngle(angle);
//        connect(thread, SIGNAL(started()), rotator, SLOT(process()));
//        connect(rotator, SIGNAL(finished(QImage)), this, SLOT(setPreviewImage(QImage)));
//        connect(rotator, SIGNAL(finished()), thread, SLOT(quit()));
//        connect(rotator, SIGNAL(finished()), rotator, SLOT(deleteLater()));
//        connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
//        connect(thread, SIGNAL(finished()), this, SLOT(resetState()));
//        thread->start();
//    }
//    else if(state() == Engine::FinalRendering)
//    {

//    }

    if(!m_previewImage.isNull())
    {
        //Source https://rsdn.ru/forum/alg/3797164.all
        //With my optimizations
        qreal angle_rad = qAbs((M_PI / 180) * angle);
        qreal cos_angle = qCos(angle_rad);
        qreal sin_angle = qSin(angle_rad);
        qreal cos_2angle = qCos(2 * angle_rad);

        int cut_width = static_cast<int>(
                    (m_inputPreviewImage.width() * cos_angle -
                     m_inputPreviewImage.height() * sin_angle) / cos_2angle);

        int cut_height = static_cast<int>(
                    (m_inputPreviewImage.height() * cos_angle -
                     m_inputPreviewImage.width() * sin_angle) / cos_2angle);

        if(cut_width <= 1)
        {
            cut_width = 1;
        }
        if(cut_height <= 1)
        {
            cut_height = 1;
        }

        QRect cutRect(m_inputPreviewImage.width() / 2 - cut_width / 2,
                      m_inputPreviewImage.height() / 2 - cut_height / 2,
                      cut_width, cut_height);

        m_previewImage = QImage(cutRect.size(), QImage::Format_ARGB32_Premultiplied);

        QPainter painter(&m_previewImage);

        painter.setRenderHint(QPainter::Antialiasing);
//        painter.setRenderHint(QPainter::SmoothPixmapTransform);
        painter.setRenderHint(QPainter::HighQualityAntialiasing);
        painter.translate(m_previewImage.width() / 2, m_previewImage.height() / 2);
        painter.rotate(angle);
        painter.translate(-m_previewImage.width() / 2, -m_previewImage.height() / 2);
        painter.translate(QPoint(cut_width / 2 - m_inputPreviewImage.width() / 2,
                                 cut_height / 2 - m_inputPreviewImage.height() / 2));
        painter.drawImage(0, 0, m_inputPreviewImage);

        emit previewImageChanged();
    }
}

QImage Engine::previewImage() const
{
    return m_previewImage;
}

void Engine::setPreviewImage(QImage arg)
{
    m_previewImage = arg;
    emit previewImageChanged();
}

void Engine::setInputPreviewImage(QImage arg)
{
    m_inputPreviewImage = arg;
}

QString Engine::imagePath() const
{
    return m_imagePath;
}

void Engine::setImagePath(QString arg)
{
    m_imagePath = arg;

    if(!m_imagePath.isEmpty())
    {
        setState(Engine::Processing);
        QThread *thread = new QThread();
        Resize *resizer = new Resize();
        resizer->moveToThread(thread);
        resizer->setInputImagePath(imagePath());
        resizer->setWidth(previewWidth());
        resizer->setHeight(previewHeight());

        connect(thread, SIGNAL(started()), resizer, SLOT(process()));
        connect(resizer, SIGNAL(finished(QImage)), this, SLOT(setPreviewImage(QImage)));
        connect(resizer, SIGNAL(finished(QImage)), this, SLOT(setInputPreviewImage(QImage)));
        connect(resizer, SIGNAL(finished()), thread, SLOT(quit()));
        connect(resizer, SIGNAL(finished()), resizer, SLOT(deleteLater()));
        connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
        connect(thread, SIGNAL(finished()), this, SLOT(resetState()));
        thread->start();
        thread->setPriority(QThread::LowPriority);
    }

    emit imagePathChanged();
}

int Engine::previewWidth() const
{
    return m_previewWidth;
}

void Engine::setPreviewWidth(int arg)
{
    m_previewWidth = arg;
    emit previewWidthChanged();
}

int Engine::previewHeight() const
{
    return m_previewHeight;
}

void Engine::setPreviewHeight(int arg)
{
    m_previewHeight = arg;
    emit previewHeightChanged();
}

qreal Engine::rotation() const
{
    return m_rotation;
}

void Engine::setRotation(qreal arg)
{
    m_rotation = arg;
    emit rotationChanged();
    rotate(arg);
}

Engine::EngineState Engine::state() const
{
    return m_state;
}

void Engine::setState(Engine::EngineState arg)
{
    m_state = arg;
    emit stateChanged();
}

void Engine::resetState()
{
    m_state = Engine::Passive;
    emit stateChanged();
}


// Resizer

Resize::Resize(QObject *parent) : QObject(parent)
{

}

int Resize::width() const
{
    return m_width;
}

int Resize::height() const
{
    return m_height;
}

void Resize::process()
{
    m_outputImage = QImage(m_path).
            scaled(width(), height(), Qt::KeepAspectRatioByExpanding).
            convertToFormat(QImage::Format_ARGB32_Premultiplied);

    emit finished();
    emit finished(m_outputImage);
}

void Resize::setInputImagePath(QString path)
{
    m_path = path;
}

void Resize::setWidth(int arg)
{
    m_width = arg;
}

void Resize::setHeight(int arg)
{
    m_height = arg;
}


// Rotate

Rotate::Rotate(QObject *parent) : QObject(parent), m_angle(0)
{

}

QImage Rotate::rotate(QImage &image, qreal angle)
{
    return image;
}

qreal Rotate::angle() const
{
    return m_angle;
}

void Rotate::setAngle(qreal value)
{
    m_angle = value;
}

void Rotate::process()
{
    if(!m_inputImage.isNull())
    {
        QImage resultImage(m_inputImage.width(),
                           m_inputImage.height(),
                           QImage::Format_ARGB32_Premultiplied);
        QPainter painter(&resultImage);
        //painter->setRenderHint(QPainter::Antialiasing);
        painter.setRenderHint(QPainter::SmoothPixmapTransform);
        //painter->setRenderHint(QPainter::HighQualityAntialiasing);
        painter.translate(m_inputImage.width()/2, m_inputImage.height()/2);
        painter.rotate(m_angle);
        painter.translate(-m_inputImage.width()/2, -m_inputImage.height()/2);
        painter.drawImage(0, 0, m_inputImage);
        painter.end();
        emit finished(resultImage);
    }
    emit finished();
}

void Rotate::setInputImagePath(QString path)
{
    m_path = path;
}

void Rotate::setInputImage(QImage &image)
{
    m_inputImage = image;
}


