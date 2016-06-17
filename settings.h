#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QSettings>

class Settings : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool spthPreview READ spthPreview WRITE setSpthPreview
               NOTIFY spthPreviewChanged)
    Q_PROPERTY(bool spthFinal READ spthFinal WRITE setSpthFinal
               NOTIFY spthFinalChanged)

public:

    explicit Settings(QObject *parent = 0);

    ~Settings();

    Q_INVOKABLE void update();
    
    bool spthPreview() const;
    void setSpthPreview(bool arg);

    bool spthFinal() const;
    void setSpthFinal(bool arg);

signals:
    
    void spthPreviewChanged(bool arg);
    void spthFinalChanged(bool arg);

public slots:

private:

QSettings *m_pSettings;

};

#endif // SETTINGS_H
