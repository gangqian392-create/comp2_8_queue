#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

void initialize(QUEUE* q, size_t mem_size)
{
    q->memory_begin = (int*)malloc(sizeof(int) * mem_size);
    q->memory_end = q->memory_begin + mem_size;

    q->head = q->memory_begin;   // dequeue の位置
    q->tail = q->memory_begin;   // enqueue の位置
}

void finalize(QUEUE* q)
{
    free(q->memory_begin);
    q->memory_begin = NULL;
    q->memory_end = NULL;
    q->head = NULL;
    q->tail = NULL;
}

// キューが空か？
bool isEmpty(const QUEUE* q)
{
    return q->head == q->tail;
}

// キューに入っている要素数
int countQueuedElements(const QUEUE* q)
{
    if (q->tail >= q->head)
        return q->tail - q->head;
    else
        return (q->memory_end - q->head) + (q->tail - q->memory_begin);
}

// キューにあと何個入れられるか
int countQueueableElements(const QUEUE* q)
{
    return (q->memory_end - q->memory_begin) - countQueuedElements(q) - 1;
}

// 1つ追加
bool enqueue(QUEUE* q, int val)
{
    // 満杯なら false
    if (countQueueableElements(q) <= 0) return false;

    *(q->tail) = val;
    q->tail++;

    // 循環
    if (q->tail == q->memory_end)
        q->tail = q->memory_begin;

    return true;
}

// 複数追加
bool enqueue_array(QUEUE* q, int* addr, int num)
{
    if (countQueueableElements(q) < num)
        return false;  // 入り切らない

    for (int i = 0; i < num; i++)
    {
        enqueue(q, addr[i]);
    }
    return true;
}

// 1つ取り出す
int dequeue(QUEUE* q)
{
    if (isEmpty(q)) return 0; // 取り出せない

    int result = *(q->head);
    q->head++;

    if (q->head == q->memory_end)
        q->head = q->memory_begin;

    return result;
}

// 複数取り出す
int dequeue_array(QUEUE* q, int* addr, int num)
{
    int count = 0;

    while (count < num && !isEmpty(q))
    {
        addr[count] = dequeue(q);
        count++;
    }

    return count;  // 実際に取り出せた数
}