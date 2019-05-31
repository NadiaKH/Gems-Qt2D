#include "gem.hpp"
#include "gamearea.hpp"
#include <stdlib.h>
#include <time.h>
#include <QPainter>
#include "animation.hpp"


Gem::Gem(int indX, int indY, GemsGrid * parent)
    : _parent(parent)
    , _col(indX)
    , _row(indY)
    , _qpix( new QGraphicsPixmapItem() )
    , _fall(nullptr)
    , _disappear(nullptr)
{}


Gem::~Gem() {
    if (_qpix) delete _qpix;
}


void Gem::setCell(int indX, int indY) {
    _col = indX;
    _row = indY;
    int x = indX * GemsGrid::cellSize;
    int y = indY * GemsGrid::cellSize;
    setPos(x, y);
}


void Gem::setPos(int x, int y) {
    int offset = (GemsGrid::cellSize - iconSize) / 2;
    _qpix->setPos(x + offset, y + offset);
}


void Gem::startFall(int row, qreal velocity) {
    int start = _row * GemsGrid::cellSize;
    int dest = row * GemsGrid::cellSize;
    _fall = new Fall(start, dest, velocity);
    _row = row;
    connect(_fall, &Fall::updated, this, &Gem::updatePos);
    connect(_fall, &Fall::stop, this, &Gem::stop);

}


void Gem::startDisappear() {
    _disappear = new Disappear;
    connect(_disappear, &Disappear::updated, this, &Gem::updateOpacity);
}


void Gem::updatePos() {
    int x = _col * GemsGrid::cellSize;
    setPos(x, int(_fall->pos()));
}


void Gem::updateOpacity() {
    _qpix->setOpacity(_disappear->opacity());
}


void Gem::stop() {
    int x = _col * GemsGrid::cellSize;
    int y = _row * GemsGrid::cellSize;
    setPos(x, y);
}




const std::vector<const char *> UsualGem::path = {
    ":/img/Diamond.png",
    ":/img/PixelRuby.png",
    ":/img/Lapis.png",
    ":/img/GoldApple.png",
};


UsualGem::UsualGem(int indX, int indY, GemsGrid * parent)
    : Gem(indX, indY, parent)
{

    int num = int(path.size());

    _type = rand() % num;

    _qpix = new QGraphicsPixmapItem(QPixmap(path[_type])
                                    .scaled(iconSize, iconSize));
}
