#include <QtGui/QApplication>

//#include <QDeclarativeContext>
#include <QtDeclarative> //qmlRegisterType()
#include "qmlapplicationviewer.h"

#include "imagefetcher.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));

    qmlRegisterType<ImageFetcher>("imagefetcher", 1, 0, "ImageFetcher");

    QmlApplicationViewer viewer;
    viewer.setMainQmlFile(QLatin1String("qml/RotateIt/main.qml"));
    viewer.showExpanded();

    return app->exec();
}
