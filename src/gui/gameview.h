#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include "gameengine.h"
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
        GameEngine engine_;
};

#endif // GAMEVIEW_H
