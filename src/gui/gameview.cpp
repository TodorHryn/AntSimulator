#include "gameview.h"
#include "ui_gameview.h"
#include <QSize>
#include <QPainter>
#include <iostream>
#include <QtMath>

GameView::GameView(QWidget *parent) : QWidget(parent), ui(new Ui::GameView), engine_(QSize(200, 100)) {
    ui->setupUi(this);

    for (int i = 0; i < 1000; ++i)
        engine_.ants().emplace_back(engine_, QVector2D(50, 50));

    engine_.addFood(Food(QVector2D(100, 50), 50));
    engine_.addFood(Food(QVector2D(22, 56), 50));

    tickTimer_ = new QTimer(this);
    connect(tickTimer_, SIGNAL(timeout()), this, SLOT(nextTick()));
    tickTimer_->start(1000.0 / 60);
}

GameView::~GameView() {
    delete ui;
}

QColor getGradient(double level, double maxLevel) {
    QColor color;

    if (level < maxLevel / 2)
        color = QColor::fromRgb(level / (maxLevel / 2) * 255, 255, 0);
    else
        color = QColor::fromRgb(255, (2 - level / (maxLevel / 2)) * 255, 0);

    color.setAlpha(sqrt(level / maxLevel) * 255);
    return color;
}

void GameView::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QSizeF size_ = painter.window().size();
    Terrain &terrain = engine_.terrain();

    double tileSize = std::min(size_.width() / terrain.size().width(), size_.height() / terrain.size().height());
    QPoint shift((size_.width() - terrain.size().width() * tileSize) / 2, size_.height() - terrain.size().height() * tileSize);

    painter.save();
    painter.fillRect(0, 0, painter.device()->width(), painter.device()->height(), Tiles::SKY.color);
    painter.translate(shift);

    long long maxHeatmapValue = 1;
    for (int x = 0; x < terrain.size().width(); ++x) {
        for (int y = 0; y < terrain.size().height(); ++y) {
            maxHeatmapValue = std::max(maxHeatmapValue, engine_.foodHeatmap()[x][y]);
        }
    }

    painter.setCompositionMode(QPainter::CompositionMode_SourceAtop);
    for (int x = 0; x < terrain.size().width(); ++x) {
        for (int y = 0; y < terrain.size().height(); ++y) {
            double tileH = tileSize * terrain.tile(x, y).fillLevel / UINT8_MAX;

            painter.fillRect(x * tileSize, y * tileSize + (tileSize - tileH), ceil(tileSize), ceil(tileH), terrain.tile(x, y).color);
            painter.fillRect(x * tileSize, y * tileSize, ceil(tileSize), ceil(tileSize), getGradient(engine_.foodHeatmap()[x][y], maxHeatmapValue));
        }
    }
    painter.drawLine(0, 0, 0, terrain.size().height() * tileSize);
    painter.drawLine(terrain.size().width() * tileSize, 0, terrain.size().width() * tileSize, terrain.size().height() * tileSize);

    painter.setBrush(Qt::black);
    for (Ant &ant : engine_.ants()) {
        painter.drawEllipse(ant.position().x() * tileSize, ant.position().y() * tileSize, 10, 10);
        painter.drawEllipse((ant.position().x() + ant.forwardDirection().x() * 0.45) * tileSize, (ant.position().y() + ant.forwardDirection().y() * 0.45) * tileSize, 10, 10);

        if (ant.foodCarried() != 0)
            painter.setBrush(Qt::green);

        painter.drawEllipse((ant.position().x() + ant.forwardDirection().x() * 0.9) * tileSize, (ant.position().y() + ant.forwardDirection().y() * 0.9) * tileSize, 10, 10);

        if (ant.foodCarried() != 0)
            painter.setBrush(Qt::black);
    }

    painter.setPen(Qt::darkGreen);
    painter.setBrush(Qt::darkGreen);
    for (Food &food : engine_.food()) {
        painter.drawEllipse(food.position().x() * tileSize, food.position().y() * tileSize, 10, 10);
    }

    painter.restore();
}

void GameView::nextTick() {
    engine_.tick();
    update();
}
