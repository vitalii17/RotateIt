#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>
#include <QThread>
#include <QImage>
#include <QString>

class Engine : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QImage      previewImage
               READ        previewImage
               WRITE       setPreviewImage
               NOTIFY      previewImageChanged)
    Q_PROPERTY(QString     imagePath
               READ        imagePath
               WRITE       setImagePath)
    Q_PROPERTY(int         previewWidth
               READ        previewWidth
               WRITE       setPreviewWidth)
    Q_PROPERTY(int         previewHeight
               READ        previewHeight
               WRITE       setPreviewHeight)
    Q_PROPERTY(qreal       rotation
               READ        rotation
               WRITE       setRotation)
    Q_PROPERTY(EngineState state
               READ        state
               RESET       resetState)
    Q_PROPERTY(bool        smoothPixmapTransformHint
               READ        smoothPixmapTransformHint
               WRITE       setSmoothPixmapTransformHint)
    Q_PROPERTY(bool        exifEnabled
               READ        exifEnabled
               WRITE       setExifEnabled
               NOTIFY      exifEnabledChanged)

    Q_ENUMS(EngineState)

public:

    enum EngineState
    {
        Passive, Processing
    };

    explicit Engine(QObject *parent = 0);

    QImage previewImage() const;

    QString imagePath() const;
    void setImagePath(QString path);

    int previewWidth() const;
    void setPreviewWidth(int width);

    int previewHeight() const;
    void setPreviewHeight(int height);

    qreal rotation() const;
    void setRotation(qreal rotation);

    bool smoothPixmapTransformHint() const;
    void setSmoothPixmapTransformHint(bool hint);

    bool exifEnabled() const;
    void setExifEnabled(bool exifEn);

    EngineState state() const;

    Q_INVOKABLE void rotate(qreal angle);
    Q_INVOKABLE void save(int quality = -1);

signals:

    void previewImageChanged();
    void imagePathChanged();
    void previewWidthChanged();
    void previewHeightChanged();
    void rotationChanged();
    void exifEnabledChanged();

    void stateChanged();
    void savingFinished();

public slots:

private:

    enum PrivateEngineState
    {
        Opening, Saving
    };

private slots:

    void setPreviewImage(const QImage image);
    void setInputPreviewImage(QImage image);
    void setState(EngineState state, PrivateEngineState privateState);
    void resetState();

    void resetPrivateOpeningState();
    void resetPrivateSavingState();

private:
    
    QImage      m_previewImage;
    QImage      m_inputPreviewImage;
    QString     m_imagePath;
    int         m_previewWidth;
    int         m_previewHeight;
    qreal       m_rotation;
    bool        m_smoothPixmapTransformHint;
    EngineState m_state;
    bool        m_exifEnabled;

    bool        m_privateOpeningState;
    bool        m_privateSavingState;
};


#endif // ENGINE_H
