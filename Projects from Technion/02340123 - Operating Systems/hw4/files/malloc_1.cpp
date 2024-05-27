#include <unistd.h>
#include <math.h>
void* smalloc(size_t size)
{
    if(size==0 || size>pow(10,8))
    {
        return NULL;
    }
    void* return_value=sbrk(size);
    if(return_value==(void*)-1)
    {
            return NULL;
    }
    return return_value;
}