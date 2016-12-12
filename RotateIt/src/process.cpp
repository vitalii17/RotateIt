#include "process.h"

#include <QProcess>

Process::Process(QObject *parent) :
    QObject(parent)
{

}

void Process::startDetached(const QString &program)
{
    QProcess::startDetached(program);
}
