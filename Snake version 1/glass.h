#ifndef GLASS_H
#define GLASS_H

#include <QWidget>
#include <QColor>
#include <QVector>
#include <QTime>
#include <QMessageBox>
#include <QPainter>
#include <QKeyEvent>
#include <QTimerEvent>
#include <QPaintEvent>
#include <QDebug>
#include "target.h"
#include "snake.h"

class Glass : public QWidget
{
    QColor emptyCellColor;
    const uint rows = 15;
    const uint columns = 20;
    const uint cellSize = 40;

    Target myTarget;
    Snake mySnake;

    direction myDirection;

    uint startLength;
    QColor currentColor;
    QColor nextColor;

    bool gameOn;
    bool gameOver;
    int myTimerID;
    uint score;
    uint interval;


    Q_OBJECT
public:
    explicit Glass(QWidget *parent = nullptr);
    ~Glass();

signals:

    void ScoreUp(int);

public slots:

    void NewGameSlot();
    void PauseSlot();

protected:
    virtual void timerEvent(QTimerEvent *event) override;
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;
};

#endif // GLASS_H
