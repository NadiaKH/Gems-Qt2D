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

    void click(qreal x, qreal y) {
        if (x < 0 || y < 0) return;
        unsigned int j = static_cast<unsigned int>(x / cellSize);
        unsigned int i = static_cast<unsigned int>(y / cellSize);
        if (i >= _h || j >= _w) return;
        clickGem(i, j);
    }

    void clickGem(unsigned int i, unsigned int j) {
        assert(i < _h);
        assert(j < _w);

        Matrix<Gem *> layers = GridTraverse(i, j);
        _clickAnimation =  new ChunkDisappear(layers);

    }

    Gem * at(int i, int j);

private:
    Matrix<Gem *> GridTraverse(unsigned int y0, unsigned int x0);

    ChunkDisappear * _clickAnimation;
    unsigned int _h;
    unsigned int _w;
    Matrix<Gem *> _grid;
};
