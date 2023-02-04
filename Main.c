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
    list->capacity = 8;
    list->data = (int32_t*)malloc(sizeof(int32_t) * list->capacity);

    return list;
}

void ListAdd(ListPointer list, int32_t value)
{
    if (list->size == list->capacity)
    {
        list->capacity *= 2;
        int32_t* temp = (int32_t*)realloc(list->data, list->capacity * sizeof(int32_t));
        if (temp == NULL)
        {
            puts("Error realloc");
            return;
        }
        list->data = temp;
    }

    ++list->size;
    list->data[list->size - 1] = value;
}

void ListSet(ListPointer list, int32_t index, int32_t value)
{
    if (list->size < index || index < 0)
    {
        return;
    }

    list->data[index] = value;
}

int32_t* ListGet(ListPointer list, int32_t index)
{
    if (list->size < index || index < 0)
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
    if (list->size < index || index <= 0)
    {
        return;
    }

    if (list->size == 1)
    {
        list->data[0] = 0;
    }

    for (size_t i = index ; i < list->size ; ++i)
    {
        if (i <= list->size)
        {
            list->data[i] = 0;
        }

        list->data[i] = list->data[i + 1];
    }
}

void ListRemove(ListPointer list, int32_t value)
{
    if (list->size == 1)
    {
        if (list->data[0] == value)
        {
            list->data[0] = 0;
            return;
        }
    }

    for (size_t i = 0 ; i < list->size ; ++i)
    {
        if (list->data[i] == value)
        {
            for (size_t t = i ; t < list->size ; ++t)
            {
                if (t <= list->size)
                {
                    list->data[t] = 0;
                }

                list->data[t] = list->data[t + 1];
            }
            return;
        }
    }
}

void ListRemoveIf(ListPointer list, int32_t value)
{
    if (list->size == 1)
    {
        if (list->data[0] == value)
        {
            list->data[0] = 0;
            return;
        }
    }

    for (size_t i = 0 ; i <= list->size ; ++i)
    {
        if (list->data[i] == value)
        {
            for (size_t t = i ; t < list->size ; ++t)
            {
                if (t <= list->size)
                {
                    list->data[t] = 0;
                }

                list->data[t] = list->data[t + 1];
            }
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