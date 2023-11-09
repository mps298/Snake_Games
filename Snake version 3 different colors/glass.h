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
#include "mypoint.h"

enum direction { Leftwards,Rightwards,Upwards,Downwards };

class Glass : public QWidget
{
    QColor emptyCellColor;
    const uint rows = 15;
    const uint columns = 20;
    const uint cellSize = 40;

    MyPoint nextTarget;
    direction myDirection;

    QVector<MyPoint> mySnake;
    QVector<QColor> mySnakeColors;

    uint startLength;
    QColor currentColor;
    QColor nextColor;

    bool gameOn;
    int myTimerID;
    uint score;
    uint interval;


    Q_OBJECT
public:
    explicit Glass(QWidget *parent = nullptr);
    QColor SetNewColor();

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
