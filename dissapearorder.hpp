#pragma once
#include <vector>
#include "gemsgrid.hpp"

class GemsGrid;
class Gem;


class DisappearOrder {

    //TODO:
    template<typename T>
    using Matrix =  std::vector<std::vector<T>>;

    template<typename T>
    using Vector = std::vector<T>;

public:
    DisappearOrder(GemsGrid * grid, unsigned int row, unsigned int col);
    void init();
    Matrix<Gem *> layers() { return _layers; }
    Matrix<int>   ordmap   () { return _ordmap; }
    bool is(unsigned int i, unsigned int j) { return _ordmap[i][j]; }
    unsigned int height();
    unsigned int width();


private:
    GemsGrid * _grid;
    unsigned int _row;
    unsigned int _col;
    int _type;

    Vector<Gem *> addNextLayer(const Vector<Gem *> & prevLayer, int ordNum);

    Matrix<Gem *>   _layers;
    Matrix<int>     _ordmap;
};
