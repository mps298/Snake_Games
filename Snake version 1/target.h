#ifndef TARGETR_H
#define TARGETR_H

#include "mypoint.h"
#include <QColor>


class Target

{
    MyPoint myTarget;
    QColor myColor;
public:
    Target() = default;
    Target(const MyPoint& other);
    Target(const Target& other);
    Target(Target&& other);
    Target(uint c, uint r);
    MyPoint getTarget() const;
    void setTarget(const MyPoint &value);
    void setNewTarget(uint columns, uint rows);

    QColor getColor() const;
    void setColor(const QColor &value);
    void SetNewRandomColor();

    bool operator==(const Target& other);
    bool operator==(const MyPoint& other);
    bool operator!=(const Target& other);
    bool operator!=(const MyPoint& other);
    Target& operator=(const Target& other);
    Target& operator=(const MyPoint& other);
};

#endif // TARGETR_H
