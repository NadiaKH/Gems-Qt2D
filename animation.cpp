#include "animation.hpp"
#include <QTimerEvent>
#include <math.h>
#include "gem.hpp"

int Animation::Counter = 0;

void Fall::timerEvent(QTimerEvent *) {
    if (_dest > _pos) {
        _v += G * Interval;
        _pos += _v;
        emit updated();
    }
    else {
        _pos = _dest;
        emit updated();
        delete this;
    }
}


int Fall::animationTime(qreal deltaPos, qreal v) {
    assert(deltaPos * G > 0);
    qreal a = G / 2;
    qreal b = (G / 2 + v);
    qreal c = G + v - deltaPos;

    qreal D = b * b - 4 * a * c;

    qreal time = Interval * ceil( (-b + sqrt(D)) / (2 * a) );
    return int(time);
}


void Disappear::timerEvent(QTimerEvent *) {
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


int Disappear::animationTime() {
    qreal time = Interval * ceil( 1 / V );
    return int(time);
}


void ChunkDisappear::timerEvent(QTimerEvent *) {

    if (_level == _gems.size()) {
        delete this;
        return;
    }

    for (Gem * gem : _gems[_level]) {
        gem->startDisappear();
    }

    _level += 1;
}


int ChunkDisappear::animationTime( unsigned int levels ) {
    assert(levels > 0);
    unsigned int time = Interval * (levels - 1);
    return int(time);
}


ColumnFall::ColumnFall(GemsGrid * grid, unsigned int col)
    : Animation(Interval)
    , _grid(grid)
    , _col(col)
    , _row(int(grid->height()))
{}


void ColumnFall::timerEvent(QTimerEvent *) {

    _row = _row - 1;
    Gem * gem = _grid->at(_row, int(_col));
    //assert(gem != nullptr);
    if (gem)
        gem->startFall(_row);

    if (_row == 0)
        delete this;
}


void GemsFall::timerEvent(QTimerEvent *) {
    if (_radius == 0) {
        ColumnFall * cf = new ColumnFall(_grid, _startCol);
        _radius = 1;
        return;
    }

    //TODO
    if (_startCol - _left < _radius && _startCol + _radius > _right) {
        delete this;
        return;
    }

    assert(_startCol >= _left);
    if (_startCol - _left >= _radius) {
        ColumnFall * cf = new ColumnFall(_grid, _startCol - _radius);
    }

    if (_startCol + _radius <= _right) {
        ColumnFall * cf = new ColumnFall(_grid, _startCol + _radius);
    }

    _radius += 1;
}

