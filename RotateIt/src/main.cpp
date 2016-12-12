#include <QtGui/QApplication>
#include <QtDeclarative>
#include <QLocale>
#include "qmlapplicationviewer.h"

#include "imagefetcher.h"
#include "imageview.h"
#include "engine.h"
#include "settings.h"
#include "vibra.h"
#include "process.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QLabel *splashScreen = new QLabel;

#ifdef Q_OS_SYMBIAN
    splashScreen->setText("Symbian Zone");
#else
    splashScreen->setText("Rotate It!");
#endif

    QFont font;
    font.setPixelSize(10);

    QFontMetrics fontMetrics(font);

    font.setPixelSize(app.desktop()->screenGeometry().width() *
                      font.pixelSize() /
                      fontMetrics.width(splashScreen->text()));

    splashScreen->setFont(font);
    splashScreen->setAlignment(Qt::AlignCenter);
    splashScreen->showFullScreen();

    QCoreApplication::setOrganizationName("VS");
    QCoreApplication::setApplicationName("RotateIt");

    QString translationPath = ":/translations/" +
            QLocale::languageToString(QLocale::system().language());

    QTranslator translator;
    translator.load(translationPath);

    app.installTranslator(&translator);

    Vibra    vibra;
    Settings settings;
    Process  process;

    qmlRegisterType<ImageFetcher>("imagefetcher", 1, 0, "ImageFetcher");
    qmlRegisterType<ImageView>   ("imageview",    1, 0, "ImageView");
    qmlRegisterType<Engine>      ("engine",       1, 0, "Engine");

    QDeclarativeView view;
    view.rootContext()->setContextProperty("vibra", &vibra);
    view.rootContext()->setContextProperty("settings", &settings);
    view.rootContext()->setContextProperty("process", &process);

    if(argc > 1)
    {
        view.rootContext()->setContextProperty("startImagePath", argv[1]);
    }
    else
    {
        view.rootContext()->setContextProperty("startImagePath", "");
    }

    view.setSource(QUrl("qrc:/gui/qml/main.qml"));
    view.showFullScreen();

    delete splashScreen;

    return app.exec();
}
