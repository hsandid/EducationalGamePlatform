#ifndef CARD_H
#define CARD_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

/**
 *
 * \file card.h
 * \brief The card class
 */

class card : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit card(QObject *parent = 0);

    bool *hasCard; //!< Check if the user has this card (in case the user has matched cards (NOT USED))
    bool *cardShown; //!< Check if the card is shown (i.e. face up) or not
    int *cardValue; //!< Current Card value in the Cabo game (0-13)



signals:

public slots:
void setPosition(int x, int y, int rotation);
void setCardPic();
};

#endif // CARD_H
