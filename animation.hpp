#pragma once

#include <QObject>
#include <vector>
class Gem;


class Animation : public QObject {

    Q_OBJECT

public:
    Animation(int ms) {
        startTimer(ms);
        Counter++;
    }

    ~Animation() {
        Counter--;
        emit stop();
    }

    static int getCounter() { return Animation::Counter; }

private:
    static int Counter;

signals:
    void updated();
    void stop();

};


class Fall : public Animation {

public:
    Fall(qreal start, qreal dest, qreal velocity, int ms = 10)
        : Animation(ms), _pos(start), _dest(dest), _v(velocity), _ms(ms){}

    qreal pos() { return _pos; }
    void timerEvent(QTimerEvent * event) override;


private:
    constexpr static qreal G = 0.01;
    qreal _pos;
    qreal _dest;
    qreal _v;
    qreal _ms;

};


class Disappear : public Animation {

public:
    Disappear(int ms = 10) : Animation(ms), _opacity(1) {}
    qreal opacity() { return _opacity; }
    void timerEvent(QTimerEvent * event) override;

private:
    constexpr static const qreal V = 0.02;
    qreal _opacity;

};


class ChunkDisappear : public Animation {

    template<typename T>
    using Matrix =  std::vector<std::vector<T>>;

    template<typename T>
    using Vector = std::vector<T>;

public:
    ChunkDisappear(const Matrix<Gem *> & gems, int ms = 150)
        : Animation(ms), _gems(gems), _level(0) {}
    void timerEvent(QTimerEvent * event) override;

private:
    Matrix<Gem *> _gems;
    unsigned int _level;

};
