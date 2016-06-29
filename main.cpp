#include <QtGui/QApplication>

//#include <QDeclarativeContext>
#include <QtDeclarative> // For qmlRegisterType()
#include "qmlapplicationviewer.h"

#include "imagefetcher.h"
#include "imageview.h"
#include "engine.h"
#include "settings.h"
#include "vibra.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));

    QCoreApplication::setOrganizationName("VS");
    QCoreApplication::setApplicationName("RotateIt");

    Vibra    vibra;
    Settings settings;

    qmlRegisterType<ImageFetcher>("imagefetcher", 1, 0, "ImageFetcher");
    qmlRegisterType<ImageView>   ("imageview",    1, 0, "ImageView");
    qmlRegisterType<Engine>      ("engine",       1, 0, "Engine");

    QmlApplicationViewer viewer;
    viewer.rootContext()->setContextProperty("vibra", &vibra);
    viewer.rootContext()->setContextProperty("settings", &settings);
    viewer.setMainQmlFile(QLatin1String("qml/RotateIt/main.qml"));
    viewer.showExpanded();

    return app->exec();
}
