#include "ant.h"
#include "gameengine.h"
#include "tiles.h"
#include <QTransform>
#include <QtMath>

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
    int x = position_.x();
    int y = position_.y();
    int rotationAmount = (rand() % 2) ? 20 : -20;

    if (engine_.foodHeatmap()[x][y] > 0.5) {
        double maxHeatmapValue = engine_.foodHeatmap()[x][y];
        QVector2D ortho(forwardDirection_.y(), -forwardDirection_.x());

        for (int cx = std::max(0, x - 1); cx <= std::min(engine_.terrain().size().width() - 1, x + 1); ++cx) {
            for (int cy = std::max(0, y - 1); cy <= std::min(engine_.terrain().size().height() - 1, y + 1); ++cy) {
                if (cx != x || cy != y) {
                    if (engine_.foodHeatmap()[cx][cy] > maxHeatmapValue) {
                        maxHeatmapValue = engine_.foodHeatmap()[cx][cy];
                        double angle = acos(QVector2D::dotProduct(forwardDirection_.normalized(), (QVector2D(cx, cy) + QVector2D(0.5, 0.5) - position_).normalized()));

                        if (QVector2D::dotProduct(QVector2D(cx, cy) + QVector2D(0.5, 0.5) - position_, ortho) > 0)
                            rotationAmount = qRadiansToDegrees(-angle);
                        else
                            rotationAmount = qRadiansToDegrees(angle);
                    }
                }
            }
        }
    }

    QVector2D newPosition = position_ + forwardDirection_ * speed_ * 10;

    if (newPosition.x() >= 2.0 && newPosition.y() >= 2.0 && newPosition.x() < engine_.terrain().size().width() - 2 && newPosition.y() < engine_.terrain().size().height() - 2) {
        if (engine_.terrain().tile(newPosition.x(), newPosition.y()).empty()) {
            position_ += forwardDirection_ * speed_;

            if (abs(rotationAmount) == 20)
                rotationAmount = (rand() % 2) ? 5 : -5;
        }
    }

    if (rand() % 10 == 0) {
        QTransform rotation;
        rotation.rotate(rotationAmount);

        forwardDirection_ = QVector2D(rotation.map(forwardDirection_.toPointF()));
        forwardDirection_.normalize();
    }
}

QVector2D Ant::position() const {
    return position_;
}

QVector2D Ant::forwardDirection() const {
    return forwardDirection_;
}
