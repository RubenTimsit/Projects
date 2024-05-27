#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>


// METADATA STRUCT
typedef struct MallocMetadata 
{
    size_t size;
    bool is_free;
    MallocMetadata* next;
    MallocMetadata* prev;

} MMD;

// DEF OF GLOBAL VARIABLES
MMD* blocks_List = NULL;
size_t free_blocks = 0;
size_t free_bytes = 0;
size_t allocated_blocks = 0;
size_t allocated_bytes = 0;
size_t metadata_bytes = 0;
size_t size_meta_data = 0;

// ASSIST LIST FUNCTION
void insert(MMD* node)
{
    
    MMD* first=blocks_List;
    if(first==NULL)
    {
        blocks_List = node;
    }
    else
    {
        while(first->next!=NULL)
        {
            first=first->next;
        }
        first->next=node;
    }
    node->prev=first;
    node->next=NULL;
    allocated_blocks++;
    allocated_bytes += node->size;
    metadata_bytes += sizeof(MMD);
}

// MAIN FUNCTIONS
void* smalloc(size_t size)
{
    if(size <= 0 || size>pow(10,8))
        return NULL;

    size_t req_size = size + sizeof(MMD);
    MMD* curr=blocks_List;
    while(curr!=NULL)
    {
        if(curr->is_free && curr->size >= size)
        {
            curr->is_free=false;
            free_blocks--;
            free_bytes-=curr->size;
            return (char*)curr + sizeof(MMD);
        }
        curr=curr->next;
    }

    void* prog_brk = sbrk(req_size);
    if(prog_brk==(void*)-1)
    {
        return NULL;
    }

    MMD* meta = (MMD*)prog_brk;
    meta->size=size;
    meta->is_free=false;
    insert(meta);
    return (char*)prog_brk + sizeof(MMD);
}

void* scalloc(size_t num, size_t size)
{   
    void* return_value = smalloc(num*size);
    if(return_value == NULL)
        return NULL;
    memset(return_value, 0, size*num);
    return return_value;
}

void sfree(void *p)
{
    if(p==NULL)
        return;
    MMD* meta = (MMD*)((char*)p - sizeof(MMD));
    if(meta->is_free)
    {
        return;
    }
    meta->is_free=true;
    free_blocks++;
    free_bytes+=meta->size;
    return;
}

void* srealloc(void* oldp, size_t size)
{
    if(size == 0 || size > pow(10,8))
        return NULL;
        
    if(oldp == NULL)
        return smalloc(size);

    MMD* old_meta = (MMD*)((char*)oldp - sizeof(MMD));
    if(old_meta->size >= size)
    {
        return oldp;
    }

    void* newp = smalloc(size);
    if(newp == NULL)
    {
        return NULL;
    }

	sfree(oldp);
    memmove(newp, oldp, old_meta->size);
    return newp;
}

size_t _num_free_blocks()
{
    return free_blocks;
}

size_t _num_free_bytes()
{
    return free_bytes;
}

size_t _num_allocated_blocks()
{
    return allocated_blocks;
}

size_t _num_allocated_bytes()
{
    return allocated_bytes;
}

size_t _num_meta_data_bytes()
{
    return metadata_bytes;
}

size_t _size_meta_data()
{
    return sizeof(MMD);
}
