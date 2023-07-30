#ifndef AIPLAYCARD_H
#define AIPLAYCARD_H
#include<card.h>

class AIPlayCard
{
public:
    AIPlayCard();
    static int findSmallestCards(QList<Card*>& cards);
    static int findStraight(QList<Card*>& cards);
    static int findStraightPair(QList<Card*>& cards);
    static int findPlaneWithOne(QList<Card*>& cards);
    static int findPlaneWithPair(QList<Card*>& cards);
    static int findPlane(QList<Card*>& cards);
    static int findTripleWithOne(QList<Card*>& cards);
    static int findTripleWithPair(QList<Card*>& cards);
    static int findTriple(QList<Card*>& cards);
    static int findPair(QList<Card*>& cards);
    static int findSingle(QList<Card*>& cards);
    static int findBomb(QList<Card*>& cards, int value);
    static int findKingBomb(QList<Card*>& cards);
    static int findSmallestSingle(QList<Card*>& cards);

    static QList<Card*> BeatCards(QList<Card*>& cardInHand, QList<Card*>& cardLastPlayer);

    static int findBeatBySameType(QList<Card*>& cardInHand, QList<Card*>& cardLastPlayer);
    static int findStraight(QList<Card*>& cards, int point, int len);
    static int findStraightPair(QList<Card*>& cards, int point, int len);
    static int findPlaneWithOne(QList<Card*>& cards, int point);
    static int findPlaneWithPair(QList<Card*>& cards, int point);
    static int findPlane(QList<Card*>& cards, int point);
    static int findTripleWithOne(QList<Card*>& cards, int point);
    static int findTripleWithPair(QList<Card*>& cards, int point);
    static int findTriple(QList<Card*>& cards, int point);
    static int findPair(QList<Card*>& cards, int point);
    static int findSingle(QList<Card*>& cards, int point);
};

#endif // AIPLAYCARD_H
