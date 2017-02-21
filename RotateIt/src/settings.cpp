#include <QDebug>

#include "settings.h"

Settings::Settings(QObject *parent) :
    QObject(parent), m_pSettings(new QSettings)
{
    m_spthPreview         = m_pSettings->value("SmoothPixmapTransformHintPreview", false).toBool();
    m_quality             = m_pSettings->value("Quality", 96).toInt();
    m_isDefaultQuality    = m_pSettings->value("IsDefaultQuality", true).toBool();
    m_vibraOn             = m_pSettings->value("VibraOn", true).toBool();
    m_sliderArrowsEnabled = m_pSettings->value("SliderArrowsEnabled", true).toBool();
    m_exifEnabled         = m_pSettings->value("ExifEnabled", false).toBool();
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

    if(m_sliderArrowsEnabled != m_pSettings->value("SliderArrowsEnabled", true).toBool())
    {
        m_pSettings->setValue("SliderArrowsEnabled", m_sliderArrowsEnabled);
    }

    if(m_exifEnabled != m_pSettings->value("ExifEnabled", false).toBool())
    {
        m_pSettings->setValue("ExifEnabled", m_exifEnabled);
    }

    delete m_pSettings;
}

bool Settings::spthPreview() const
{
    return m_spthPreview;
}

void Settings::setSpthPreview(bool spth)
{
    if(m_spthPreview != spth)
    {
        m_spthPreview = spth;
        emit spthPreviewChanged(m_spthPreview);
    }
}

int Settings::quality() const
{
    return m_quality;
}

void Settings::setQuality(int quality)
{
    if(m_quality != quality)
    {
        m_quality = quality;
        emit qualityChanged(m_quality);
    }
}

bool Settings::isDefaultQuality() const
{
    return m_isDefaultQuality;
}

void Settings::setIsDefaultQuality(bool isDefQuality)
{
    if(m_isDefaultQuality != isDefQuality)
    {
        m_isDefaultQuality = isDefQuality;
        emit isDefaultQualityChanged(m_isDefaultQuality);
    }
}

bool Settings::vibraOn() const
{
    return m_vibraOn;
}

void Settings::setVibraOn(bool vibraOn)
{
    if(m_vibraOn != vibraOn)
    {
        m_vibraOn = vibraOn;
        emit vibraOnChanged(m_vibraOn);
    }
}

bool Settings::galleryAvailable() const
{
#ifdef MG_FETCH_ENABLED
    return true;
#elif MG_FETCH_DISABLED
    return false;
#endif
}

bool Settings::sliderArrowsEnabled() const
{
    return m_sliderArrowsEnabled;
}

void Settings::setSliderArrowsEnabled(bool arrowsEn)
{
    if(m_sliderArrowsEnabled != arrowsEn)
    {
        m_sliderArrowsEnabled = arrowsEn;
        emit sliderArrowsEnabledChanged(m_sliderArrowsEnabled);
    }
}

bool Settings::exifEnabled() const
{
    return m_exifEnabled;
}

void Settings::setExifEnabled(bool exifEn)
{
    if(m_exifEnabled != exifEn)
    {
        m_exifEnabled = exifEn;
        emit exifEnabledChanged(m_exifEnabled);
    }
}




