#ifndef VIBRA_H
#define VIBRA_H

#include <QObject>

#ifdef Q_OS_SYMBIAN
#include "Symbian/xqvibra.h"
#define D_VIBRA XQVibra
#endif //Q_OS_SYMBIAN

#ifdef Q_OS_SYMBIAN_SIMULATOR
#include "Symbian_simulator/emptyvibra.h"
#define D_VIBRA EmptyVibra
#endif //Q_OS_SYMBIAN_SIMULATOR

class Vibra : public QObject
{
    Q_OBJECT

public:

    explicit Vibra(QObject *parent = 0);
    ~Vibra();
    
signals:
    
public slots:

    void vibrate(int periodmsec);
    void doubleVibrate(int periodmsec, int pausemsec);

private slots:

    void vibrate();
    
private:

    D_VIBRA *m_pVibra;
    int m_period;
};

#endif // VIBRA_H
