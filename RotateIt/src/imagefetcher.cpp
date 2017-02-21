#include <QFileDialog>

#ifdef Q_OS_SYMBIAN
#ifdef MG_FETCH_ENABLED
#include <MGFetch.h>
#include <eikenv.h>
#include <eikmenub.h>
#include <aknappui.h>
#endif // MG_FETCH_ENABLED
#endif // Q_OS_SYMBIAN

#include "imagefetcher.h"

ImageFetcher::ImageFetcher(QObject *parent) :
    QObject(parent)
{
}

QString ImageFetcher::fetchImage(FetchMethod method)
{
    QString strRes;

    setFetched(false);

    switch(method)
    {
    case Gallery:
    {
    #ifdef Q_OS_SYMBIAN
    #ifdef MG_FETCH_ENABLED
        CDesCArrayFlat* fileArray = new(ELeave)CDesCArrayFlat(3);
        CleanupStack::PushL(fileArray);
        if (MGFetch::RunL(*fileArray, EImageFile, EFalse))
        {
            HBufC* result = fileArray->MdcaPoint(0).Alloc();
            strRes = QString((QChar*)result->Des().Ptr(), result->Length());
            m_path = strRes;
            setFetched(true);
        }
        else
        {
            if(!m_path.isEmpty())
            {
                setFetched(true);
            }
            else
            {
                strRes = "";
                setFetched(false);
            }
        }
        CleanupStack::PopAndDestroy();
    #endif // MG_FETCH_ENABLED
    #endif // Q_OS_SYMBIAN
    }
        break;

    case FileManager:
    {
        strRes = QFileDialog::getOpenFileName(0, tr("Select File"), "", "Images (*.png *.jpg");
        if(!strRes.isEmpty())
        {
            setFetched(true);
            m_path = strRes;
        }
        else
        {
            if(!m_path.isEmpty())
            {
                setFetched(true);
            }
            else
            {
                setFetched(false);
            }
        }
    }
        break;

    default:
        setFetched(false);
        break;
    }

    if(!m_path.isEmpty())
    {
        setFetched(true);
    }

    return strRes;
}

bool ImageFetcher::fetched() const
{
    return m_fetched;
}

void ImageFetcher::setFetched(bool fetched)
{
    m_fetched = fetched;
    emit fetchedChanged();
}


