#include "emptyvibra.h"

EmptyVibra::EmptyVibra()
{
}

bool EmptyVibra::start(int duration) const
{
    duration = 0;
    return false;
}

bool EmptyVibra::setIntensity(int intensity) const
{
    return false;
}
