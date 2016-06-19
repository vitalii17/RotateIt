#include <QTimer>

#include "vibra.h"

Vibra::Vibra(QObject *parent) :
    QObject(parent), m_pVibra(new XQVibra)
{
    m_pVibra->setIntensity(90);
}

Vibra::~Vibra()
{
    delete m_pVibra;
}

void Vibra::vibrate(int periodmsec)
{
    m_pVibra->start(periodmsec);
}

void Vibra::doubleVibrate(int periodmsec, int pausemsec)
{
    m_period = periodmsec;
    m_pVibra->start(periodmsec);

    QTimer::singleShot(pausemsec, this, SLOT(vibrate()));
}

void Vibra::vibrate()
{
    m_pVibra->start(m_period);
}
