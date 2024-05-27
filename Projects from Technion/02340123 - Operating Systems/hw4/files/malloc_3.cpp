#include <unistd.h>
#include <cstring>
#include <sys/mman.h>
#include <cstdlib>
#include <time.h>


struct MallocMetadata
{
    int cookie;
    size_t size;
    bool is_free;
    MallocMetadata* next;
    MallocMetadata* prev;
};

MallocMetadata* array[11];
bool firstTime=true;
size_t numOfFreeBlocks=0;
size_t numOfUsedBlocks=0;
size_t numOfFreeBytes=0;
size_t numOfUsedBytes=0;
size_t numOfUsedMMAPblocks=0;
size_t numOfUsedMMAPbytes=0;

MallocMetadata* map= NULL;
int cookieNum=0;


void checkCookie(MallocMetadata* c)
{
    if(c->cookie != cookieNum)
    {
        exit(0xDEADBEEF);
    }
}

unsigned long findSizeByTwo(size_t size)
{
    unsigned long twoSize=128;
    while((unsigned long)(size+ sizeof(MallocMetadata)) > twoSize)
    {
        twoSize= twoSize*2;
    }
    return twoSize;
}


//section of code for map
void addToMap(MallocMetadata* t)
{
    checkCookie(t);
    t->prev= NULL;
    t->next= map;
    if(map!=NULL)
    {
        map->prev= t;
    }
    map= t;
}

void removeFromMap(MallocMetadata* t)
{
    checkCookie(t);
    if(t->prev==NULL)
    {
        map=t->next;
        if(map!=NULL)
        {
            map->prev=NULL;
        }
        t->next=NULL;
        return;
    }

    MallocMetadata* prev= t->prev;
    prev->next= t->next;
    if(t->next!=NULL)
    {
        (t->next)->prev= prev;
    }
    t->prev= NULL;
    t->next= NULL;
}
//end of section of code for map


void addToList(int index, MallocMetadata* metadata)
{
    checkCookie(metadata);
    if(array[index]==NULL)
    {
        metadata->prev=NULL;
        metadata->next=NULL;
        array[index]= metadata;
        return;
    }
    MallocMetadata* temp= array[index];
    checkCookie(temp);
    if((unsigned long)metadata < (unsigned long)array[index])
    {
        //case of adding at the beginning
        metadata->next= array[index];
        metadata->prev= NULL;
        checkCookie(array[index]);
        array[index]->prev= metadata;
        array[index]= metadata;
        return;
    }
    while(temp->next != NULL && (unsigned long)(temp->next) < (unsigned long)metadata)
    {
        temp= temp->next;
        checkCookie(temp);
    }

    if(temp->next==NULL)
    {
        temp->next= metadata;
        metadata->prev= temp;
        metadata->next= NULL;
        return;
    }

    MallocMetadata* save= temp->next;
    temp->next= metadata;
    metadata->next= save;
    metadata->prev= temp;
    save->prev= metadata;
}

void* startArray()
{
    unsigned long current= (unsigned long)sbrk(0);

    unsigned long offset= (128*32*1024)-(current%(128*32*1024));
    void* address= sbrk(offset);
    if(address== (void*)(-1))
    {
        return NULL;
    }
    void* nextInArray= sbrk(128*32*1024);


    if(nextInArray== (void*)(-1))
    {
        return NULL;
    }

    //creating the rand number
    srand(time(NULL));
    cookieNum= std::rand();

    for(int i=0; i<32; i++)
    {
        MallocMetadata add;
        add.cookie= cookieNum;
        add.size= 1024*128;
        add.is_free= true;
        add.prev= NULL;
        add.next= NULL;
        std::memmove(nextInArray, &add, sizeof(MallocMetadata));
        addToList(10, (MallocMetadata*)nextInArray);
        nextInArray= (void*)((unsigned long)(nextInArray)+128*1024);
        //setting stats
        numOfFreeBytes+= 128*1024;
        numOfFreeBlocks++;
    }
    return nextInArray;
}

void removeFromList(MallocMetadata* remove, int index)
{
    checkCookie(remove);
    if(remove->prev==NULL)
    {
        array[index]= remove->next;
        if(remove->next!=NULL)
        {
            checkCookie(array[index]);
            array[index]->prev= NULL;
        }
        remove->next=NULL;
        return;
    }

    MallocMetadata* prev= remove->prev;
    checkCookie(prev);
    prev->next= remove->next;
    if(remove->next!=NULL)
    {
        checkCookie(remove->next);
        (remove->next)->prev= prev;
    }
    remove->prev= NULL;
    remove->next= NULL;
}

