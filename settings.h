#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QSettings>

class Settings : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool spthPreview READ spthPreview WRITE setSpthPreview
               NOTIFY spthPreviewChanged)
    Q_PROPERTY(int compression READ compression WRITE setCompression
               NOTIFY compressionChanged)
    Q_PROPERTY(bool isDefaultCompression READ isDefaultCompression WRITE setIsDefaultCompression
               NOTIFY isDefaultCompressionChanged)

public:

    explicit Settings(QObject *parent = 0);

    ~Settings();

    Q_INVOKABLE void update();
    
    bool spthPreview() const;
    void setSpthPreview(bool arg);

    int compression() const;
    void setCompression(int arg);

    bool isDefaultCompression() const;
    void setIsDefaultCompression(bool arg);

signals:
    
    void spthPreviewChanged(bool arg);
    void compressionChanged(int arg);
    void isDefaultCompressionChanged(bool arg);

public slots:

private:

QSettings *m_pSettings;

};

#endif // SETTINGS_H
