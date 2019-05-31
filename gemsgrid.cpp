#include <stdlib.h>
#include <time.h>
#include <set>
#include "gemsgrid.hpp"

template <typename T>
using Matrix = GemsGrid::Matrix<T>;


template <typename T>
using Vector = GemsGrid::Vector<T>;


GemsGrid::GemsGrid(unsigned int height, unsigned int width)
    : _w(width)
    , _h(height)
    , _clickAnimation(nullptr)
{
    _grid = Matrix<Gem *>(height, Vector<Gem *>(width));

    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
            _grid[i][j] = new UsualGem(int(j), int(i), this);
        }
    }

}


void GemsGrid::init(QGraphicsScene * scene) {

    for (unsigned int i = 0; i < _h; i++) {
        for (unsigned int j = 0; j < _w; j++) {
            scene->addItem(_grid[i][j]->qpix());
            _grid[i][j]->setCell(int(j), 3 * (int(i) - int(_h)));
        }
    }

    unsigned long i, j;
    for (i = 0 ; i < _h / 2; i++) {
        for (j = 0; j < _w; j++) {
            _grid[i * 2][j]->startFall(int(i * 2), -qreal(j)/2);
        }
        for (j = 0; j < _w; j++) {
            _grid[i * 2 + 1][j]->startFall(int(i * 2 + 1), -qreal(_w - j - 1)/2);
        }
    }

    if (i * 2 < _h)
        for (j = 0; j < _w; j++) {
            _grid[i * 2][j]->startFall(int(i * 2), -qreal(j)/2);
        }
}


Gem * GemsGrid::at(int i, int j) {
    using ui = unsigned int;

    if (i < 0 || j < 0) return nullptr;
    if (i >= int(_h) || j >=  int(_w)) return nullptr;
    return _grid[ui(i)][ui(j)];
}


Matrix<Gem *> GemsGrid::GridTraverse(unsigned int row, unsigned int col) {

    using ui = unsigned int;

    Matrix<bool> used(_h, Vector<bool>(_w, false));
    used[row][col] = true;
    Gem * startGem = _grid[row][col];
    Matrix<Gem *> layers = { { startGem } };

    for (int n = 1; n < int(_w) + int(_h) - 1; n++) {
        Vector<Gem *> & prevLayer = layers[ui(n - 1)];
        Vector<Gem *> curLayer;

        for (Gem * gem : prevLayer) {
            int row = gem->row();
            int col = gem->col();

            std::vector<std::vector<int>> adj = {
                {row - 1, col}, {row + 1, col},
                {row, col - 1}, {row, col + 1},
            };

            Gem * adjGem;
            for (auto v : adj) {
                if ( !(adjGem = at(v[0], v[1])) )   continue;
                if ( used[ ui(v[0]) ][ ui(v[1]) ] ) continue;

                if ( *adjGem == *startGem ) {
                    curLayer.push_back(adjGem);
                    used[ ui(v[0]) ][ ui(v[1]) ] = true;
                }
            }
        }

        if (!curLayer.empty())
            layers.push_back( curLayer );
        else break;
    }

    //TODO:
     /* TEST:
    for (ui i = 0; i < used.size(); i++) {
        for (ui j = 0; j < used[0].size(); j++) {
            if (used[i][j])
                _grid[i][j]->startDisappear();
        }
    }
    //*/

    return layers;
}