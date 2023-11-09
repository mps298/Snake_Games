#ifndef SNAKE_H
#define SNAKE_H
#include "mypoint.h"
#include "target.h"
#include <QVector>
#include <QColor>
#include <QMessageBox>

enum direction { Leftwards,Rightwards,Upwards,Downwards };

class Snake
{
     QVector<MyPoint> mySnake;
     QVector<QColor> myColors;
public:
    Snake() = default;

    QVector<MyPoint> getMySnake() const;

    void setMySnake(uint row, uint startLength);

    QColor getMyColor() const;
    void setColor(const QColor color);

    MyPoint& moveSnake(direction myDirection, uint rows, uint columns);
    void eatTarget(direction myDirection, uint rows, uint columns);

    MyPoint& operator[](int index);

    void SetNewRandomColor();

    int getSnakeSize();
    QColor& getSnakeCellColor(int index);

    void clearSnake();

};



#endif // SNAKE_H
