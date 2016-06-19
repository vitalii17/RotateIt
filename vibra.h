#ifndef VIBRA_H
#define VIBRA_H

#include <QObject>
#include <xqvibra.h>

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

    XQVibra *m_pVibra;
    int m_period;
};

#endif // VIBRA_H
