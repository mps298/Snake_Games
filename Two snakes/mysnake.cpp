#include "mysnake.h"
#include "mypoint.h"

direction MySnake::getMyDirection() const
{
    return myDirection;
}

void MySnake::setMyDirection(const direction &value)
{
    myDirection = value;
}

QVector<MyPoint> MySnake::getMySnake() const
{
    return mySnake;
}

void MySnake::setMySnake(uint row, uint startLength)
{
    for (uint i = 0; i < startLength; i++)
    {
        mySnake.push_front(MyPoint(i,row));
    }

    myColors.resize(startLength);
    setNewRandomColor();
}


QColor MySnake::getMyColor() const
{
    return myColors[0];
}

void MySnake::setColor(const QColor color)
{
    for (int i = 0; i<myColors.size(); i++)
    {
        myColors[i] = QColor (color.red(),color.green(),color.blue(),255-(200/myColors.size()*i));
    }
}


MyPoint &MySnake::moveSnake(uint rows, uint columns)
{
    MyPoint tmp;
    switch (myDirection) {
    case direction::Rightwards:
        tmp.setX((mySnake[0].getX()+1)%columns);
        tmp.setY(mySnake[0].getY()); break;
    case direction::Leftwards:
        tmp.setX(mySnake[0].getX()-1);
        if (tmp.getX() == -1) {tmp.setX(columns - 1);}
        tmp.setY(mySnake[0].getY()); break;
    case direction::Downwards:
        tmp.setX(mySnake[0].getX());
        tmp.setY((mySnake[0].getY() + 1)%rows); break;
    case direction::Upwards:
        tmp.setX(mySnake[0].getX());
        tmp.setY(mySnake[0].getY() - 1);
        if (tmp.getY() == -1) {tmp.setY(rows - 1);} break;
    default:
        break;
    }
    mySnake.push_front(tmp);
    mySnake.pop_back();

    return mySnake[0];
}

void MySnake::eatTarget(uint rows, uint columns)
{
    MyPoint tmp;
    switch (myDirection) {
    case direction::Rightwards:
        tmp.setX((mySnake[0].getX()+1)%columns);
        tmp.setY(mySnake[0].getY()); break;
    case direction::Leftwards:
        tmp.setX(mySnake[0].getX()-1);
        if (tmp.getX() == -1) {tmp.setX(columns - 1);}
        tmp.setY(mySnake[0].getY()); break;
    case direction::Downwards:
        tmp.setX(mySnake[0].getX());
        tmp.setY((mySnake[0].getY() + 1)%rows); break;
    case direction::Upwards:
        tmp.setX(mySnake[0].getX());
        tmp.setY(mySnake[0].getY() - 1);
        if (tmp.getY() == -1) {tmp.setY(rows - 1);} break;
    default:
        break;
    }
    mySnake.push_front(tmp);
    myColors.resize(myColors.size()+1);
}

MyPoint &MySnake::operator[](int index)
{
    if (index>=0 && index<mySnake.size())
    {
        return mySnake[index];
    }
    else
    {
        throw "Wrong Index!";
    }
}

void MySnake::setNewRandomColor()
{
    qsrand(QTime::currentTime().msec());

    QColor tmpColor;
    switch (qrand()%6)
    {
        case 0: tmpColor = Qt::darkBlue; break;
        case 1: tmpColor = Qt::darkCyan;break;
        case 2: tmpColor = Qt::darkGreen;break;
        case 3: tmpColor = Qt::darkMagenta;break;
        case 4: tmpColor = Qt::darkRed;break;
        case 5: tmpColor = Qt::darkYellow;break;
    default: tmpColor = Qt::black;break;
    }
    for (int i = 0; i<myColors.size(); i++)
    {
        myColors[i] = QColor (tmpColor.red(),tmpColor.green(),tmpColor.blue(),255-(200/myColors.size()*i));
    }
}

int MySnake::getSnakeSize()
{
    return mySnake.size();
}

QColor &MySnake::getSnakeCellColor(int index)
{
    return myColors[index];
}

void MySnake::clearSnake()
{
    mySnake.clear();
}
