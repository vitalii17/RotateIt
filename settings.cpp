#include <QDebug>

#include "settings.h"

Settings::Settings(QObject *parent) :
    QObject(parent), m_pSettings(new QSettings)
{
    m_spthPreview      = m_pSettings->value("SmoothPixmapTransformHintPreview", false).toBool();
    m_quality          = m_pSettings->value("Quality", 96).toInt();
    m_isDefaultQuality = m_pSettings->value("IsDefaultQuality", true).toBool();
    m_vibraOn          = m_pSettings->value("VibraOn", true).toBool();
    m_landscapeMode    = m_pSettings->value("LandscapeMode", false).toBool();
}

Settings::~Settings()
{
    if(m_spthPreview != m_pSettings->value("SmoothPixmapTransformHintPreview").toBool())
    {
        m_pSettings->setValue("SmoothPixmapTransformHintPreview", m_spthPreview);
    }

    if(m_quality != m_pSettings->value("Quality", 96).toInt())
    {
        m_pSettings->setValue("Quality", m_quality);
    }

    if(m_isDefaultQuality != m_pSettings->value("IsDefaultQuality", true).toBool())
    {
        m_pSettings->setValue("IsDefaultQuality", m_isDefaultQuality);
    }

    if(m_vibraOn != m_pSettings->value("VibraOn", true).toBool())
    {
        m_pSettings->setValue("VibraOn", m_vibraOn);
    }

    if(m_landscapeMode != m_pSettings->value("LandscapeMode", false).toBool())
    {
        m_pSettings->setValue("LandscapeMode", m_landscapeMode);
    }

    delete m_pSettings;
}

bool Settings::spthPreview() const
{
    return m_spthPreview;
}

void Settings::setSpthPreview(bool arg)
{
    if(m_spthPreview != arg)
    {
        m_spthPreview = arg;
        emit spthPreviewChanged(arg);
    }
}

int Settings::quality() const
{
    return m_quality;
}

void Settings::setQuality(int arg)
{
    if(m_quality != arg)
    {
        m_quality = arg;
        emit qualityChanged(arg);
    }
}

bool Settings::isDefaultQuality() const
{
    return m_isDefaultQuality;
}

void Settings::setIsDefaultQuality(bool arg)
{
    if(m_isDefaultQuality != arg)
    {
        m_isDefaultQuality = arg;
        emit isDefaultQualityChanged(arg);
    }
}

bool Settings::vibraOn() const
{
    return m_vibraOn;
}

void Settings::setVibraOn(bool arg)
{
    if(m_vibraOn != arg)
    {
        m_vibraOn = arg;
        emit vibraOnChanged(arg);
    }
}

bool Settings::landscapeMode() const
{
    return m_landscapeMode;
}

void Settings::setLandscapeMode(bool arg)
{
    if(m_landscapeMode != arg)
    {
        m_landscapeMode = arg;
        emit landscapeModeChanged(arg);
    }
}




