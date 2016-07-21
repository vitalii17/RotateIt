#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QSettings>

class Settings : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool spthPreview READ spthPreview WRITE setSpthPreview
               NOTIFY spthPreviewChanged)
    Q_PROPERTY(int quality READ quality WRITE setQuality
               NOTIFY qualityChanged)
    Q_PROPERTY(bool isDefaultQuality READ isDefaultQuality WRITE setIsDefaultQuality
               NOTIFY isDefaultQualityChanged)
    Q_PROPERTY(bool vibraOn READ vibraOn WRITE setVibraOn NOTIFY vibraOnChanged)
    Q_PROPERTY(bool landscapeMode READ landscapeMode WRITE setLandscapeMode
               NOTIFY landscapeModeChanged)
    Q_PROPERTY(bool galleryAvailable READ galleryAvailable)

public:

    explicit Settings(QObject *parent = 0);

    ~Settings();
    
    bool spthPreview() const;
    void setSpthPreview(bool arg);

    int quality() const;
    void setQuality(int arg);

    bool isDefaultQuality() const;
    void setIsDefaultQuality(bool arg);

    bool vibraOn() const;
    void setVibraOn(bool arg);

    bool landscapeMode() const;
    void setLandscapeMode(bool arg);

    bool galleryAvailable() const;

signals:
    
    void spthPreviewChanged(bool arg);
    void qualityChanged(int arg);
    void isDefaultQualityChanged(bool arg);
    void vibraOnChanged(bool arg);
    void landscapeModeChanged(bool arg);

public slots:

private:

QSettings *m_pSettings;
bool m_spthPreview;
int m_quality;
bool m_isDefaultQuality;
bool m_vibraOn;
bool m_landscapeMode;

};

#endif // SETTINGS_H
