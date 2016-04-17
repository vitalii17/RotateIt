#include "engine.h"

#include <QDebug>
#include <QPainter>
#include <qmath.h>

Engine::Engine(QObject *parent) :
    QObject(parent)
{

}

void Engine::rotate(qreal angle)
{
    if(!m_imagePath.isEmpty())
    {
        qreal angle_rad = qAbs((M_PI / 180) * angle);
        qreal cos_angle = qCos(angle_rad);
        qreal sin_angle = qSin(angle_rad);
        qreal cos_2angle = qCos(2 * angle_rad);

        int cut_width = (m_previewImage.width() * cos_angle -
                         m_previewImage.height() * sin_angle) / cos_2angle;

        int cut_height = (m_previewImage.height() * cos_angle -
                          m_previewImage.width() * sin_angle) / cos_2angle;

        QRect cutRect(m_previewImage.width() / 2 - cut_width / 2,
                  m_previewImage.height() / 2 - cut_height / 2,
                  cut_width - 1, cut_height - 1);

        QPainter painter(&m_previewImage);
        //painter->setRenderHint(QPainter::Antialiasing);
        painter.setRenderHint(QPainter::SmoothPixmapTransform);
        //painter->setRenderHint(QPainter::HighQualityAntialiasing);
        painter.translate(m_previewImage.width()/2, m_previewImage.height()/2);
        painter.rotate(angle);
        painter.translate(-m_previewImage.width()/2, -m_previewImage.height()/2);
        painter.drawImage(0, 0, m_inputPreviewImage);
        painter.end();

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

QString Engine::imagePath() const
{
    return m_imagePath;
}

void Engine::setImagePath(QString arg)
{
    m_imagePath = arg;

    if(!m_imagePath.isEmpty())
    {
        //setPreviewImage(QImage(imagePath()).scaled(previewWidth(),
          //                                         previewHeight(),
            //                                       Qt::KeepAspectRatio).convertToFormat(QImage::Format_ARGB32_Premultiplied));

        QThread *thread = new QThread();
        Resizer *resizer = new Resizer();
        resizer->moveToThread(thread);
        resizer->setInputImage(imagePath());

        connect(thread, SIGNAL(started()), resizer, SLOT(process()));
        connect(resizer, SIGNAL(finished(QImage)), this, SLOT(setPreviewImage(QImage)));
        connect(resizer, SIGNAL(finished()), thread, SLOT(quit()));
        connect(resizer, SIGNAL(finished()), resizer, SLOT(deleteLater()));
        connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
        thread->start();
        thread->setPriority(QThread::LowPriority);

        m_inputPreviewImage = previewImage();
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
}


// Resizer

Resizer::Resizer(QObject *parent) : QObject(parent)
{

}

void Resizer::process()
{
    m_outputImage = QImage(m_path).scaled(640, 360, Qt::KeepAspectRatio);
    emit finished();
    emit finished(m_outputImage);
}

void Resizer::setInputImage(QString path)
{
    m_path = path;
}



