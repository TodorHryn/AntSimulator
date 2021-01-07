#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QWidget>
#include "terrain.h"

namespace Ui {
class GameView;
}

class GameView : public QWidget {
    Q_OBJECT

    public:
        explicit GameView(QWidget *parent = nullptr);
        ~GameView();

        void paintEvent(QPaintEvent *event) override;

    private:
        Ui::GameView *ui;

        Terrain terrain_;
};

#endif // GAMEVIEW_H
