#include "dissapearorder.hpp"
#include "gem.hpp"
#include "gemsgrid.hpp"

//TODO:
template<typename T>
using Matrix =  std::vector<std::vector<T>>;

template<typename T>
using Vector = std::vector<T>;


DisappearOrder::DisappearOrder(GemsGrid * grid, unsigned int row, unsigned int col)
    : _grid(grid)
    , _row(row)
    , _col(col)
{
    _type = grid->at(int(row), int(col))->type();
    init();
}


unsigned int DisappearOrder::height() { return _grid->height(); }
unsigned int DisappearOrder::width() {return _grid->width(); }


Vector<Gem *> DisappearOrder::addNextLayer(const Vector<Gem *> & prevLayer, int ordNum) {

    using ui = unsigned int;
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
            if ( !(adjGem = _grid->at(v[0], v[1])) )   continue;
            if ( _ordmap [ ui(v[0]) ][ ui(v[1]) ] ) continue;

            if ( adjGem->type() == _type ) {
                curLayer.push_back(adjGem);
                _ordmap        [ ui(v[0]) ][ ui(v[1]) ] = ordNum;
            }
        }
    }

    return curLayer;
}


void DisappearOrder::init() {
    using ui = unsigned int;
    ui h = _grid->height();
    ui w = _grid->width();

    _ordmap = Matrix<int>  (h, Vector<int> (w, 0));
    _ordmap [_row][_col] = 1;

    Gem * startGem = _grid->at(int(_row), int(_col));
    _layers = { { startGem } };

    for (int n = 1; n < int(w) + int(h) - 1; n++) {
        Vector<Gem *> & prevLayer = _layers[ui(n - 1)];
        Vector<Gem *> curLayer = addNextLayer(prevLayer, n + 1);
        if (!curLayer.empty())
            _layers.push_back( curLayer );
        else break;
    }
}




