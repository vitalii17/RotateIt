#ifndef IMAGEFETCHER_H
#define IMAGEFETCHER_H

#include <QObject>
#include <QString>
#include <QImage>

class ImageFetcher : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool fetched READ fetched WRITE setFetched)
    Q_ENUMS(FetchMethod)

public:

    enum FetchMethod
    {
        Gallery,
        FileManager
    };

    explicit ImageFetcher(QObject *parent = 0);

    Q_INVOKABLE QString fetchImage(FetchMethod method);

    bool fetched() const;

signals:

public slots:

    void setFetched(const bool arg);

private:

    bool m_fetched;
};

#endif // IMAGEFETCHER_H
