#pragma once
#include "animation.hpp"
#include <vector>
class Gem;

template<typename T>
using Vector = std::vector<T>;

class LightningAnimation : public Animation {

public:
    LightningAnimation(Vector<Gem *> & seq)
        : Animation(Interval)
        , _indx(0)
        , _seq(seq)
    {}

    void timerEvent(QTimerEvent *) override;

private:
    constexpr static int Interval = 50;
    unsigned int _indx;
    Vector<Gem *> _seq;
};
