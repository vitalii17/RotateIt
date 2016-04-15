#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QDeclarativeItem>
#include <QLabel>
#include <QImage>
#include <QThread>

class ImageView : public QDeclarativeItem
{
    Q_OBJECT

    Q_PROPERTY(QImage sourceImage READ sourceImage WRITE setSourceImage)

public:

    explicit ImageView(QDeclarativeItem *parent = 0);

    QImage sourceImage() const;

signals:
    void sourceImageChanged();
    
public slots:
    void setSourceImage(const QImage arg);

private slots:

    void widthUpdated();
    void heightUpdated();

private:

    QLabel *label;
    QImage m_sourceImage;
};

#endif // IMAGEVIEW_H
