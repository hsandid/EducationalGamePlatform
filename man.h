#ifndef BASKET_H
#define BASKET_H

#include <QGraphicsPixmapItem>

class basket : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit basket(QObject *parent = 0);
    void keyPressEvent(QKeyEvent* event);
    
signals:
    
public slots:
    
};

#endif // BASKET_H
