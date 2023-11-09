#ifndef TARGETR_H
#define TARGETR_H

#include "mypoint.h"
#include <QColor>


class MyTarget

{
    MyPoint myTarget;
    QColor myColor;
public:
    MyTarget() = default;
    MyTarget(const MyPoint& other);
    MyTarget(const MyTarget& other);
    MyTarget(MyTarget&& other);
    MyTarget(uint c, uint r);
    MyPoint getTarget() const;
    void setTarget(const MyPoint &value);
    void setNewTarget(uint columns, uint rows);

    QColor getColor() const;
    void setColor(const QColor &value);
    void setNewRandomColor();

    bool operator==(const MyTarget& other);
    bool operator==(const MyPoint& other);
    bool operator!=(const MyTarget& other);
    bool operator!=(const MyPoint& other);
    MyTarget& operator=(const MyTarget& other);
    MyTarget& operator=(const MyPoint& other);
};

#endif // TARGETR_H
