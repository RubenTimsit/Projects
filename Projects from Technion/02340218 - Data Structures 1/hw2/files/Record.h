//
// Created by Ruben on 11/06/2023.
//

#ifndef HW2_RECORD_H
#define HW2_RECORD_H


class Record {

private:
    int copiesAmount;
    int purchaseAmount;


public:

    Record(int copiesAmount);

    int getCopiesAmount();
    int getPurchaseAmount();

    void addCopiesAmount(int amount);
    void addPurchaseAmount(int amount);

};


#endif //HW2_RECORD_H
