#include <QGraphicsProxyWidget>

#include "imageview.h"

ImageView::ImageView(QDeclarativeItem *parent) :
    QDeclarativeItem(parent)
{
    m_label = new QLabel;
    m_label->setAlignment(Qt::AlignCenter);

    QGraphicsProxyWidget *proxy = new QGraphicsProxyWidget(this);
    proxy->setWidget(m_label);

    connect(this, SIGNAL(widthChanged()), this, SLOT(widthUpdated()));
    connect(this, SIGNAL(heightChanged()), this, SLOT(heightUpdated()));
}

ImageView::~ImageView()
{
    delete m_label;
}

QImage ImageView::sourceImage() const
{
    return m_sourceImage;
}

void ImageView::setSourceImage(const QImage &sourceImage)
{
    m_sourceImage = sourceImage;

    m_label->setPixmap(QPixmap::fromImage(m_sourceImage).scaled(width(), height(),
                                                                Qt::KeepAspectRatio,
                                                                Qt::SmoothTransformation));

    //    m_label->setPixmap(QPixmap::fromImage(sourceImage));

    emit sourceImageChanged();
}

void ImageView::widthUpdated()
{
    m_label->resize(width(), height());
}

void ImageView::heightUpdated()
{
    m_label->resize(width(), height());
}
