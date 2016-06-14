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

}

bool Settings::spthPreview() const
{
    return m_pSettings->value("SmoothPixmapTransformHintPreview", true).toBool();
}

void Settings::setSpthPreview(bool arg)
{
    m_pSettings->setValue("SmoothPixmapTransformHintPreview", arg);
    emit spthChanged(arg);
}


