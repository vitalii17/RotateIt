#include <QtGui/QApplication>

//#include <QDeclarativeContext>
#include <QtDeclarative> //qmlRegisterType()
#include "qmlapplicationviewer.h"

#include <QDebug>

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));

    QmlApplicationViewer viewer;
    viewer.setMainQmlFile(QLatin1String("qml/RotateIt/main.qml"));
    viewer.showExpanded();

//    int array_size = 4000;
//    int **array = new int *[array_size];
//    for(int count = 0; count < array_size; count++)
//    {
//        array[count] = new int[array_size];
//    }
//    for(int count_row = 0; count_row < array_size; count_row++)
//    {
//        for(int count_column = 0; count_column < array_size; count_column++)
//        {
//            array[count_row][count_column] = 23;
//        }
//    }

//    for(int count_row = 0; count_row < array_size; count_row++)
//    {
//        for(int count_column = 0; count_column < array_size; count_column++)
//        {
//            array[count_row][count_column] = 23+count_row/2+count_column;
//        }
//    }

//    for(int count = 0; count < array_size; count++)
//    {
//        delete []array[count];
//    }
//    delete []array;

    return app->exec();
}
