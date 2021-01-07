#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include "terrain.h"
#include <QWidget>
#include <QTimer>

namespace Ui {
class GameView;
}

class GameView : public QWidget {
    Q_OBJECT

    public:
        explicit GameView(QWidget *parent = nullptr);
        ~GameView();

        void paintEvent(QPaintEvent *event) override;

    private slots:
        void nextTick();

    private:
        Ui::GameView *ui;

        QTimer *tickTimer_;
        Terrain terrain_;
};

#endif // GAMEVIEW_H
