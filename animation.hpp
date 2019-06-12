#pragma once

#include <QObject>
#include <vector>
#include <assert.h>
#include <map>
#include "dissapearorder.hpp"
#include "gemsgrid.hpp"

class GemsGrid;

class Gem;

class Animation : public QObject {

    Q_OBJECT

public:
    Animation(int ms) : _ms(ms) {
        startTimer(ms);
        Counter++;
    }

    ~Animation() {
        Counter--;
        emit stop();
    }


    static int getCounter() { return Animation::Counter; }
    int interval() { return _ms; }


private:
    static int Counter;
    int _ms;

signals:
    void updated();
    void stop();

};


class Fall : public Animation {

public:
    Fall(qreal start, qreal dest, qreal velocity)
        : Animation(Interval), _pos(start), _dest(dest), _v(velocity)
    { /*assert((dest - start) * G >= 0);*/ }

    qreal pos() { return _pos; }

    void timerEvent(QTimerEvent * event) override;
    static int animationTime(qreal deltaPos, qreal v = 0);

private:
    constexpr static qreal G = 0.01;
    constexpr static int Interval = 10;
    qreal _pos;
    qreal _dest;
    qreal _v;

};


class Disappear : public Animation {

public:
    Disappear() : Animation(Interval), _opacity(1) {}
    qreal opacity() { return _opacity; }

    void timerEvent(QTimerEvent * event) override;
    static int animationTime();

private:
    constexpr static qreal V = 0.02;
    constexpr static int Interval = 10;
    qreal _opacity;

};


class ChunkDisappear : public Animation {

    template<typename T>
    using Matrix =  std::vector<std::vector<T>>;

    template<typename T>
    using Vector = std::vector<T>;

public:
    ChunkDisappear(const Matrix<Gem *> & gems)
        : Animation(Interval), _gems(gems), _level(0) {}
    //TODO
    //~ChunkDisappear();

    void timerEvent(QTimerEvent * event) override;
    static int animationTime(unsigned int levels);
    int animationTime() { return Interval * int(_gems.size()); }

private:
    constexpr static int Interval = 150;
    Matrix<Gem *> _gems;
    unsigned int _level;
    //TODO delete old gems when animation stops

};


class ColumnFall : public Animation {
public:
    ColumnFall(GemsGrid * grid, unsigned int col);
    void timerEvent(QTimerEvent *) override;

private:
    constexpr static int Interval = 100;
    GemsGrid * _grid;
    unsigned int _col;
    int _row;
};


class GemsFall : public Animation {
public:
    GemsFall(GemsGrid * grid, unsigned int startCol,
             unsigned int left, unsigned int right)
        : Animation(Interval)
        , _grid(grid)
        , _startCol(startCol)
        , _radius(0)
        , _left(left)
        , _right(right)
    {}

    void timerEvent(QTimerEvent *) override;

private:
    constexpr static int Interval = 250;
    GemsGrid  * _grid;
    unsigned int _startCol;
    unsigned int _radius;

    unsigned int _left;
    unsigned int _right;

};


