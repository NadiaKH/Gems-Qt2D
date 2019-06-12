#include "clickanimation.hpp"
#include <utility>

//TODO:
template<typename T>
using Matrix =  std::vector<std::vector<T>>;

template<typename T>
using Vector = std::vector<T>;

ClickAnimation::ClickAnimation(GemsGrid * grid, unsigned int i, unsigned int j)
    : Animation(Interval)
    , _grid(grid)
    , _row(i)
    , _col(j)

{
    using ui = unsigned int;
    Matrix<Gem *> layers = _grid->getGemChunk(i, j);
    ChunkDisappear * ch = new ChunkDisappear(layers);
    _disappearTime =  Disappear::animationTime() + ch->animationTime();
    _left = grid->width();
    _right = 0;

    for (Vector<Gem *> v : layers) {
        for (Gem * g : v) {
            _left = std::min(_left, ui(g->col()));
            _right = std::max(_right, ui(g->col()));
        }
    }
}


void ClickAnimation::timerEvent(QTimerEvent *) {
    static int curTime = 0;

    if (curTime < _disappearTime / 2) {
        curTime += Interval;
        return;
    }

    GemsFall * gf = new GemsFall(_grid, _col, _left, _right);
    delete this;
}
