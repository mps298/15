#ifndef FIELDVIEW_H
#define FIELDVIEW_H

#include <QWidget>
#include <QPoint>
#include <QDebug>
#include <QVector>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QRect>



class fieldView : public QWidget
{
    Q_OBJECT


    int fieldSideLength;
    int cellSize;

    QVector<QPoint> myCells;
    QVector<QPoint> arrangedCells;

public:
    explicit fieldView(QWidget *parent = nullptr);

    int getFieldSideLength() const;
    void setFieldSideLength(int value);

signals:

    void gameOverSignal();

public slots:

    void resetCells(int length);
    void messCells();

    // QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;
};

#endif // FIELDVIEW_H
