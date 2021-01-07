#include "gameview.h"
#include "ui_gameview.h"
#include <QSize>
#include <QPainter>

GameView::GameView(QWidget *parent) : QWidget(parent), ui(new Ui::GameView), terrain_(QSize(200, 100)) {
    ui->setupUi(this);

    tickTimer_ = new QTimer(this);
    connect(tickTimer_, SIGNAL(timeout()), this, SLOT(nextTick()));
    tickTimer_->start(1000.0 / 600);
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

    double tileSize = std::min(size_.width() / terrain_.size().width(), size_.height() / terrain_.size().height());
    QPoint shift((size_.width() - terrain_.size().width() * tileSize) / 2, size_.height() - terrain_.size().height() * tileSize);

    painter.save();
    painter.fillRect(0, 0, painter.device()->width(), painter.device()->height(), Tiles::SKY.color);
    painter.translate(shift);

    double maxLevel = 0;
    for (int x = 0; x < terrain_.size().width(); ++x)
        for (int y = 0; y < terrain_.size().height(); ++y)
            maxLevel = std::max(maxLevel, terrain_.waterHeatmap()[x][y]);

    painter.setCompositionMode(QPainter::CompositionMode_SourceAtop);
    for (int x = 0; x < terrain_.size().width(); ++x) {
        for (int y = 0; y < terrain_.size().height(); ++y) {
            double tileH = tileSize * terrain_.tile(x, y).fillLevel / UINT8_MAX;

            painter.fillRect(x * tileSize, y * tileSize + (tileSize - tileH), ceil(tileSize), ceil(tileH), terrain_.tile(x, y).color);
            //painter.fillRect(x * tileSize, y * tileSize, ceil(tileSize), ceil(tileSize), getGradient(terrain_.waterHeatmap()[x][y], maxLevel));
        }
    }
    painter.drawLine(0, 0, 0, terrain_.size().height() * tileSize);
    painter.drawLine(terrain_.size().width() * tileSize, 0, terrain_.size().width() * tileSize, terrain_.size().height() * tileSize);

    painter.restore();
}

void GameView::nextTick() {
    terrain_.tick();
    update();
}
