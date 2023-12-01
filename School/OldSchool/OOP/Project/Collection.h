#pragma once
#include "Card.cpp"

class Collection
{
private:
    Card **cards;
    int collectionSize; // Amount of cards in a collection
    int index;
    std::string name;

public:
    Collection(int size);
    ~Collection();

    void addCardToCollection(Card *card);
    void removeCardFromCollection(Card *card);
    void setCollectionName(std::string name);
    void setCardToIndex(Card *card, int i);

    std::string getCollectionName();
    Card *getCard(int index);
    int getColletionCardCount();
};
