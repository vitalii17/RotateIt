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
    emit spthFinalChanged(spthFinal());
}

bool Settings::spthPreview() const
{
    return m_pSettings->value("SmoothPixmapTransformHintPreview", true).toBool();
}

void Settings::setSpthPreview(bool arg)
{
    m_pSettings->setValue("SmoothPixmapTransformHintPreview", arg);
    emit spthPreviewChanged(arg);
}

bool Settings::spthFinal() const
{
    return m_pSettings->value("SmoothPixmapTransformHintFinal", true).toBool();
}

void Settings::setSpthFinal(bool arg)
{
    m_pSettings->setValue("SmoothPixmapTransformHintFinal", arg);
    emit spthFinalChanged(arg);
}


