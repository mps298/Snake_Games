#ifndef MYPOINT_H
#define MYPOINT_H

#include <QtCore>


class MyPoint
{
    int X;
    int Y;

public:
    MyPoint() = default;
    MyPoint(uint x, uint y):X(x),Y(y){}

    bool operator ==(const MyPoint& other)  {
        return (X == other.X && Y == other.Y); }
    bool operator !=(const MyPoint& other)  {
        return !(X == other.X && Y == other.Y); }

    MyPoint& operator =(const MyPoint& other)
    {
        X = other.X;
        Y = other.Y;
        return *this;
    }
    int getX() const;
    void setX(const int &value);
    void setY(const int &value);
    int getY() const;
};

#endif // MYPOINT_H
