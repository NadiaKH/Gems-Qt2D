#pragma once

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QGraphicsRectItem>
#include <QObject>
#include "gemsgrid.hpp"

class GameArea : public QGraphicsView {
public:
    constexpr const static qreal SceneWidth = 1300;
    constexpr const static qreal SceneHeight = 800;

    constexpr const static qreal ViewWidth = 1310;
    constexpr const static qreal ViewHeight = 810;

    GameArea();
    void mousePressEvent(QMouseEvent * event) override;

private:
    bool _clickable;
    bool _gameStarted;
    GemsGrid * _grid;

};

