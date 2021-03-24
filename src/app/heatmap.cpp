#include "heatmap.h"
#include "gameengine.h"

Heatmap::Heatmap(GameEngine &engine, const QSize &heatmapSize) : engine_(engine), size_(heatmapSize) {
    values_.resize(size_.width());

    for (int i = 0; i < size_.width(); ++i)
        values_[i].resize(size_.height(), 0);
}

void Heatmap::apply(int x, int y, long long amount) {
    int fragmentSize = ceil(log2(amount));

    int x1 = std::max(0, x - fragmentSize);
    int y1 = std::max(0, y - fragmentSize);
    int x2 = std::min(size_.width() - 1, x + fragmentSize);
    int y2 = std::min(size_.height() - 1, y + fragmentSize);

    bool updated;
    std::vector<std::vector<long long>> fragment(fragmentSize * 2 + 1);
    for (int i = 0; i < fragmentSize * 2 + 1; ++i)
        fragment[i].resize(fragmentSize * 2 + 1, 0);
    fragment[x - x1][y - y1] = amount;

    do {
        updated = false;

        for (int x = x1; x <= x2; ++x) {
            for (int y = y1; y <= y2; ++y) {
                if (engine_.terrain().tile(x, y).empty()) {
                    double val = fragment[x - x1][y - y1];

                    if (x > x1 && fragment[x - x1 - 1][y - y1] / 2 > val && fragment[x - x1 - 1][y - y1] >= 2) {
                        val = fragment[x - x1 - 1][y - y1] / 2;
                        updated = true;
                    }

                    if (x < x2 && fragment[x - x1 + 1][y - y1] / 2 > val && fragment[x - x1 + 1][y - y1] >= 2) {
                        val = fragment[x - x1 + 1][y - y1] / 2;
                        updated = true;
                    }

                    if (y > y1 && fragment[x - x1][y - y1 - 1] / 2 > val && fragment[x - x1][y - y1 - 1] >= 2) {
                        val = fragment[x - x1][y - y1 - 1] / 2;
                        updated = true;
                    }

                    if (y < y2 && fragment[x - x1][y - y1 + 1] / 2 > val && fragment[x - x1][y - y1 + 1] >= 2) {
                        val = fragment[x - x1][y - y1 + 1] / 2;
                        updated = true;
                    }

                    fragment[x - x1][y - y1] = val;
                }
            }
        }
    }
    while (updated);

    for (int x = x1; x <= x2; ++x) {
        for (int y = y1; y <= y2; ++y) {
            values_[x][y] = std::max(values_[x][y], fragment[x - x1][y - y1]);
        }
    }
}

void Heatmap::clear() {
    for (int x = 0; x < size_.width(); ++x)
        for (int y = 0; y < size_.height(); ++y)
            values_[x][y] = 0;
}

std::vector<long long>& Heatmap::operator[](int pos) {
    return values_[pos];
}

const std::vector<long long> &Heatmap::operator[](int pos) const {
    return values_[pos];
}
