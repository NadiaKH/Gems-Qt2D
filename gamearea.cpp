#include "gamearea.hpp"
#include "animation.hpp"


GameArea::GameArea() : _clickable(true), _gameStarted(false) {

    QGraphicsScene * scene = new QGraphicsScene(QRectF(0, 0, SceneWidth, SceneHeight));
    setScene(scene);

    setFixedSize(int(ViewWidth), int(ViewHeight));
    //TODO
    //scene->setBackgroundBrush(QColor(204, 255, 255));
    _grid = new GemsGrid(8, 13);

}


void GameArea::mousePressEvent(QMouseEvent * event){
    if (!_gameStarted) {
        _gameStarted = true;
        _grid->init(scene());
        return;
    }

    if (Animation::getCounter() > 0) return;

    //TODO
    QPointF p = event->localPos();
    qreal offsetX = (ViewWidth - SceneWidth) / 2;
    qreal offsetY = (ViewHeight - SceneHeight) / 2;

    _grid->click(p.x() - offsetX, p.y() - offsetY);

}
