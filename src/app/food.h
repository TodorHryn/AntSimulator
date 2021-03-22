#ifndef FOOD_H
#define FOOD_H

#include <QVector2D>

class Food {
    public:
        explicit Food(const QVector2D &pos, int foodAmount);

        int amount() const;
        QVector2D position() const;

    private:
        QVector2D position_;
        int amount_;
};

#endif // FOOD_H
