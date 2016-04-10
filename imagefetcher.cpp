#include "imagefetcher.h"

#include <QDebug>

#ifdef Q_OS_SYMBIAN
#include <MGFetch.h>
#include <eikenv.h>
#include <eikmenub.h>
#include <aknappui.h>
#endif

ImageFetcher::ImageFetcher(QObject *parent) :
    QObject(parent)
{
}

QString ImageFetcher::fetchImage(FetchMethod method)
{
    QString strRes;

    switch(method)
    {
    case Gallery:
    {
    #ifdef Q_OS_SYMBIAN
        CDesCArrayFlat* fileArray = new(ELeave)CDesCArrayFlat(3);
        CleanupStack::PushL(fileArray);
        if (MGFetch::RunL(*fileArray, EImageFile, EFalse))
        {
            HBufC* result = fileArray->MdcaPoint(0).Alloc();
            strRes = QString((QChar*)result->Des().Ptr(), result->Length());
            setFetched(true);
        }
        else
        {
            setFetched(false);
        }
        CleanupStack::PopAndDestroy();
    #endif
    }
        break;

    case FileManager:
    {
        // ToDo: write FileMan fatch code
        setFetched(false);
    }
        break;

    default:
        setFetched(false);
    }

    return strRes;
}

bool ImageFetcher::fetched() const
{
    return m_fetched;
}

void ImageFetcher::setFetched(bool arg)
{
    m_fetched = arg;
}


