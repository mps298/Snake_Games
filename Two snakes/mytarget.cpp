#include "mytarget.h"
#include "mypoint.h"

MyPoint MyTarget::getTarget() const
{
    return myTarget;
}

void MyTarget::setTarget(const MyPoint &value)
{
    myTarget = value;
}

void MyTarget::setNewTarget(uint columns, uint rows)
{
    myTarget.setX(rand()%columns);
    myTarget.setY(rand()%rows);
}

QColor MyTarget::getColor() const
{
    return myColor;
}

void MyTarget::setColor(const QColor &value)
{
    myColor = value;
}

void MyTarget::setNewRandomColor()
{
    qsrand(QTime::currentTime().msec());
    switch (rand()%6)
    {
        case 0: myColor = Qt::darkBlue;break;
        case 1: myColor = Qt::darkCyan;break;
        case 2: myColor = Qt::darkGreen;break;
        case 3: myColor = Qt::darkMagenta;break;
        case 4: myColor = Qt::darkRed;break;
        case 5: myColor = Qt::darkYellow;break;
    default: myColor = Qt::black;break;
    }
}

bool MyTarget::operator==(const MyTarget &other)
{
    return myTarget == other.myTarget;
}

bool MyTarget::operator==(const MyPoint &other)
{
    return myTarget == other;
}

bool MyTarget::operator!=(const MyTarget &other)
{
    return myTarget != other.myTarget;
}

bool MyTarget::operator!=(const MyPoint &other)
{
    return myTarget != other;
}

MyTarget& MyTarget::operator=(const MyTarget &other)
{
    myTarget = other.myTarget;
    return *this;
}

MyTarget& MyTarget::operator=(const MyPoint &other)
{
    myTarget = other;
    return *this;
}

MyTarget::MyTarget(const MyPoint &other)
{
    myTarget = other;
}

MyTarget::MyTarget(const MyTarget &other)
{
    myTarget = other.myTarget;
}

MyTarget::MyTarget(MyTarget &&other)
{
    myTarget = other.myTarget;
}

MyTarget::MyTarget(uint c, uint r)
{
    myTarget.setX(c);
    myTarget.setY(r);
}
