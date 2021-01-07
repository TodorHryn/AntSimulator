#include "gameview.h"
#include "ui_gameview.h"
#include <QSize>
#include <QPainter>

GameView::GameView(QWidget *parent) : QWidget(parent), ui(new Ui::GameView), terrain_(QSize(200, 100)) {
    ui->setupUi(this);
}

GameView::~GameView() {
    delete ui;
}

void GameView::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QSizeF size_ = painter.window().size();

    double tileSize = std::min(size_.width() / terrain_.size().width(), size_.height() / terrain_.size().height());
    QPoint shift((size_.width() - terrain_.size().width() * tileSize) / 2, size_.height() - terrain_.size().height() * tileSize);

    painter.save();
    painter.fillRect(0, 0, painter.device()->width(), painter.device()->height(), Tiles::SKY.color);
    painter.translate(shift);

    for (int x = 0; x < terrain_.size().width(); ++x) {
        for (int y = 0; y < terrain_.size().height(); ++y) {
            painter.fillRect(x * tileSize, y * tileSize, ceil(tileSize), ceil(tileSize), terrain_.tile(x, y).color);
        }
    }
    painter.drawLine(0, 0, 0, terrain_.size().height() * tileSize);
    painter.drawLine(terrain_.size().width() * tileSize, 0, terrain_.size().width() * tileSize, terrain_.size().height() * tileSize);

    painter.restore();
}