//this is the total size needed in the block-> including the meta
int makeBlock(size_t size)
{
    unsigned long num= 128;
    int startLevel= 0;
    while(size > num)
    {
        num=num*2;
        startLevel++;
    }
    unsigned long sizeToDivide= num;
    int i;
    MallocMetadata* temp;
    //looking for the smallest block need to divide
    for(i= startLevel; i< 11; i++)
    {
        temp= array[i];
        bool found= false;
        while(temp!=NULL)
        {
            found= false;
            checkCookie(temp);
            if(temp->is_free)
            {
                found=true;
                break;
            }
            temp= temp->next;
        }
        if(found)
        {
            break;
        }
        sizeToDivide= sizeToDivide*2;
    }
    if(i==11)
    {
        return i;
    }
    //dividing
    while(sizeToDivide!=num)
    {
        temp->size=sizeToDivide/2;
        removeFromList(temp,i);
        MallocMetadata add;
        add.cookie= cookieNum;
        add.size= sizeToDivide/2;
        add.is_free= true;
        add.prev= NULL;
        add.next= NULL;
        void* buddyAddress= (void*)((unsigned long)temp +sizeToDivide/2);
        std::memmove(buddyAddress, &add, sizeof(MallocMetadata));
        addToList(i-1, temp);
        addToList(i-1, (MallocMetadata*)buddyAddress);
        i--;
        sizeToDivide= sizeToDivide/2;

        //stats
        numOfFreeBlocks++;
    }
    return i;
}

