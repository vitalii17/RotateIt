#include <QtGui/QApplication>

//#include <QDeclarativeContext>
#include <QtDeclarative> // For qmlRegisterType()
#include "qmlapplicationviewer.h"

#include "imagefetcher.h"
#include "imageview.h"
#include "engine.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));

    qmlRegisterType<ImageFetcher>("imagefetcher", 1, 0, "ImageFetcher");
    qmlRegisterType<ImageView>("imageview", 1, 0, "ImageView");
    qmlRegisterType<Engine>("engine", 1, 0, "Engine");

    QmlApplicationViewer viewer;
    viewer.setMainQmlFile(QLatin1String("qml/RotateIt/main.qml"));
    viewer.showExpanded();

    return app->exec();
}
