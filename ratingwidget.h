#ifndef RATINGWIDGET_H
#define RATINGWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include "item.h"

class RatingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RatingWidget(QWidget *parent = 0);
    int m_rate;
    void setRate(int rate) { m_rate = rate; }
    int rate(void) { return m_rate; }
    QSize sizeHint() const { return QSize(100, 20); }
    int rateAt(int pos);
signals:
    void editingFinished();
protected:
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
public slots:

    // QWidget interface
protected:
};
#endif // RATINGWIDGET_H

