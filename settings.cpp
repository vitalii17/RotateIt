#include <QDebug>

#include "settings.h"

Settings::Settings(QObject *parent) :
    QObject(parent), m_pSettings(new QSettings)
{

}

Settings::~Settings()
{
    delete m_pSettings;
}

void Settings::update()
{
    emit spthPreviewChanged(spthPreview());
}

bool Settings::spthPreview() const
{
    return m_pSettings->value("SmoothPixmapTransformHintPreview", false).toBool();
}

void Settings::setSpthPreview(bool arg)
{
    m_pSettings->setValue("SmoothPixmapTransformHintPreview", arg);
    emit spthPreviewChanged(arg);
}

int Settings::quality() const
{
    return m_pSettings->value("Quality", 96).toInt();
}

void Settings::setQuality(int arg)
{
    m_pSettings->setValue("Quality", arg);
    emit qualityChanged(arg);
}

bool Settings::isDefaultQuality() const
{
    return m_pSettings->value("IsDefaultQuality", true).toBool();
}

void Settings::setIsDefaultQuality(bool arg)
{
    m_pSettings->setValue("IsDefaultQuality", arg);
    emit isDefaultQualityChanged(arg);
}

bool Settings::vibraOn() const
{
    return m_pSettings->value("VibraOn", true).toBool();
}

void Settings::setVibraOn(bool arg)
{
    m_pSettings->setValue("VibraOn", arg);
    emit vibraOnChanged(arg);
}




