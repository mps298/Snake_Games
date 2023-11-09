#ifndef SNAKE_H
#define SNAKE_H
#include "mypoint.h"
#include "mytarget.h"
#include <QVector>
#include <QColor>
#include <QMessageBox>

enum class direction { Leftwards,Rightwards,Upwards,Downwards };

class MySnake
{
     QVector<MyPoint> mySnake;
     QVector<QColor> myColors;
     direction myDirection;
public:
    MySnake() = default;



    void setMySnake(uint row, uint startLength);

    QColor getMyColor() const;
    void setColor(const QColor color);

    MyPoint& moveSnake(uint rows, uint columns);
    void eatTarget(uint rows, uint columns);

    MyPoint& operator[](int index);

    void setNewRandomColor();

    int getSnakeSize();
    QColor& getSnakeCellColor(int index);

    void clearSnake();

    direction getMyDirection() const;
    void setMyDirection(const direction &value);

    QVector<MyPoint> getMySnake() const;
};



#endif // SNAKE_H
