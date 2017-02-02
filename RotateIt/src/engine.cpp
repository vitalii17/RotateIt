#include <QDebug>
#include <QPainter>
#include <qmath.h>

#include <QElapsedTimer> // For performance measurement
#include <QTime>

#include "engine.h"
#include "rotator.h"

Engine::Engine(QObject *parent) :
    QObject(parent), m_rotation(0), m_smoothPixmapTransformHint(false),
    m_privateOpeningState(false), m_privateSavingState(false)
{

}

void Engine::rotate(qreal angle)
{
    if(!m_previewImage.isNull())
    {
        m_previewImage = Rotator::rotate(m_inputPreviewImage, angle,
                                        smoothPixmapTransformHint());
        emit previewImageChanged();
    }
}

QImage Engine::previewImage() const
{
    return m_previewImage;
}

void Engine::setPreviewImage(const QImage arg)
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
        setState(Engine::Processing, Engine::Opening);
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
        connect(thread, SIGNAL(finished()), this, SLOT(resetPrivateOpeningState()));
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

bool Engine::smoothPixmapTransformHint() const
{
    return m_smoothPixmapTransformHint;
}

void Engine::setSmoothPixmapTransformHint(bool hint)
{
    m_smoothPixmapTransformHint = hint;
}

Engine::EngineState Engine::state() const
{
    return m_state;
}

void Engine::save(int quality)
{
    if(!imagePath().isEmpty())
    {
        setState(Engine::Processing, Engine::Saving);

        QString outputPath = imagePath().
                insert(imagePath().lastIndexOf("."), "_rotated(" +
                       QTime::currentTime().toString("mmss") + ")");

        QThread *thread = new QThread();
        Rotator *rotator = new Rotator();
        rotator->moveToThread(thread);
        rotator->setInputImagePath(imagePath());
        rotator->setAngle(rotation());
        rotator->setQuality(quality);
        rotator->setOutputImagePath(outputPath);
        rotator->setSpth(smoothPixmapTransformHint());

        connect(thread, SIGNAL(started()), rotator, SLOT(process()));
        connect(rotator, SIGNAL(finished()), thread, SLOT(quit()));
        connect(rotator, SIGNAL(finished()), rotator, SLOT(deleteLater()));
        connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
        connect(thread, SIGNAL(finished()), this, SLOT(resetPrivateSavingState()));
        connect(thread , SIGNAL(finished()), this, SIGNAL(savingFinished()));
        thread->start();
        thread->setPriority(QThread::LowPriority);
    }
}

void Engine::setState(Engine::EngineState arg, Engine::PrivateEngineState privateState)
{
    m_state = arg;

    switch(privateState)
    {
    case Engine::Opening:
        m_privateOpeningState = true;
        break;

    case Engine::Saving:
        m_privateSavingState = true;
        break;

    default:
        break;
    }

    emit stateChanged();
}

void Engine::resetState()
{
    if((!m_privateOpeningState) && (!m_privateSavingState))
    {
        m_state = Engine::Passive;
        emit stateChanged();
    }
}

void Engine::resetPrivateOpeningState()
{
    m_privateOpeningState = false;
    resetState();
}

void Engine::resetPrivateSavingState()
{
    m_privateSavingState = false;
    resetState();
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
            scaled(width(), height(), Qt::KeepAspectRatio).
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



