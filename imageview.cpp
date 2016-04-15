#include <QGraphicsProxyWidget>

#include "imageview.h"
#include <QDebug>

ImageView::ImageView(QDeclarativeItem *parent) :
    QDeclarativeItem(parent)
{
    label = new QLabel;
    label->setAlignment(Qt::AlignCenter);

    QGraphicsProxyWidget *proxy = new QGraphicsProxyWidget(this);
    proxy->setWidget(label);

    connect(this, SIGNAL(widthChanged()), this, SLOT(widthUpdated()));
    connect(this, SIGNAL(heightChanged()), this, SLOT(heightUpdated()));
}

QImage ImageView::sourceImage() const
{
    return m_sourceImage;
}

void ImageView::setSourceImage(const QImage arg)
{
    m_sourceImage = arg;
    label->setPixmap(QPixmap::fromImage(m_sourceImage).scaled(width(), height(),
                                                              Qt::KeepAspectRatio,
                                                              Qt::SmoothTransformation));
    emit sourceImageChanged();
}

void ImageView::widthUpdated()
{
    label->resize(width(), height());
}

void ImageView::heightUpdated()
{
    label->resize(width(), height());
}
