#include "glass.h"


MySnake &Glass::getActiveSnake()
{
    if (myActiveSnake == ActiveSnake::First)
    {   return mySnake_1;    }
    else
    {   return mySnake_2;    }
}

MySnake &Glass::getPassiveSnake()
{
    if (myActiveSnake == ActiveSnake::First)
    {   return mySnake_2;    }
    else
    {   return mySnake_1;    }
}

Glass::Glass(QWidget *parent) : QWidget(parent)
{
//    emptyCellColor = Qt::lightGray;
    gameOn = false;
    gameOver = false;
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


    if (mySnake_1.getSnakeSize())
        {   mySnake_1.clearSnake(); }

    if (mySnake_2.getSnakeSize())
        {   mySnake_2.clearSnake(); }


    mySnake_1.setMySnake(rows/3, startLength);
    mySnake_2.setMySnake(rows/3*2, startLength);

    mySnake_1.setNewRandomColor();

    do
    {   mySnake_2.setNewRandomColor();  }
    while (mySnake_1.getMyColor() == mySnake_2.getMyColor());

    do
    {   myTarget.setNewRandomColor();   }
    while (mySnake_1.getMyColor() == myTarget.getColor() || mySnake_2.getMyColor() == myTarget.getColor());

    myActiveSnake = ActiveSnake::First;

    mySnake_1.setMyDirection(direction::Rightwards);
    mySnake_2.setMyDirection(direction::Rightwards);


    interval = 300;
    score = 0;
    emit ScoreUp(score);
    myTimerID = startTimer(interval);
    gameOn = true;
    gameOver = false;
    snakeCrossed = false;

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
        if (myTarget == getActiveSnake().moveSnake(rows,columns))
        {
            getActiveSnake().eatTarget(rows,columns);
            getActiveSnake().setColor(myTarget.getColor());

            do
            {   myTarget.setNewRandomColor();   }
            while (getActiveSnake().getMyColor() == myTarget.getColor()
                   || getPassiveSnake().getMyColor() == myTarget.getColor());

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
                for (const auto& point: mySnake_1.getMySnake())
                {
                    if (myTarget == point)
                    {
                    correctTarget = false;
                    break;
                    }
                }
                for (const auto& point: mySnake_2.getMySnake())
                {
                    if (myTarget == point)
                    {
                    correctTarget = false;
                    break;
                    }
                }
            }
            while (!correctTarget);

            if (myActiveSnake == ActiveSnake::First)
            {   myActiveSnake = ActiveSnake::Second;    }
            else
            {   myActiveSnake = ActiveSnake::First;     }
        }

        for (int i = 1; i < getActiveSnake().getSnakeSize(); i++)
        {
            if (getActiveSnake()[0] == getActiveSnake()[i])
            {
                gameOver = true;
                break;
            }
        }

        if (!gameOver)
        {
            for (int i = 0; i < getPassiveSnake().getSnakeSize(); i++)
            {
                if (getActiveSnake()[0] == getPassiveSnake()[i])
                {
                    gameOver = true;
                    break;
                }
            }
        }

        if (gameOver)
        {
            if (myTimerID)
            {
                killTimer(myTimerID);
                myTimerID = 0;
                gameOn = false;
            }

            QMessageBox* gameOverMessage = new QMessageBox;
            gameOverMessage->setIconPixmap(QPixmap(":/myImages/Images/iconExit.ico"));
            gameOverMessage->setWindowTitle(tr("Snake"));

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
                if (getActiveSnake().getMyDirection() == direction::Upwards || getActiveSnake().getMyDirection() == direction::Downwards)
                {
                   getActiveSnake().setMyDirection(direction::Leftwards);
                } break;

            case Qt::Key_Right:
                if (getActiveSnake().getMyDirection() == direction::Upwards || getActiveSnake().getMyDirection() == direction::Downwards)
                {
                   getActiveSnake().setMyDirection(direction::Rightwards);
                } break;

            case Qt::Key_Up:
                if (getActiveSnake().getMyDirection() == direction::Leftwards || getActiveSnake().getMyDirection() == direction::Rightwards)
                {
                   getActiveSnake().setMyDirection(direction::Upwards);
                } break;

            case Qt::Key_Down:
                if (getActiveSnake().getMyDirection() == direction::Leftwards || getActiveSnake().getMyDirection() == direction::Rightwards)
                {
                   getActiveSnake().setMyDirection(direction::Downwards);
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

    for (int row = 0; row < rows; row++)
    {
        for (int col = 0; col < columns; col++)
        {
            QRect glassRect(QPoint(col*cellSize, row*cellSize),QSize(cellSize,cellSize));
            painter.drawPixmap(glassRect, QPixmap(":/Images/zero.png"));
        }
    }

    for (int i = 0; i<getActiveSnake().getSnakeSize(); i++)
    {
        QRect tmpRect(QPoint(getActiveSnake()[i].getX()*cellSize, getActiveSnake()[i].getY()*cellSize),QSize(cellSize,cellSize));
        painter.fillRect(tmpRect,getActiveSnake().getSnakeCellColor(i));
    }

    QColor passiveColor = Qt::darkGray;
    for (int i = 0; i<getPassiveSnake().getSnakeSize(); i++)
    {
        QRect tmp(QPoint(getPassiveSnake()[i].getX()*cellSize, getPassiveSnake()[i].getY()*cellSize),QSize(cellSize,cellSize));
        painter.fillRect(tmp, QColor (passiveColor.red(),passiveColor.green(),passiveColor.blue(),255-(200/getPassiveSnake().getSnakeSize()*i)));
    }

    if (gameOn)
    {
        QRect targetRect(QPoint(myTarget.getTarget().getX()*cellSize, myTarget.getTarget().getY()*cellSize),QSize(cellSize,cellSize));
        painter.fillRect(targetRect,myTarget.getColor());
    }
    if (gameOver)
    {
        QRect targetRect(QPoint(getActiveSnake()[0].getX()*cellSize, getActiveSnake()[0].getY()*cellSize),QSize(cellSize,cellSize));
        painter.fillRect(targetRect,Qt::red);
    }
}
