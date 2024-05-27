//
// Created by ofir1 on 09-Jun-23.
//

#include "recordsCompany.h"

RecordsCompany::RecordsCompany() : user_array(UserArray()), records(nullptr), membersTree(User::compareUsers), uf(nullptr), recordsNum(0)
{

}

RecordsCompany::~RecordsCompany() {

    delete uf;

    for (int i = 0; i < recordsNum; i++)
        delete records[i];

    delete[] records;

}
StatusType RecordsCompany::newMonth(int *records_stocks, int number_of_records){
    if(uf != nullptr)
        delete uf;
    if(records != nullptr) {
        for (int i = 0; i < recordsNum; i++)
            delete records[i];
        delete[] records;
    }
    try {
        uf = new UnionFind(number_of_records);
        for (int i = 0; i < number_of_records; i++) {
            uf->MakeSet(records_stocks[i]);
        }
    }
    catch (const std::bad_alloc& e){
        return StatusType::ALLOCATION_ERROR;
    }
    Record **tempRecords = nullptr;
    try {
        tempRecords = new Record *[number_of_records];
    }
    catch (const std::bad_alloc& e){
        return StatusType::ALLOCATION_ERROR;
    }
    for(int i =0;i<number_of_records;i++){
        tempRecords[i] = new Record(records_stocks[i]);
        if(tempRecords[i] == nullptr)
            return StatusType::ALLOCATION_ERROR;
    }
    records = tempRecords;

    shared_ptr<User> *temp = nullptr;
    try {
        temp = new shared_ptr<User>[membersTree.getTreeSize()];
    }
    catch (const std::bad_alloc& e){
        return StatusType::ALLOCATION_ERROR;
    }

    membersTree.toArray(temp);
    membersTree.resetPrizes();

    for(int i =0;i<membersTree.getTreeSize();i++){
        temp[i]->resetExpenses();
        temp[i]->resetPrizesOffset();
    }
    recordsNum = number_of_records;
    delete[] temp;

    return StatusType::SUCCESS;
}
StatusType RecordsCompany::addCostumer(int c_id, int phone)
{
    if(c_id < 0 || phone < 0)
    {
        return StatusType::INVALID_INPUT;
    }
    if(user_array.find(c_id))
    {
        return StatusType ::ALREADY_EXISTS;
    }

    shared_ptr<User> tempUser(new User(c_id,phone));
    if(tempUser == nullptr)
        return StatusType ::INVALID_INPUT;
    try {
        user_array.insert(c_id, tempUser);
    }
    catch (const std::bad_alloc& e){
        return StatusType::ALLOCATION_ERROR;
    }


    return StatusType ::SUCCESS;


}
Output_t<int> RecordsCompany::getPhone(int c_id)
{
    if(c_id < 0)
    {
        return StatusType::INVALID_INPUT;
    }

    if(!(user_array.find(c_id)))
    {
        return StatusType::DOESNT_EXISTS;
    }
    int phone = user_array.find(c_id)->getPhone();
    return phone;

}
StatusType RecordsCompany::makeMember(int c_id){
    if(c_id < 0)
        return StatusType::INVALID_INPUT;

    if(!(user_array.find(c_id)))
    {
        return StatusType :: DOESNT_EXISTS;
    }
    shared_ptr<User> user = user_array.find(c_id);
    if(user->getMember())
    {
        return StatusType ::ALREADY_EXISTS;
    }
    double offset = 0;
    try {

        membersTree.insertNode(user, &offset);
    }
    catch (const std::bad_alloc& e){
        return StatusType::ALLOCATION_ERROR;
    }
    user->setOffset(offset);
    user->setMember();
    return StatusType::SUCCESS;
}
Output_t<bool> RecordsCompany::isMember(int c_id){
    if(c_id < 0)
        return StatusType::INVALID_INPUT;
    if(!(user_array.find(c_id)))
    {
        return StatusType ::DOESNT_EXISTS;
    }
    shared_ptr<User> user = user_array.find(c_id);

    return user->getMember();

}
StatusType RecordsCompany::buyRecord(int c_id, int r_id){
    if( (c_id < 0) || (r_id < 0) )
        return StatusType::INVALID_INPUT;
    if ((user_array.find(c_id) == nullptr) || (r_id >= recordsNum))
        return StatusType::DOESNT_EXISTS;
    if(user_array.find(c_id)->getMember())
        user_array.find(c_id)->addExpenses(100 + records[r_id]->getPurchaseAmount());
    records[r_id]->addPurchaseAmount(1);

    return StatusType::SUCCESS;
}
StatusType RecordsCompany::addPrize(int c_id1, int c_id2, double  amount){
    if( (c_id1 < 0) || (c_id2 < 0) || (amount <= 0) || (c_id2 < c_id1) )
        return StatusType::INVALID_INPUT;
    shared_ptr<User> tempUser2(new User(c_id2,0));
    if(tempUser2 == nullptr)
        return StatusType ::INVALID_INPUT;
    shared_ptr<User> tempUser1(new User(c_id1,0));
    if(tempUser2 == nullptr)
        return StatusType ::INVALID_INPUT;
    membersTree.addPrize(tempUser2, amount);
    membersTree.addPrize(tempUser1, -amount);

    return StatusType::SUCCESS;
}
Output_t<double> RecordsCompany::getExpenses(int c_id)
{
    if(c_id < 0)
    {
        return StatusType ::INVALID_INPUT;
    }
    if(user_array.find(c_id)== nullptr)
    {
        return StatusType :: DOESNT_EXISTS;
    }
    if(!(user_array.find(c_id)->getMember()))
    {
        return StatusType :: DOESNT_EXISTS;
    }
    shared_ptr<User> tempUser1(new User(c_id,0));
    if(tempUser1 == nullptr)
        return StatusType ::INVALID_INPUT;
    double prize = 0;
    double prizeOffset = membersTree.find(tempUser1, &prize)->getValue()->getPrizesBeforeIJoined();
    shared_ptr<User> user = user_array.find(c_id);


    double expense = user->getExpenses();



    return (expense - prize + prizeOffset);

}
StatusType RecordsCompany::putOnTop(int r_id1, int r_id2){
    if((r_id1 < 0) || (r_id2 < 0))
        return StatusType::INVALID_INPUT;
    if((r_id1 >= recordsNum) || (r_id2 >= recordsNum))
        return StatusType::DOESNT_EXISTS;
    if(uf->getCol(r_id1) == uf->getCol(r_id2)) return StatusType::FAILURE;
    uf->Union(r_id1, r_id2);
    return StatusType::SUCCESS;

}

StatusType RecordsCompany::getPlace(int r_id, int *column, int *height){
    if(column == nullptr || height == nullptr || r_id < 0)
        return StatusType::INVALID_INPUT;
    if(r_id >= recordsNum)
        return StatusType::DOESNT_EXISTS;
    *column = uf->getCol(r_id);
    *height = uf->getHeight(r_id);
    return StatusType::SUCCESS;
}
