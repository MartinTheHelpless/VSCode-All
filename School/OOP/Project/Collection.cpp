#pragma once
#include "Collection.h"

Collection::Collection(int size)
{
    this->index = 0;
    this->collectionSize = size;
    this->cards = new Card *[size];
}

Collection::~Collection()
{
    delete this->cards;
}

void Collection::addCardToCollection(Card *card)
{
    if (index < this->collectionSize)
    {
        this->cards[index] = card;
        index++;
    }
}

void Collection::removeCardFromCollection(Card *card)
{
    for (int i = 0; i < this->collectionSize; i++)
        this->cards[i] == card ? this->cards[i] = nullptr : this->cards[i];
}

void Collection::setCollectionName(std::string name)
{
    this->name = name;
}

void Collection::setCardToIndex(Card *card, int i)
{

    this->cards[i] = card;
}

std::string Collection::getCollectionName()
{
    return this->name;
}

Card *Collection::getCard(int index)
{
    return this->cards[index];
}

int Collection::getColletionCardCount()
{
    return this->collectionSize;
}
