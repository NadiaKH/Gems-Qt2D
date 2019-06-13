#include <stdlib.h>
#include <time.h>
#include <set>
#include "gem.hpp"
#include "gemsgrid.hpp"
#include "animation.hpp"
#include "clickanimation.hpp"

template <typename T>
using Matrix = GemsGrid::Matrix<T>;


template <typename T>
using Vector = GemsGrid::Vector<T>;


GemsGrid::GemsGrid(unsigned int height, unsigned int width)
    : _w(width)
    , _h(height)
{
    _grid = Matrix<Gem *>(height, Vector<Gem *>(width));

    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
            _grid[i][j] = new UsualGem(int(j), int(i), this);
        }
    }

}


void GemsGrid::init(QGraphicsScene * scene) {

    _scene = scene;

    for (unsigned int i = 0; i < _h; i++) {
        for (unsigned int j = 0; j < _w; j++) {
            scene->addItem(_grid[i][j]->qpix());
            _grid[i][j]->setCell(int(j), 3 * (int(i) - int(_h)));
        }
    }

    unsigned long i, j;
    for (i = 0 ; i < _h / 2; i++) {
        for (j = 0; j < _w; j++) {
            _grid[i * 2][j]->startFall(int(i * 2), -qreal(j)/4);
        }
        for (j = 0; j < _w; j++) {
            _grid[i * 2 + 1][j]->startFall(int(i * 2 + 1), -qreal(_w - j - 1)/4);
        }
    }

    if (i * 2 < _h)
        for (j = 0; j < _w; j++) {
            _grid[i * 2][j]->startFall(int(i * 2), -qreal(j)/4);
        }
}



Gem * GemsGrid::at(int i, int j) {
    using ui = unsigned int;
    if (i < 0 || j < 0 || i >= int(_h) || j >= int(_w))
        return nullptr;
    return _grid[ui(i)][ui(j)];
}

/*
void GemsGrid::clickGem(unsigned int i, unsigned int j) {
    assert(i < _h);
    assert(j < _w);


    DisappearOrder ord(this, i, j);
    std::vector<std::vector<Gem *>> newGems(ord.width());

    //generate new gems with init positions
    for (unsigned int i = 0; i < ord.width(); i++) {
        for (unsigned int j = 0; j < ord.height(); j++) {
            if (ord.is(j, i)) {
                int row = 0;
                if (newGems[i].empty())
                    row = -1;
                else
                    row = newGems[i].back()->row() - 1;
                newGems[i].push_back(new Gem(row, int(i)));
            }
        }
    }


    //TODO how to delete old gems?

    //_clickAnimation =  new ChunkDisappear(tr.layers());


}
*/


void GemsGrid::click(qreal x, qreal y) {
    if (x < 0 || y < 0) return;
    unsigned int j = static_cast<unsigned int>(x / cellSize);
    unsigned int i = static_cast<unsigned int>(y / cellSize);
    if (i >= _h || j >= _w) return;
    ClickAnimation * ca = new ClickAnimation(this, i, j);
}


Matrix<Gem *> GemsGrid::getGemChunk(unsigned int i, unsigned int j) {
    DisappearOrder d(this, i, j);
    for (unsigned int row = 0; row < _h; row++) {
        for (unsigned int col = 0; col < _w; col++)
            if (d.is(row, col))
                _grid[row][col] = nullptr;
    }

    //generateNewGems();

    return d.layers();
}



void GemsGrid::deleteGems(Indx & indx) {
    for (auto p : indx) {
        if (at(int(p.first), int(p.second))) {
            _grid[p.first][p.second] = nullptr;
        }
    }

    //generateNewGems();
}


void GemsGrid::generateNewGems() {
    using ui = unsigned int;
    for (int j = 0; j < int(_w); j++) {
        int shift = 0;
        for (int i = int(_h - 1); i >= 0; i--) {
            if (_grid[ui(i)][ui(j)] == nullptr)
                shift++;
            else {
                _grid[ui(i + shift)][ui(j)] = _grid[ui(i)][ui(j)];
            }
        }

        //generate new gems
        int pos = 0;
        while(shift > 0) {
            shift--;
            pos--;
            // shift instead pos
            _grid[ui(shift)][ui(j)] = new UsualGem(j, pos, this);
            //_grid[ui(shift)][ui(j)] = new UsualGem(j, shift, this);

            //add gem to scene
            _scene->addItem(_grid[ui(shift)][ui(j)]->qpix());
        }
    }

}


/*
Matrix<Gem *> GemsGrid::GridTraverse(unsigned int row, unsigned int col,
                                     Matrix<bool> & used) {

    using ui = unsigned int;

    used = Matrix<bool>(_h, Vector<bool>(_w, false));
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
      TEST:
    for (ui i = 0; i < used.size(); i++) {
        for (ui j = 0; j < used[0].size(); j++) {
            if (used[i][j])
                _grid[i][j]->startDisappear();
        }
    }
    //

    return layers;
}
*/
