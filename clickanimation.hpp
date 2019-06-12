#pragma once
#include "animation.hpp"
class GemsGrig;


class ClickAnimation : public Animation {

public:
    ClickAnimation(GemsGrid * grid, unsigned int i, unsigned int j);

private:
    constexpr static int Interval = 10;
    GemsGrid * _grid;
    unsigned int _row;
    unsigned int _col;
    int _disappearTime;
    unsigned int _left;
    unsigned int _right;
    void timerEvent(QTimerEvent *) override;

};

