#ifndef EXTAPPLAUNCHER_H
#define EXTAPPLAUNCHER_H

#include <QObject>

class ExtAppLauncher : public QObject
{
    Q_OBJECT

public:

    explicit ExtAppLauncher(QObject *parent = 0);
    
signals:
    
public slots:

    void startDetached(const QString &program);
    
};

#endif // EXTAPPLAUNCHER_H
