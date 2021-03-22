#include "gameview.h"
#include "ui_gameview.h"
#include <QSize>
#include <QPainter>

GameView::GameView(QWidget *parent) : QWidget(parent), ui(new Ui::GameView), engine_(QSize(200, 100)) {
    ui->setupUi(this);

    engine_.ants().emplace_back(engine_, QVector2D(50, 50));

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

    painter.setCompositionMode(QPainter::CompositionMode_SourceAtop);
    for (int x = 0; x < terrain.size().width(); ++x) {
        for (int y = 0; y < terrain.size().height(); ++y) {
            double tileH = tileSize * terrain.tile(x, y).fillLevel / UINT8_MAX;

            painter.fillRect(x * tileSize, y * tileSize + (tileSize - tileH), ceil(tileSize), ceil(tileH), terrain.tile(x, y).color);
        }
    }
    painter.drawLine(0, 0, 0, terrain.size().height() * tileSize);
    painter.drawLine(terrain.size().width() * tileSize, 0, terrain.size().width() * tileSize, terrain.size().height() * tileSize);

    painter.setBrush(Qt::black);
    for (Ant& ant : engine_.ants()) {
        painter.drawEllipse(ant.position().x() * tileSize, ant.position().y() * tileSize, 10, 10);
        painter.drawEllipse((ant.position().x() + ant.forwardDirection_.x() * 0.45) * tileSize, (ant.position().y() + ant.forwardDirection_.y() * 0.45) * tileSize, 10, 10);
        painter.drawEllipse((ant.position().x() + ant.forwardDirection_.x() * 0.9) * tileSize, (ant.position().y() + ant.forwardDirection_.y() * 0.9) * tileSize, 10, 10);
    }

    painter.restore();
}

void GameView::nextTick() {
    engine_.tick();
    update();
}
