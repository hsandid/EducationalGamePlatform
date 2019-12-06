#ifndef GAME2SCENE_H
#define GAME2SCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QWidget>
#include <QtWidgets>
#include <QTimer>
#include "card.h"
#include "cpu.h"

/**
 *
 * \file game2scene.h
 * \brief The game2scene class
 */

class game2scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit game2scene(QObject *parent = 0);

    CPU *CPU1;  //!< First CPU opponent
    CPU *CPU2; //!< Second CPU opponent
    card *playerCard1; //!< Player card
    card *playerCard2; //!< Player card
    card *playerCard3; //!< Player card
    card *playerCard4; //!< Player card

    card *CPU1Card1; //!< CPU1 card
    card *CPU1Card2; //!< CPU1 card
    card *CPU1Card3; //!< CPU1 card
    card *CPU1Card4; //!< CPU1 card

    card *CPU2Card1; //!< CPU2 card
    card *CPU2Card2; //!< CPU2 card
    card *CPU2Card3; //!< CPU2 card
    card *CPU2Card4; //!< CPU2 card

    card *drawPileCard; //!< Draw pile
    card *discardPileCard; //!< Discard pile
    card *tempPlayerDisplay;  //!< Temporary card to display whenever the player picks from the draw pile and needs to make a choice


    QGraphicsPixmapItem *cross; //!< Cross symbol used to let the user select cards
    QGraphicsPixmapItem *crossTemp; //!< Second cross symbol used to let the user select cards

    QGraphicsTextItem *text; //!< Text element in GUI
    QGraphicsTextItem *drawpiletext; //!< Text element in GUI
    QGraphicsTextItem *discardpiletext; //!< Text element in GUI
    QGraphicsTextItem *opp1; //!< Text element in GUI
    QGraphicsTextItem *opp2; //!< Text element in GUI
    QGraphicsPixmapItem *discardPile; //!< Text element in GUI
    QGraphicsPixmapItem *drawPile; //!< Text element in GUI

    QPushButton *goLeft; //!< Go right
    QPushButton *goRight; //!< Go left
    QPushButton *takeDiscard; //!< Take from discard pile
    QPushButton *takeDraw; //!< Take from draw pile
    QPushButton *keep; //!< Keep card picked from draw pile
    QPushButton *discard; //!< do not keep picked card from draw pile
    QPushButton *select; //!< Select button
    QPushButton *callCabo; //!< Call Cabo and end game
    QPushButton *exitButton; //!< Call Cabo and end game

    int *cardSelection; //!< Integer helps with navigation when selecting cards
    int *cardSelectionAdversary; //!< Integer helps with navigation when selecting cards

    int *firstSelection;
    int *caboCaller; //!< Integer helping check who called cabo

    int *turnsPassed; //!< Check how much turns have passed

    bool *firstTurn; //!< Check if the game just started
    bool *cputurn; //!< Check if it is the CPU's turn
    bool *caboCalled; //!< Check if cabo has been called

    bool *lock; //!< Temporary lock boolean used to evaluate conditions between functions

    int *finalScorePlayer; //!< Final score of the human player once the game ends


    QVector<int> *drawPileCards; //!< Holds value in the draw pile
    QVector<int> *discardPileCards; //!< Holds value in the discard pile
    QString *mystr; //!< String to display on text

//    QString *link;

signals:

public slots:
void initUI();
void initDrawPile();
void initDiscardPile();
void initAllCards();
void goLeftMove();
void goLeftMoveAdv();
void goRightMove();
void goRightMoveAdv();
void checkTwoCards_startPlayer();
void getTwoCards_checkPhase1();
void getTwoCards_checkPhase2();
void getTwoCards_checkPhase3();
void checkOneCards_startPlayer();
void getOneCards_checkPhase1();
void getOneCards_checkPhase2();
void swapCard_withenemy_phase1();
void swapCard_withenemy_phase2();
void swapCard_withenemy_phase3();
void spyCard_withenemy_phase1();
void spyCard_withenemy_phase2();
void spyCard_withenemy_phase3();
void checkFinalCabo();
void selectPile();
void caboCall();
void discardAction();
void selectandswap_discard();
void drawAction();
void discardcard_action();
void keepcard_action();
void keepcard_action_phase1();
void checkDrawPile_amount();
void checkDrawPile_amount_CPUs();
void gameLoop_main();
void cpuTurn();
void cpuActions_1();
void cpuActions_2();
void startCPUGame();
void exitgame_n_save();
void endgame_exit();
void load_game();

};

#endif // GAME2SCENE_H