void* smalloc(size_t size)
{
    if(firstTime==true)
    {
        firstTime= false;
        void* success= startArray();
        if(success== (void*)(-1))
        {
            return NULL;
        }
    }
    if(size==0 || size > 100000000)
    {
        return NULL;
    }


    if(size + sizeof(MallocMetadata) > 128*1024)
    {
        //unsigned long byTwo= findSizeByTwo(size);
        void* mapAddress= mmap(NULL, size+sizeof(MallocMetadata), PROT_WRITE | PROT_READ, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

        MallocMetadata add;
        add.cookie= cookieNum;
        add.size= size+sizeof(MallocMetadata);
        add.is_free= false;
        add.prev= NULL;
        add.next= NULL;

        std::memmove(mapAddress, &add, sizeof(MallocMetadata));
        addToMap((MallocMetadata*)mapAddress);

        //stats
        numOfUsedMMAPbytes+= size+sizeof(MallocMetadata);
        numOfUsedMMAPblocks++;
        return (void*)((unsigned long)mapAddress+ sizeof(MallocMetadata));
    }

    int addIndex= makeBlock(size+ sizeof(MallocMetadata));
    if(addIndex == 11)
    {
        return NULL;
    }
    MallocMetadata* temp= array[addIndex];
    while(temp!=NULL)
    {
        checkCookie(temp);
        if(temp->is_free && temp->size >= size + sizeof(MallocMetadata))
        {
            temp->is_free= false;

            //setting stats
            numOfUsedBlocks++;
            numOfFreeBlocks--;
            numOfUsedBytes= numOfUsedBytes+ temp->size;
            numOfFreeBytes= numOfFreeBytes- temp->size;
            return (void*)((unsigned long)temp+ sizeof (MallocMetadata));
        }
        temp= temp->next;
    }
    return NULL;
}

void* scalloc(size_t num, size_t size)
{
    void* address= smalloc(num * size);
    if(address == NULL)
    {
        return NULL;
    }

    memset(address, 0,num*size);
    return address;
}

//pass total size-> including meta
int findIndex(size_t size)
{
    int i=0;
    unsigned long start= 128;
    while(size!=start)
    {
        i++;
        start= start*2;
    }
    return i;
}

void sfree(void* p)
{
    if(p==NULL)
    {
        return;
    }
    unsigned long add= (unsigned long)p;
    MallocMetadata* metaAddress= (MallocMetadata*) (add - sizeof (MallocMetadata));
    checkCookie(metaAddress);
    if(metaAddress->is_free== true)
    {
        return;
    }

    if(metaAddress->size > 128*1024)
    {
        //stats
        numOfUsedMMAPbytes-= metaAddress->size;
        numOfUsedMMAPblocks--;

        removeFromMap(metaAddress);
        munmap((void*)metaAddress, metaAddress->size);

        return;
    }

    metaAddress->is_free=true;

    //stats
    numOfFreeBlocks++;
    numOfUsedBlocks--;
    numOfUsedBytes-= metaAddress->size;
    numOfFreeBytes+= metaAddress->size;

    MallocMetadata* buddyMeta= (MallocMetadata*)((unsigned long)metaAddress^metaAddress->size);
    checkCookie(buddyMeta);
    while(buddyMeta->is_free && buddyMeta->size== metaAddress->size && buddyMeta->size < 1024*128)
    {
        checkCookie(buddyMeta);

        int index= findIndex(metaAddress->size);
        removeFromList(metaAddress, index);
        removeFromList(buddyMeta, index);

        if((unsigned long)metaAddress < (unsigned long)buddyMeta)
        {
            metaAddress->size= metaAddress->size*2;
            addToList(index+1, metaAddress);
        }
        else
        {
            buddyMeta->size= buddyMeta->size*2;
            addToList(index+1, buddyMeta);
            metaAddress= buddyMeta;
        }
        numOfFreeBlocks--;
        buddyMeta= (MallocMetadata*)((unsigned long)metaAddress^metaAddress->size);

        checkCookie(buddyMeta);
    }


}

void* srealloc(void* oldp, size_t size)
{
    void* newAlloc;
    if(oldp == NULL || size > 100000000 || size==0)
    {
        return NULL;
    }

    unsigned long add= (unsigned long)oldp;
    MallocMetadata* metaOld= (MallocMetadata*) (add - sizeof (MallocMetadata));
    checkCookie(metaOld);
    unsigned long oldSize= metaOld->size;
    if(metaOld->size >= size+ sizeof(MallocMetadata))
    {
        return oldp;
    }
    if(metaOld->size > 128*1024)
    {
        unsigned long newSize= findSizeByTwo(size+ sizeof(MallocMetadata));
        void* mapAddress= mmap(NULL, newSize, PROT_WRITE | PROT_READ, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        std::memmove(mapAddress, metaOld, metaOld->size);
        MallocMetadata* mapNew= (MallocMetadata*)mapAddress;
        mapNew->size= newSize;
        sfree(oldp);
        addToMap(mapNew);
        numOfUsedMMAPbytes+= newSize;
        numOfUsedMMAPblocks++;
        return (void*)((unsigned long) mapAddress +sizeof(MallocMetadata));
    }

    //here we check if we can allocate using buddies
    MallocMetadata* left= metaOld;
    checkCookie(left);
    left->is_free=true;
    unsigned long sizeSoFar= left->size;
    MallocMetadata* buddyMeta= (MallocMetadata*)((unsigned long)left^sizeSoFar);
    checkCookie(buddyMeta);
    while(buddyMeta->is_free && buddyMeta->size== sizeSoFar && sizeSoFar<size+sizeof(MallocMetadata) && sizeSoFar < 1024*128)
    {
        if((unsigned long) buddyMeta < (unsigned long) left)
        {
            left= buddyMeta;
        }
        sizeSoFar= sizeSoFar*2;
        buddyMeta= (MallocMetadata*)((unsigned long)left^sizeSoFar);
        checkCookie(buddyMeta);
    }

    //do the relocation with buddies
    if(sizeSoFar>=size+sizeof(MallocMetadata) && sizeSoFar < 1024*128)
    {
        MallocMetadata* metaAddress= metaOld;
        buddyMeta= (MallocMetadata*)((unsigned long)metaOld^metaOld->size);
        checkCookie(metaAddress);
        while(metaAddress->size<size+sizeof(MallocMetadata))
        {
            int index = findIndex(metaAddress->size);
            removeFromList(metaAddress, index);
            removeFromList(buddyMeta, index);
            numOfFreeBlocks--;
            if ((unsigned long) metaAddress < (unsigned long) buddyMeta) {
                metaAddress->size = metaAddress->size * 2;
                addToList(index + 1, metaAddress);
            } else {
                checkCookie(buddyMeta);
                buddyMeta->size = buddyMeta->size * 2;
                addToList(index + 1, buddyMeta);
                metaAddress = buddyMeta;
            }
            buddyMeta = (MallocMetadata *) ((unsigned long) metaAddress ^ metaAddress->size);
            checkCookie(metaAddress);
        }
        checkCookie(metaAddress);
        metaAddress->is_free= false;
        memmove((void*)(metaAddress+sizeof(MallocMetadata)), oldp,oldSize-sizeof(MallocMetadata));
        numOfFreeBytes= numOfFreeBytes+oldSize-metaAddress->size;
        numOfUsedBytes= numOfUsedBytes-oldSize+metaAddress->size;
        return  (void*)((unsigned long) metaAddress + sizeof(MallocMetadata));
    }

    //in case there are no buddies
    newAlloc= smalloc(size);
    if(newAlloc == NULL)
    {
        //in case n place-> keep pold
        checkCookie(metaOld);
        metaOld->is_free=false;
        return NULL;
    }
    memmove(newAlloc, oldp,size);
    sfree(oldp);
    return newAlloc;
}

size_t _num_free_blocks()
{
    return numOfFreeBlocks;
}

size_t _num_free_bytes()
{
    return numOfFreeBytes- numOfFreeBlocks*sizeof(MallocMetadata);
}

size_t _num_allocated_blocks()
{
    return numOfFreeBlocks+ numOfUsedBlocks+ numOfUsedMMAPblocks;
}

size_t _num_allocated_bytes()
{
    return numOfUsedBytes+ numOfFreeBytes+ numOfUsedMMAPbytes- _num_allocated_blocks() * sizeof(MallocMetadata);
}

size_t _num_meta_data_bytes()
{
    return (_num_allocated_blocks())*sizeof(MallocMetadata);
}

size_t _size_meta_data()
{
    return sizeof(MallocMetadata);
}