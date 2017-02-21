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
    Q_PROPERTY(bool   sliderArrowsEnabled
               READ   sliderArrowsEnabled
               WRITE  setSliderArrowsEnabled
               NOTIFY sliderArrowsEnabledChanged)
    Q_PROPERTY(bool   exifEnabled
               READ   exifEnabled
               WRITE  setExifEnabled
               NOTIFY exifEnabledChanged)

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

    bool galleryAvailable() const;

    bool sliderArrowsEnabled() const;
    void setSliderArrowsEnabled(bool arg);

    bool exifEnabled() const;
    void setExifEnabled(bool arg);

signals:
    void spthPreviewChanged(bool arg);
    void qualityChanged(int arg);
    void isDefaultQualityChanged(bool arg);
    void vibraOnChanged(bool arg);
    void sliderArrowsEnabledChanged(bool arg);
    void exifEnabledChanged(bool arg);

public slots:

private:
    QSettings *m_pSettings;
    bool m_spthPreview;
    int m_quality;
    bool m_isDefaultQuality;
    bool m_vibraOn;
    bool m_sliderArrowsEnabled;
    bool m_exifEnabled;

};

#endif // SETTINGS_H
