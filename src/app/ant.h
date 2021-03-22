#ifndef ANT_H
#define ANT_H

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

    private:
        GameEngine &engine_;

        QVector2D position_;
        qreal speed_ = 0.15;
        QVector2D forwardDirection_ = {1.0, 0.0};
};

#endif // ANT_H
