#include "fieldview.h"

int fieldView::getFieldSideLength() const
{
    return fieldSideLength;
}

void fieldView::setFieldSideLength(int value)
{
    fieldSideLength = value;
}

fieldView::fieldView(QWidget *parent) : QWidget(parent)
{
    resize(400,400);

    resetCells(4);
}

void fieldView::resetCells(int length)
{
    fieldSideLength = length;
    cellSize = width()/fieldSideLength;
    qDebug()<<height();
    qDebug()<<cellSize;

    myCells = QVector<QPoint>(fieldSideLength*fieldSideLength);
    arrangedCells = QVector<QPoint>(fieldSideLength*fieldSideLength);

    arrangedCells[0] = QPoint((fieldSideLength-1)*cellSize,(fieldSideLength-1)*cellSize);

    for (int i = 0; i < fieldSideLength*fieldSideLength-1; i++)
    {
        arrangedCells[i+1] = QPoint((i%fieldSideLength)*cellSize,((i-i%fieldSideLength)/fieldSideLength)*cellSize);
    }

    myCells = arrangedCells;

    repaint();
}

void fieldView::messCells()
{
    int moves = fieldSideLength*250;

    qDebug()<<"moves = "<<moves;

    for (int i = 0; i < moves; i++)
    {
        auto it = myCells.begin();

        switch (qrand()%4) {
        case 0 : //empty cell goes rightwards
        {
            if (myCells.at(0).x()!=(fieldSideLength-1)*cellSize)
            {
                while (*it!=QPoint(myCells.at(0).x()+cellSize, myCells.at(0).y()))
                {
                    ++it;
                }
            }
            break;
        }
        case 1 : //empty cell goes leftwards
        {
            if (myCells.at(0).x())
            {
                while (*it!=QPoint(myCells.at(0).x()-cellSize, myCells.at(0).y()))
                {
                    ++it;
                }
            }
            break;
        }
        case 2 : //empty cell goes downwards
        {
            if (myCells.at(0).y()!=(fieldSideLength-1)*cellSize)
            {
                while (*it!=QPoint(myCells.at(0).x(), myCells.at(0).y()+cellSize))
                {
                    ++it;
                }
            }
            break;
        }

        case 3 : //empty cell goes upwards
        {
            if (myCells.at(0).y())
            {
                while (*it!=QPoint(myCells.at(0).x(), myCells.at(0).y()-cellSize))
                {
                    ++it;
                }
            }
            break;
        }


        default:
            break;
        }

        QPoint tmpPoint = *it;
        *it = myCells.at(0);
        myCells[0] = tmpPoint;

        repaint();
    }
}

void fieldView::mousePressEvent(QMouseEvent *event)
{
    if (myCells==arrangedCells) { return; }

    int currentX = event->pos().x();
    while (currentX%cellSize) {    currentX--;    }

    int currentY = event->pos().y();
    while (currentY%cellSize) {    currentY--;    }

    if (myCells.at(0) == QPoint(currentX,currentY)) { qDebug()<<"zero"; return; }
    if (myCells.at(0).x() != currentX && myCells.at(0).y() != currentY) { qDebug()<<"no-no"; return; }

    const int step = 5;

    QVector<int> cellsToMove;

    if (myCells.at(0).x() > currentX) //a cell goes rightwards
    {
        for (int i = 1; i < myCells.size(); i++)
        {
            if (myCells.at(i).y() == currentY
                && myCells.at(i).x() >= currentX
                && myCells.at(i).x() < myCells.at(0).x())
            {
                cellsToMove.push_back(i);
            }
        }
        qDebug()<<cellsToMove;

        for (int i = 0; i < cellSize/step; i++)
        {
            for (int index: cellsToMove)
            {
                myCells[index].setX(myCells.at(index).x()+step);
            }
            repaint();
        }
    }

    if (myCells.at(0).x() < currentX) //a cell goes leftwards
    {
        for (int i = 1; i < myCells.size(); i++)
        {
            if (myCells.at(i).y() == currentY
                && myCells.at(i).x() <= currentX
                && myCells.at(i).x() > myCells.at(0).x())
            {
                cellsToMove.push_back(i);
            }
        }

        qDebug()<<cellsToMove;



        for (int i = 0; i < cellSize/step; i++)
        {

            for (int index: cellsToMove)
            {
                myCells[index].setX(myCells.at(index).x()-step);
            }
            repaint();
        }
    }

    if (myCells.at(0).y() > currentY) //a cell goes downwards
    {
        for (int i = 1; i < myCells.size(); i++)
        {
            if (myCells.at(i).x() == currentX
                && myCells.at(i).y() >= currentY
                && myCells.at(i).y() < myCells.at(0).y())
            {
                cellsToMove.push_back(i);
            }
        }
        qDebug()<<cellsToMove;

        for (int i = 0; i < cellSize/step; i++)
        {
            for (int index: cellsToMove)
            {
                myCells[index].setY(myCells.at(index).y()+step);
            }
            repaint();
        }
    }

    if (myCells.at(0).y() < currentY) //a cell goes upwards
    {
        for (int i = 1; i < myCells.size(); i++)
        {
            if (myCells.at(i).x() == currentX
                && myCells.at(i).y() <= currentY
                && myCells.at(i).y() > myCells.at(0).y())
            {
                cellsToMove.push_back(i);
            }
        }

        qDebug()<<cellsToMove;

        for (int i = 0; i < cellSize/step; i++)
        {

            for (int index: cellsToMove)
            {
                myCells[index].setY(myCells.at(index).y()-step);
            }
            repaint();
        }
    }

    myCells[0].setX(currentX);
    myCells[0].setY(currentY);

    qDebug()<<"0 = "<<myCells.at(0);
    repaint();

    if (myCells==arrangedCells)
    {
        emit gameOverSignal();
    }
}

void fieldView::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(QPen(QBrush(Qt::darkBlue), 5));
    painter.setFont(QFont("Times", cellSize/3, QFont::Bold));

    for (int i = 0; i < myCells.size(); i++)
    {
        QRect rect = QRect(myCells.at(i), QSize(cellSize,cellSize));
        if  (i) { painter.fillRect(rect, Qt::gray); }

        painter.drawRect(rect);
        if (i)
        {
            QString str;
            str.setNum(i);
            painter.drawText(rect, Qt::AlignCenter, str);
        }
    }
    painter.drawRect(QRect(0,0,cellSize*fieldSideLength,cellSize*fieldSideLength));

}
