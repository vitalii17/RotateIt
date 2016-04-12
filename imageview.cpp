#include <QGraphicsProxyWidget>

#include "imageview.h"
#include <QDebug>

ImageView::ImageView(QDeclarativeItem *parent) :
    QDeclarativeItem(parent)
{
    label = new QLabel;

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
    label->setPixmap(QPixmap::fromImage(m_sourceImage).scaled(640, 360));
    emit sourceImageChanged();
}

void ImageView::widthUpdated()
{

}

void ImageView::heightUpdated()
{

}
