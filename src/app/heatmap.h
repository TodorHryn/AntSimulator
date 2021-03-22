#ifndef HEATMAP_H
#define HEATMAP_H

#include <vector>
#include <QSize>

class GameEngine;

class Heatmap {
    public:
        explicit Heatmap(GameEngine &engine, const QSize &heatmapSize);

        void apply(int x, int y, double amount);

        std::vector<double>& operator[](int pos);

    private:
        GameEngine &engine_;
        QSize size_;
        std::vector<std::vector<double>> values_;
};

#endif // HEATMAP_H
