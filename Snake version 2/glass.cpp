#include "glass.h"

Glass::Glass(QWidget *parent) : QWidget(parent)
{
    emptyCellColor = Qt::gray;
    gameOn = false;
    score = 0;
    myTimerID = 0;

    setFixedSize(columns*cellSize, rows*cellSize);
}

QColor Glass::SetNewColor()
{
    switch (rand()%6)
    {
        case 0: return Qt::darkBlue;
        case 1: return Qt::darkCyan;
        case 2: return Qt::darkGreen;
        case 3: return Qt::darkMagenta;
        case 4: return Qt::darkRed;
        case 5: return Qt::darkYellow;
        default: return emptyCellColor;
    }
}

void Glass::NewGameSlot()
{
    if (myTimerID)
    {
        killTimer(myTimerID);
        myTimerID = 0;
    }

    nextTarget = MyPoint(columns/2, rows/2);

    startLength = 3;

    if (mySnake.size())
    {
        mySnake.clear();
    }

    for (uint i = 0; i < startLength; i++)
    {
        mySnake.push_front(MyPoint(i,rows/2));
    }
    currentColor = SetNewColor();

    do
    {
        nextColor = SetNewColor();
    }
    while (nextColor == currentColor);

    interval = 300;
    score = 0;
    emit ScoreUp(score);
    myTimerID = startTimer(interval);
    gameOn = true;
    myDirection = Rightwards;
    setFocus();
}

void Glass::PauseSlot()
{
    if (gameOn)
    {
        if (myTimerID)
        {
            killTimer(myTimerID);
            myTimerID = 0;
        }
        gameOn = false;
    }
    else
    {
        myTimerID = startTimer(interval);
        setFocus();
        gameOn = true;
    }
}

void Glass::timerEvent(QTimerEvent *event)
{

    if (gameOn)
    {
        MyPoint tmp;
        switch (myDirection) {
        case Rightwards:
            tmp.setX((mySnake[0].getX()+1)%columns);
            tmp.setY(mySnake[0].getY()); break;
        case Leftwards:
            tmp.setX(mySnake[0].getX()-1);
            if (tmp.getX() == -1) {tmp.setX(columns - 1);}
            tmp.setY(mySnake[0].getY()); break;
        case Downwards:
            tmp.setX(mySnake[0].getX());
            tmp.setY((mySnake[0].getY() + 1)%rows); break;
        case Upwards:
            tmp.setX(mySnake[0].getX());
            tmp.setY(mySnake[0].getY() - 1);
            if (tmp.getY() == -1) {tmp.setY(rows - 1);} break;
        default:
            break;
        }
        mySnake.push_front(tmp);

        if (mySnake[0]!=nextTarget)
        {
            mySnake.pop_back();
        }
        else
        {
            currentColor = nextColor;

            do
            {
                nextColor = SetNewColor();
            }
            while (nextColor == currentColor);

            interval-=(interval/100);
            qDebug()<<interval;

            score++;
            emit ScoreUp(score);

            if (myTimerID)
            {
                killTimer(myTimerID);
                myTimerID = startTimer(interval);
            }

            bool correctTarget = true;
            do
            {
                correctTarget = true;
                nextTarget = MyPoint(rand()%columns, rand()%rows);
                for (const auto& point: mySnake)
                {
                    if (nextTarget == point)
                    {
                        correctTarget = false;
                        break;
                    }
                }
            }
            while (!correctTarget);
        }

        bool snakeCrossed = false;

        for (int i = 1; i < mySnake.size(); i++)
        {
            if (mySnake[0] == mySnake[i])
            {
                snakeCrossed = true;
                break;
            }
        }

        if (snakeCrossed)
        {
            if (myTimerID)
            {
                killTimer(myTimerID);
                myTimerID = 0;
                gameOn = false;
            }

            QMessageBox* gameOver = new QMessageBox;
            gameOver->setIconPixmap(QPixmap(":/myImages/Images/iconExit.ico"));
            gameOver->setWindowTitle("");

            QString scoreString;
            scoreString.setNum(score);
            gameOver->setText(tr("GAME OVER\nYour score is ") + QString::number(score));
            gameOver->exec();

           delete gameOver;
        }

        repaint();
    }
}

void Glass::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Escape || event->key()==Qt::Key_Space)
    {
        PauseSlot();
    }
    if (gameOn)
    {
        switch (event->key())
        {
            case Qt::Key_Left:
                if (myDirection == Upwards || myDirection == Downwards)
                {
                   myDirection = Leftwards;
                } break;

            case Qt::Key_Right:
                if (myDirection == Upwards || myDirection == Downwards)
                {
                   myDirection = Rightwards;
                } break;

            case Qt::Key_Up:
                if (myDirection == Leftwards || myDirection == Rightwards)
                {
                   myDirection = Upwards;
                } break;

            case Qt::Key_Down:
                if (myDirection == Leftwards || myDirection == Rightwards)
                {
                   myDirection = Downwards;
                } break;

            default: break;
        }
        qDebug()<<myDirection;
    }
    else
    {
        QWidget::keyPressEvent(event);
    }
}

void Glass::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect glassRect(QPoint(0,0),QSize(cellSize*columns,cellSize*rows));
    painter.fillRect(glassRect, emptyCellColor);

    for (int i = 0; i<mySnake.size(); i++)
    {
        QColor tmpColor(currentColor.red(),currentColor.green(),currentColor.blue(),255-(200/mySnake.size()*i));
        QRect tmp(QPoint(mySnake[i].getX()*cellSize, mySnake[i].getY()*cellSize),QSize(cellSize,cellSize));
        painter.fillRect(tmp,tmpColor);
    }

    if (gameOn)
    {
        QRect targetRect(QPoint(nextTarget.getX()*cellSize, nextTarget.getY()*cellSize),QSize(cellSize,cellSize));
        painter.fillRect(targetRect,nextColor);
    }
}
