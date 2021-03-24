#ifndef HEATMAP_H
#define HEATMAP_H

#include <vector>
#include <QSize>

class GameEngine;

class Heatmap {
    public:
        explicit Heatmap(GameEngine &engine, const QSize &heatmapSize);

        void apply(int x, int y, long long amount);
        void clear();

        std::vector<long long>& operator[](int pos);
        const std::vector<long long>& operator[](int pos) const;

    private:
        GameEngine &engine_;
        QSize size_;
        std::vector<std::vector<long long>> values_;
};

#endif // HEATMAP_H
