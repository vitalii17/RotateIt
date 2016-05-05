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
    Q_PROPERTY(EngineState state         READ state         WRITE setState RESET resetState)
    Q_ENUMS(EngineState)

public:

    enum EngineState
    {
        Passive, Processing, Opening, Saving, FinalRendering
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

    EngineState state() const;

signals:

    void previewImageChanged();
    void imagePathChanged();
    void previewWidthChanged();
    void previewHeightChanged();
    void rotationChanged();

    void stateChanged();
    
public slots:

private slots:

    void setPreviewImage(QImage arg);
    void setInputPreviewImage(QImage arg);
    void setState(EngineState arg);
    void resetState();

private:

    void rotate(qreal angle);
    
    QImage m_previewImage;
    QImage m_inputPreviewImage;
    QString m_imagePath;
    int m_previewWidth;
    int m_previewHeight;
    qreal m_rotation;
    EngineState m_state;
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

    static QImage rotate(QImage &image, qreal angle);

    qreal angle() const;
    void setAngle(qreal value);

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
    QString m_path;
};

#endif // ENGINE_H
