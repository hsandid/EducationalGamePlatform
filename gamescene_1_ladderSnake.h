#ifndef GAMESCENE_1_LADDERSNAKE_H
#define GAMESCENE_1_LADDERSNAKE_H

#include <QtMath>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

/**
 *
 * \file gamescene_1_laddersnake.h
 * \brief The gamescene_1_ladderSnake class
 */

class gamescene_1_ladderSnake : public QObject , public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit gamescene_1_ladderSnake(QObject *parent = 0);
    QPixmap * image; //!< Image associated to ladder/snake
    int *id; //!< Id associated to ladder/snake
    bool *goForward; //!< Bool associated to movement logic
    int *posXstart; //!< Temp value used in calculations across functions
    int *posXend;//!< Temp value used in calculations across functions
    int *posYstart;//!< Temp value used in calculations across functions
    int *posYend;//!< Temp value used in calculations across functions
    int *posXtemp;//!< Temp value used in calculations across functions
    int *posYtemp;//!< Temp value used in calculations across functions
    int *posXtempFunc;//!< Temp value used in calculations across functions
    int *posYtempFunc;//!< Temp value used in calculations across functions
    double *size;//!< Temp value used in calculations across functions
    double *angle;//!< Temp value used in calculations across functions
    double *centerX;//!< Temp value used in calculations across functions
    double *centerY;//!< Temp value used in calculations across functions
    double *tempLength;//!< Temp value used in calculations across functions

signals:

public slots:
void initLadder(int seed,int start,int end);
int  getXYcase(int caseNum, int xy);
};

#endif // gamescene_1_ladderSnake_H
