#include "ant.h"
#include "gameengine.h"
#include "tiles.h"
#include <QTransform>

Ant::Ant(GameEngine &engine) : engine_(engine) {
    forwardDirection_ = QVector2D(rand() % 100 - 50, rand() % 100 - 50).normalized();

    if (forwardDirection_.length() < 0.5)
        forwardDirection_ = QVector2D(1.0, 0.0);
}

Ant::Ant(GameEngine &engine, const QVector2D &pos) : engine_(engine), position_(pos) {
    forwardDirection_ = QVector2D(rand() % 100 - 50, rand() % 100 - 50).normalized();

    if (forwardDirection_.length() < 0.5)
        forwardDirection_ = QVector2D(1.0, 0.0);
}

void Ant::tick() {
    int rotationAmount = 20;

    QVector2D newPosition = position_ + forwardDirection_ * speed_ * 10;

    if (newPosition.x() >= 2.0 && newPosition.y() >= 2.0 && newPosition.x() < engine_.terrain().size().width() - 2 && newPosition.y() < engine_.terrain().size().height() - 2) {
        if (engine_.terrain().tile(newPosition.x(), newPosition.y()).empty()) {
            position_ += forwardDirection_ * speed_;
            rotationAmount = 5;
        }
    }

    if (rand() % 20 == 0) {
        QTransform rotateLeft;
        rotateLeft.rotate(-rotationAmount);

        forwardDirection_ = QVector2D(rotateLeft.map(forwardDirection_.toPointF()));
        forwardDirection_.normalize();
    }

    if (rand() % 20 == 1) {
        QTransform rotateRight;
        rotateRight.rotate(rotationAmount);

        forwardDirection_ = QVector2D(rotateRight.map(forwardDirection_.toPointF()));
        forwardDirection_.normalize();
    }
}

QVector2D Ant::position() const {
    return position_;
}

QVector2D Ant::forwardDirection() const {
    return forwardDirection_;
}
