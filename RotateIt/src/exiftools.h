#ifndef EXIFTOOLS_H
#define EXIFTOOLS_H

#include <QString>
#include <QFile>
#include "exif.hpp"
#include "image.hpp"

class ExifTools
{
public:
    ExifTools();

    static void copyExif(const QString &sourceStr,
                         const QString &destStr,
                         const QString &descriptionStr);
};

#endif // EXIFTOOLS_H
