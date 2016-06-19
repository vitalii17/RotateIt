#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>
#include <QThread>
#include <QImage>
#include <QString>

class Engine : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QImage      previewImage  READ previewImage  WRITE setPreviewImage)
    Q_PROPERTY(QString     imagePath     READ imagePath     WRITE setImagePath)
    Q_PROPERTY(int         previewWidth  READ previewWidth  WRITE setPreviewWidth)
    Q_PROPERTY(int         previewHeight READ previewHeight WRITE setPreviewHeight)
    Q_PROPERTY(qreal       rotation      READ rotation      WRITE setRotation)
    Q_PROPERTY(EngineState state         READ state         RESET resetState)
    Q_PROPERTY(bool smoothPixmapTransformHint
               READ smoothPixmapTransformHint
               WRITE setSmoothPixmapTransformHint)

    Q_ENUMS(EngineState)

public:

    enum EngineState
    {
        Passive, Processing
    };

    explicit Engine(QObject *parent = 0);

    QImage previewImage() const;

    QString imagePath() const;
    void setImagePath(QString arg);

    int previewWidth() const;
    void setPreviewWidth(int arg);

    int previewHeight() const;
    void setPreviewHeight(int arg);

    qreal rotation() const;
    void setRotation(qreal arg);

    bool smoothPixmapTransformHint();
    void setSmoothPixmapTransformHint(bool hint);

    EngineState state() const;

    Q_INVOKABLE void save(int compression = -1);

signals:

    void previewImageChanged();
    void imagePathChanged();
    void previewWidthChanged();
    void previewHeightChanged();
    void rotationChanged();

    void stateChanged();
    void savingFinished();

public slots:

private:

    enum PrivateEngineState
    {
        Opening, Saving
    };

private slots:

    void setPreviewImage(QImage arg);
    void setInputPreviewImage(QImage arg);
    void setState(EngineState arg, PrivateEngineState privateState);
    void resetState();

    void resetPrivateOpeningState();
    void resetPrivateSavingState();

private:

    void rotate(qreal angle);
    
    QImage m_previewImage;
    QImage m_inputPreviewImage;
    QString m_imagePath;
    int m_previewWidth;
    int m_previewHeight;
    qreal m_rotation;
    bool m_smoothPixmapTransformHint;
    EngineState m_state;

    bool m_privateOpeningState;
    bool m_privateSavingState;
};


class Resize : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int width READ width WRITE setWidth)
    Q_PROPERTY(int height READ height WRITE setHeight)

public:

    explicit Resize(QObject *parent = 0);

    int width() const;
    int height() const;

public slots:

    void process();
    void setInputImagePath(QString path);

    void setWidth(int arg);
    void setHeight(int arg);

signals:

    void finished();
    void finished(QImage outputImage);

private:

    QImage m_inputImage;
    QImage m_outputImage;
    QString m_path;
    int m_width;
    int m_height;
};


class Rotate : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal angle READ angle WRITE setAngle)

public:

    explicit Rotate(QObject *parent = 0);

    static QImage rotate(QImage &image, qreal angle,
                         bool smoothPixmapTransformHint = false);

    qreal angle() const;
    void setAngle(qreal value);

    void setCompression(int value);
    int compression() const;

    void setOutputImagePath(QString &path);

    void setSpth(bool hint);
    bool spth() const;

signals:

    void finished(QImage outputImage);
    void finished();

public slots:

    void process();
    void setInputImagePath(QString path);
    void setInputImage(QImage &image);

private:

    qreal m_angle;
    QImage m_inputImage;
    QString m_inputImagePath;
    QString m_outputImagePath;
    int m_compression;
    bool m_spth;
};

#endif // ENGINE_H
