#ifndef ANT_H
#define ANT_H

#include <QVector2D>

class Ant {
    public:
        explicit Ant();
        explicit Ant(const QVector2D &pos);

        void tick();

        QVector2D position() const;

    private:
        QVector2D position_;
        QVector2D forwardDirection_ = {1.0, 0.0};
        qreal speed_ = 0.05;
};

#endif // ANT_H
