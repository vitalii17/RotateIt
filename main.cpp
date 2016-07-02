#include <QtGui/QApplication>
#include <QtDeclarative>
#include "qmlapplicationviewer.h"

#include "imagefetcher.h"
#include "imageview.h"
#include "engine.h"
#include "settings.h"
#include "vibra.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QCoreApplication::setOrganizationName("VS");
    QCoreApplication::setApplicationName("RotateIt");

    Vibra    vibra;
    Settings settings;

    qmlRegisterType<ImageFetcher>("imagefetcher", 1, 0, "ImageFetcher");
    qmlRegisterType<ImageView>   ("imageview",    1, 0, "ImageView");
    qmlRegisterType<Engine>      ("engine",       1, 0, "Engine");

    QDeclarativeView view;
    view.rootContext()->setContextProperty("vibra", &vibra);
    view.rootContext()->setContextProperty("settings", &settings);
    view.setSource(QUrl("qrc:///qml/RotateIt/main.qml"));
    view.showFullScreen();

    return app.exec();
}
