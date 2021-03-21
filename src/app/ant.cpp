#include "ant.h"
#include <QTransform>

Ant::Ant() {

}

Ant::Ant(const QVector2D &pos) : position_(pos) {

}

void Ant::tick() {
    position_ += forwardDirection_ * speed_;

    if (rand() % 20 == 0) {
        QTransform rotateLeft;
        rotateLeft.rotate(-5);

        forwardDirection_ = QVector2D(rotateLeft.map(forwardDirection_.toPointF()));
        forwardDirection_.normalize();
    }

    if (rand() % 20 == 1) {
        QTransform rotateRight;
        rotateRight.rotate(5);

        forwardDirection_ = QVector2D(rotateRight.map(forwardDirection_.toPointF()));
        forwardDirection_.normalize();
    }
}

QVector2D Ant::position() const {
    return position_;
}
