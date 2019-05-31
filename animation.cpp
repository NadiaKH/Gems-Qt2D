#include "animation.hpp"
#include <QTimerEvent>
#include "gem.hpp"

int Animation::Counter = 0;


void Fall::timerEvent(QTimerEvent * event) {
    if (_dest > _pos) {
        _v += G * _ms;
        _pos += _v;
        emit updated();
    }
    else {
        _pos = _dest;
        emit updated();
        delete this;
    }
}


void Disappear::timerEvent(QTimerEvent *event) {
    if (_opacity > V) {
        _opacity -= V;
        emit updated();
    }
    else {
        _opacity = 0;
        emit updated();
        delete this;
    }
}


void ChunkDisappear::timerEvent(QTimerEvent *event) {

    if (_level == _gems.size()) {
        delete this;
        return;
    }

    for (Gem * gem : _gems[_level]) {
        gem->startDisappear();
    }

    _level += 1;
}
