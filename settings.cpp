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

int Settings::compression() const
{
    return m_pSettings->value("Compression", 5).toInt();
}

void Settings::setCompression(int arg)
{
    m_pSettings->setValue("Compression", arg);
    emit compressionChanged(arg);
}

bool Settings::isDefaultCompression() const
{
    return m_pSettings->value("IsDefaultCompression", true).toBool();
}

void Settings::setIsDefaultCompression(bool arg)
{
    m_pSettings->setValue("IsDefaultCompression", arg);
    emit isDefaultCompressionChanged(arg);
}




