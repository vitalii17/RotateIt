#include <QGraphicsProxyWidget>

#include "imageview.h"

ImageView::ImageView(QDeclarativeItem *parent) :
    QDeclarativeItem(parent)
{
    m_pLabel = new QLabel;
    m_pLabel->setAlignment(Qt::AlignCenter);

    m_pProxyWidget = new QGraphicsProxyWidget(this);
    m_pProxyWidget->setWidget(m_pLabel);

    connect(this, SIGNAL(widthChanged()), this, SLOT(widthUpdated()));
    connect(this, SIGNAL(heightChanged()), this, SLOT(heightUpdated()));
}

ImageView::~ImageView()
{
    delete m_pLabel;
    delete m_pProxyWidget;
}

QImage ImageView::sourceImage() const
{
    return m_sourceImage;
}

void ImageView::setSourceImage(const QImage &sourceImage)
{
    m_sourceImage = sourceImage;

    m_pLabel->setPixmap(QPixmap::fromImage(m_sourceImage).scaled(width(), height(),
                                                                 Qt::KeepAspectRatio/*,
                                                                Qt::SmoothTransformation*/));

    //m_pLabel->setPixmap(QPixmap::fromImage(sourceImage));
    emit sourceImageChanged();
}

void ImageView::widthUpdated()
{
    m_pLabel->resize(width(), height());
}

void ImageView::heightUpdated()
{
    m_pLabel->resize(width(), height());
}
