#ifndef EMPTYVIBRA_H
#define EMPTYVIBRA_H

class EmptyVibra
{

public:

    EmptyVibra();

    bool start(int duration = 0) const;
    bool setIntensity(int intensity) const;
};

#endif // EMPTYVIBRA_H
