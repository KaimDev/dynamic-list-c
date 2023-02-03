#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

struct _List
{
    int32_t *data;
    size_t   capacity;
    size_t   size;
};

typedef struct _List List, *ListPointer;

ListPointer ListNew()
{
    ListPointer list = (ListPointer)malloc(sizeof(List));

    list->size = 0;
    list->capacity = 16;
    list->data = (int32_t*)malloc(sizeof(int32_t) * list->capacity);

    return list;
}

void ListAdd(ListPointer list, int32_t value)
{
    if (list->size < list->capacity)
    {
        ++list->size;
    }
    else if (list->size <= list->capacity)
    {
        list->capacity *= 2;
        list->data = (int32_t*)realloc(list->data, list->capacity);
        ++list->size;
    }

    list->data[list->size - 1] = value;
}

void ListSet(ListPointer list, int32_t index, int32_t value)
{
    if (!list->capacity > index)
    {
        return;
    }

    list->data[index] = value;
}

int32_t* ListGet(ListPointer list, int32_t index)
{
    if (!list->capacity > index)
    {
        return NULL;
    }

    return &list->data[index];
}

size_t ListSize(ListPointer list)
{
    return list->size;
}

void ListRemoveAt(ListPointer list, int32_t index)
{
    if (!list->capacity > index)
    {
        return;
    }

    list->data[index] = 0;
}

void ListRemove(ListPointer list, int32_t value)
{
    for (size_t i = 0 ; i <= list->size ; ++i)
    {
        if (list->data[i] == value)
        {
            list->data[i] = 0;
            return;
        }
    }
}

void ListRemoveIf(ListPointer list, int32_t value)
{
    for (size_t i = 0 ; i <= list->size ; ++i)
    {
        if (list->data[i] == value)
        {
            list->data[i] = 0;
        }
    }
}

void ListDestroy(ListPointer list)
{
    free(list->data);
    free(list);
}

int32_t main(void)
{
    ListPointer list = ListNew();

    printf("> %lu\n", list->capacity);

    ListDestroy(list);

    return EXIT_SUCCESS;
}