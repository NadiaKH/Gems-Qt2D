#include <QApplication>
#include <stdlib.h>
#include <time.h>

#include "gamearea.hpp"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    srand(time(NULL));
    GameArea gameArea;

    gameArea.show();
    return a.exec();
}
