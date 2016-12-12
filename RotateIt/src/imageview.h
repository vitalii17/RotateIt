#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QDeclarativeItem>
#include <QLabel>
#include <QImage>
#include <QPainter>
#include <QPaintEvent>

class ImageView : public QDeclarativeItem
{
    Q_OBJECT

    Q_PROPERTY(QImage sourceImage READ sourceImage WRITE setSourceImage)

public:

    explicit ImageView(QDeclarativeItem *parent = 0);
    ~ImageView();

    QImage sourceImage();

signals:
    void sourceImageChanged();
    
public slots:
    void setSourceImage(const QImage arg);

private slots:

    void widthUpdated();
    void heightUpdated();

private:

    QLabel *m_pLabel;
    QImage m_sourceImage;

    QGraphicsProxyWidget *m_pProxyWidget;
};

#endif // IMAGEVIEW_H



