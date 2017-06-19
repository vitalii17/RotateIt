#include "exiftools.h"
#include <QDebug>

ExifTools::ExifTools()
{
}

void ExifTools::copyExif(const QString &sourceStr, const QString &destStr)
{
        Exiv2::Image::AutoPtr sourceImageData =
                Exiv2::ImageFactory::open(QFile::encodeName(sourceStr).data());
        sourceImageData->readMetadata();

        Exiv2::ExifData exifData = sourceImageData->exifData();
        Exiv2::IptcData iptcData = sourceImageData->iptcData();

        Exiv2::ExifThumb exifThumb(exifData);
        exifThumb.erase();

        Exiv2::Image::AutoPtr destImageData =
                Exiv2::ImageFactory::open(QFile::encodeName(destStr).data());
        destImageData->setExifData(exifData);
        destImageData->setIptcData(iptcData);
        destImageData->writeMetadata();
}

