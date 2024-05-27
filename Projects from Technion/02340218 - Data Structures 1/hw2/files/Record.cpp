#include "Record.h"


Record::Record(int copiesAmount): copiesAmount(copiesAmount), purchaseAmount(0)
{

}

int Record::getCopiesAmount() {
    return copiesAmount;
}

int Record::getPurchaseAmount() {
    return purchaseAmount;
}

void Record::addCopiesAmount(int amount)
{
    copiesAmount += amount;
}

void Record::addPurchaseAmount(int amount)
{
    purchaseAmount+= amount;
}








