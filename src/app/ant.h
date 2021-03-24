#ifndef ANT_H
#define ANT_H

#include "heatmap.h"
#include <QVector2D>

class GameEngine;

class Ant {
    public:
        explicit Ant(GameEngine &engine);
        explicit Ant(GameEngine &engine, const QVector2D &pos);
        void operator=(const Ant&) = delete;

        void tick();

        QVector2D position() const;
        QVector2D forwardDirection() const;
        int foodCarried() const;

    private:
        bool getRotationAngleFromHeatmap(const Heatmap &heatmap, double &angle);

        const int MAX_FOOD_CARRIED = 1;

        GameEngine &engine_;

        QVector2D position_;
        qreal speed_ = 0.15;
        QVector2D forwardDirection_ = {1.0, 0.0};
        int foodCarried_ = 0;
};

#endif // ANT_H
