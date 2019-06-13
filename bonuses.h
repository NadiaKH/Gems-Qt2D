#pragma once
#include "gemsgrid.hpp"
#include "animation.hpp"
#include <vector>


template <typename T>
using Matrix = std::vector<std::vector<T>>;


template <typename T>
using Vector = std::vector<T>;


class Bonus {
public:

    Bonus(GemsGrid * grid, UsualGem * gem)
        : _animation(nullptr), _grid(grid), _gem(gem)
    {}
    virtual ~Bonus() {}
    virtual void startAnimation() = 0;

protected:
    Animation * _animation;
    GemsGrid * _grid;
    Gem * _gem;

};


class Lightning : public Bonus {
public:
    Lightning(GemsGrid * grid, UsualGem * gem = nullptr)
        : Bonus(grid, gem) {}
    void startAnimation() override;

private:
    void createSequence();
    Vector<Gem *> _sequence;
};


class ReplaceColor : public Bonus {
public:
    ReplaceColor(GemsGrid * grid, UsualGem * gem)
        : Bonus(grid, gem) {}
    void startAnimation() override;

private:
    void createLayers();
    Matrix<Gem *> _layers;

};


class ColorBomb : public Bonus {
public:
    ColorBomb(GemsGrid * grid, UsualGem * gem)
        : Bonus(grid, gem) {}
    void startAnimation() override;

private:
    void createLayers();
    Matrix<Gem *> _layers;

};




