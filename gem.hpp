#pragma once

#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <unordered_map>
#include <vector>
#include "animation.hpp"

class GameArea;
class GemsGrid;
class Fall;
class Disappear;

class Gem : public QObject {

    Q_OBJECT

public:
    const static int iconSize = 94;

    Gem(int indX, int indY, GemsGrid * parent = nullptr);
    virtual ~Gem();

    int type()                      { return _type; }
    int row()                       { return _row; }
    int col()                       { return _col; }
    QGraphicsPixmapItem * qpix()    { return _qpix; }

    void setCell(int indX, int indY);
    void setPos(int x, int y);

    bool operator==(const Gem & other) { return _type == other._type; }

    void startFall(int row, qreal velocity = 0);
    void startDisappear();

protected:
    GemsGrid * _parent;

    int _col;
    int _row;
    int _type;
    QGraphicsPixmapItem * _qpix;

    Fall * _fall;
    Disappear * _disappear;

 public slots:
    void updateOpacity();
    void updatePos();
    void stop();

};


class UsualGem : public Gem {

public:
    UsualGem(int indX, int indY, GemsGrid * parent = nullptr);

private:
    const static std::vector<const char *> path;

};
