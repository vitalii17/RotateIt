#include "extapplauncher.h"

#include <QProcess>

ExtAppLauncher::ExtAppLauncher(QObject *parent) :
    QObject(parent)
{

}

void ExtAppLauncher::startDetached(const QString &program)
{
    QProcess::startDetached(program);
}
