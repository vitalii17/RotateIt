#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>

class Engine : public QObject
{
    Q_OBJECT
public:
    explicit Engine(QObject *parent = 0);
    
private:
    int multiplier;
    int digit;

signals:
    
public slots:
    
};

#endif // ENGINE_H
