#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QSettings>

class Settings : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool   spthPreview
               READ   spthPreview
               WRITE  setSpthPreview
               NOTIFY spthPreviewChanged)
    Q_PROPERTY(int    quality
               READ   quality
               WRITE  setQuality
               NOTIFY qualityChanged)
    Q_PROPERTY(bool   isDefaultQuality
               READ   isDefaultQuality
               WRITE  setIsDefaultQuality
               NOTIFY isDefaultQualityChanged)
    Q_PROPERTY(bool   vibraOn
               READ   vibraOn
               WRITE  setVibraOn
               NOTIFY vibraOnChanged)
    Q_PROPERTY(bool   galleryAvailable // Must be moved to other class!
               READ   galleryAvailable)
    Q_PROPERTY(bool   exifEnabled
               READ   exifEnabled
               WRITE  setExifEnabled
               NOTIFY exifEnabledChanged)

public:
    explicit Settings(QObject *parent = 0);

    ~Settings();
    
    bool spthPreview() const;
    void setSpthPreview(bool spth);

    int quality() const;
    void setQuality(int quality);

    bool isDefaultQuality() const;
    void setIsDefaultQuality(bool isDefQuality);

    bool vibraOn() const;
    void setVibraOn(bool vibraOn);

    bool galleryAvailable() const;

    bool exifEnabled() const;
    void setExifEnabled(bool exifEn);

signals:
    void spthPreviewChanged(bool spth);
    void qualityChanged(int quality);
    void isDefaultQualityChanged(bool isDefQuality);
    void vibraOnChanged(bool vibraOn);
    void exifEnabledChanged(bool exifEn);

public slots:

private:
    QSettings *m_pSettings;
    bool m_spthPreview;
    int m_quality;
    bool m_isDefaultQuality;
    bool m_vibraOn;
    bool m_exifEnabled;

};

#endif // SETTINGS_H
