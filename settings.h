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

public:

    explicit Settings(QObject *parent = 0);

    ~Settings();

    Q_INVOKABLE void update();
    
    bool spthPreview() const;
    void setSpthPreview(bool arg);

    int quality() const;
    void setQuality(int arg);

    bool isDefaultQuality() const;
    void setIsDefaultQuality(bool arg);

    bool vibraOn() const;
    void setVibraOn(bool arg);

signals:
    
    void spthPreviewChanged(bool arg);
    void qualityChanged(int arg);
    void isDefaultQualityChanged(bool arg);
    void vibraOnChanged(bool arg);

public slots:

private:

QSettings *m_pSettings;

};

#endif // SETTINGS_H
