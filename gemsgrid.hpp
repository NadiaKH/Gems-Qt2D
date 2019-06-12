#pragma once

#include "gem.hpp"
#include <vector>
#include <assert.h>
#include <algorithm>
#include <functional>
#include <QGraphicsScene>
#include "gamearea.hpp"
#include "animation.hpp"

class Gem;

class GemsGrid
{

public:

    static const int cellSize = 100;

    //TODO:
    template<typename T>
    using Matrix =  std::vector<std::vector<T>>;

    template<typename T>
    using Vector = std::vector<T>;

    GemsGrid(unsigned int height, unsigned int width);
    ~GemsGrid();
    void init(QGraphicsScene * scene);

    Gem * operator()(unsigned int i, unsigned int j) {
        return _grid[i][j];
    }

    void click(qreal x, qreal y);
    Gem * at(int i, int j);

    unsigned int width()  { return _w; }
    unsigned int height() { return _h; }

    //layers order
    Matrix<Gem *> getGemChunk(unsigned int i, unsigned int j);

    //new matrix with old positions
    void generateNewGems();

private:
    unsigned int _w;
    unsigned int _h;
    QGraphicsScene * _scene;
    //ClickAnimation * _clickAnimation;
    Matrix<Gem *> _grid;

};
