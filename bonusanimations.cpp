#include "bonusanimations.h"

void LightningAnimation::timerEvent(QTimerEvent *) {
    if (_indx == _seq.size()) {
        delete this;
        return;
    }

    _seq[_indx++]->startDisappear();
}
