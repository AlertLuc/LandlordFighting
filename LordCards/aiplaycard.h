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
};

#endif // AIPLAYCARD_H
