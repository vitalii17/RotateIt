#ifndef RESIZER_H
#define RESIZER_H

#include <QObject>
#include <QImage>

class Resizer : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int width READ width WRITE setWidth)
    Q_PROPERTY(int height READ height WRITE setHeight)

public:

    explicit Resizer(QObject *parent = 0);

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

#endif // RESIZER_H
