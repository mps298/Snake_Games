#include "glass.h"

Glass::Glass(QWidget *parent) : QWidget(parent)
{
    emptyCellColor = Qt::lightGray;
    gameOn = false;
    gameOver = true;
    score = 0;
    myTimerID = 0;


    setFixedSize(columns*cellSize, rows*cellSize);
}

Glass::~Glass()
{

}


void Glass::NewGameSlot()
{
    if (myTimerID)
    {
        killTimer(myTimerID);
        myTimerID = 0;
    }

    myTarget = MyPoint(columns/2, rows/2);

    startLength = 3;


        if (mySnake.getSnakeSize())
        {
            mySnake.clearSnake();
        }


    mySnake.setMySnake(rows/2, startLength);

    mySnake.SetNewRandomColor();

    do
    {
        myTarget.SetNewRandomColor();
    }
    while (mySnake.getMyColor() == myTarget.getColor());

    interval = 300;
    score = 0;
    emit ScoreUp(score);
    myTimerID = startTimer(interval);
    gameOn = true;
    gameOver = false;
    myDirection = Rightwards;
    setFocus();
}

void Glass::PauseSlot()
{
    if (!gameOver)
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
}

void Glass::timerEvent(QTimerEvent *event)
{

    if (gameOn)
    {
        if (myTarget == mySnake.moveSnake(myDirection,rows,columns))
        {
            mySnake.eatTarget(myDirection,rows,columns);
            mySnake.setColor(myTarget.getColor());

            do
            {
                myTarget.SetNewRandomColor();
            }
            while (mySnake.getMyColor() == myTarget.getColor());

            interval-=(interval/100);
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
                myTarget.setNewTarget(columns,rows);
                for (const auto& point: mySnake.getMySnake())
                {
                    if (myTarget == point)
                    {
                        correctTarget = false;
                        break;
                    }
                }
            }
            while (!correctTarget);
        }


        bool snakeCrossed = false;

        for (int i = 1; i < mySnake.getSnakeSize(); i++)
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
            gameOver = true;

            QMessageBox* gameOverMessage = new QMessageBox;
            gameOverMessage->setIconPixmap(QPixmap(":/myImages/Images/iconExit.ico"));
            gameOverMessage->setWindowTitle("");

            QString scoreString;
            scoreString.setNum(score);
            gameOverMessage->setText(tr("GAME OVER\nYour score is ") + QString::number(score));
            gameOverMessage->exec();

            delete gameOverMessage;
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

    for (int i = 0; i<mySnake.getSnakeSize(); i++)
    {
        QRect tmp(QPoint(mySnake[i].getX()*cellSize, mySnake[i].getY()*cellSize),QSize(cellSize,cellSize));
        painter.fillRect(tmp,mySnake.getSnakeCellColor(i));
    }

    if (gameOn)
    {
        QRect targetRect(QPoint(myTarget.getTarget().getX()*cellSize, myTarget.getTarget().getY()*cellSize),QSize(cellSize,cellSize));
        painter.fillRect(targetRect,myTarget.getColor());
    }
}
