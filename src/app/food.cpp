#include "food.h"

Food::Food(const QVector2D &pos, int foodAmount) : position_(pos), amount_(foodAmount) {

}

int Food::amount() const {
    return amount_;
}

QVector2D Food::position() const {
    return position_;
}
