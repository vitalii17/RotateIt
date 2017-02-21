#include <QGraphicsProxyWidget>

#include "imageview.h"
#include <QElapsedTimer>

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
}

QImage ImageView::sourceImage()
{
    return m_sourceImage;
}

void ImageView::setSourceImage(const QImage image)
{
    if(m_sourceImage != image)
    {
        if(image.isNull())
        {
            return;
        }
    // static qint64 time_sum = 0;
    // static int counter = 0;
    // counter++;
    // QElapsedTimer timer; timer.start();
        m_sourceImage = image;

        m_pLabel->setPixmap(QPixmap::fromImage(m_sourceImage).scaled(width(), height(),
                                                                     Qt::KeepAspectRatio/*,
                                                                    Qt::SmoothTransformation*/));
    // time_sum = time_sum + timer.elapsed();
    // qint64 average = time_sum / counter;
    // qDebug() << average;
        //m_pLabel->setPixmap(QPixmap::fromImage(sourceImage));
        //emit sourceImageChanged();
    }
}

void ImageView::widthUpdated()
{
    m_pLabel->resize(width(), height());
}

void ImageView::heightUpdated()
{
    m_pLabel->resize(width(), height());
}
