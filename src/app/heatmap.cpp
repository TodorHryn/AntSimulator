#include "heatmap.h"
#include "gameengine.h"
#include <queue>
#include <algorithm>

Heatmap::Heatmap(GameEngine &engine, const QSize &heatmapSize) : engine_(engine), size_(heatmapSize) {
    values_.resize(size_.width());

    for (int i = 0; i < size_.width(); ++i)
        values_[i].resize(size_.height(), 0);
}

void Heatmap::apply(int x, int y, long long amount) {
    std::queue<std::pair<int, int>> updateQueue;
    updateQueue.push(std::make_pair(x - 1, y));
    updateQueue.push(std::make_pair(x + 1, y));
    updateQueue.push(std::make_pair(x, y - 1));
    updateQueue.push(std::make_pair(x, y + 1));
    values_[x][y] = amount;

    while (!updateQueue.empty()) {
        int x = updateQueue.front().first;
        int y = updateQueue.front().second;
        bool updated = false;
        updateQueue.pop();

        if (x < 0 || y < 0 || x > size_.width() - 1 || y > size_.height() - 1)
            continue;

        if (x > 0 && values_[x - 1][y] / 2 > values_[x][y] && values_[x - 1][y] >= 2) {
            values_[x][y] = values_[x - 1][y] / 2;
            updated = true;
        }

        if (x < size_.width() - 1 && values_[x + 1][y] / 2 > values_[x][y] && values_[x + 1][y] >= 2) {
            values_[x][y] = values_[x + 1][y] / 2;
            updated = true;
        }

        if (y > 0 && values_[x][y - 1] / 2 > values_[x][y] && values_[x][y - 1] >= 2) {
            values_[x][y] = values_[x][y - 1] / 2;
            updated = true;
        }

        if (y < size_.height() - 1 && values_[x][y + 1] / 2 > values_[x][y] && values_[x][y + 1] >= 2) {
            values_[x][y] = values_[x][y + 1] / 2;
            updated = true;
        }

        if (updated) {
            updateQueue.push(std::make_pair(x - 1, y));
            updateQueue.push(std::make_pair(x + 1, y));
            updateQueue.push(std::make_pair(x, y - 1));
            updateQueue.push(std::make_pair(x, y + 1));
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
