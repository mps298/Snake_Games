#include "target.h"
#include "mypoint.h"

MyPoint Target::getTarget() const
{
    return myTarget;
}

void Target::setTarget(const MyPoint &value)
{
    myTarget = value;
}

void Target::setNewTarget(uint columns, uint rows)
{
    myTarget.setX(rand()%columns);
    myTarget.setY(rand()%rows);
}

QColor Target::getColor() const
{
    return myColor;
}

void Target::setColor(const QColor &value)
{
    myColor = value;
}

void Target::SetNewRandomColor()
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

bool Target::operator==(const Target &other)
{
    return myTarget == other.myTarget;
}

bool Target::operator==(const MyPoint &other)
{
    return myTarget == other;
}

bool Target::operator!=(const Target &other)
{
    return myTarget != other.myTarget;
}

bool Target::operator!=(const MyPoint &other)
{
    return myTarget != other;
}

Target& Target::operator=(const Target &other)
{
    myTarget = other.myTarget;
    return *this;
}

Target& Target::operator=(const MyPoint &other)
{
    myTarget = other;
    return *this;
}

Target::Target(const MyPoint &other)
{
    myTarget = other;
}

Target::Target(const Target &other)
{
    myTarget = other.myTarget;
}

Target::Target(Target &&other)
{
    myTarget = other.myTarget;
}

Target::Target(uint c, uint r)
{
    myTarget.setX(c);
    myTarget.setY(r);
}
