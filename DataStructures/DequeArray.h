#ifndef TECHNOPARK_DEQUE_ARRAY_H
#define TECHNOPARK_DEQUE_ARRAY_H
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct DequeArray {
    int* arr; // массив
    size_t size; // размер массива (сколько выделено)
    size_t factual_size; // фактичекий размер (сколько записано)
    size_t head; // индекс первого элемента
    size_t tail; // индекс последнего элемента
} RingBuffer;

void init_DequeArray(RingBuffer* deq) {
    deq->arr = NULL; // ставим arr в NULL
    // обнуляем все поля
    deq->factual_size = deq->size = 0;
    deq->head = deq->head = 0;
}

void clear_DequeArray(RingBuffer* deq) {
    free(deq->arr); // чистим память
    deq->arr = NULL; // ставим arr в NULL
    // обнуляем все поля
    deq->factual_size = deq->size = 0;
    deq->head = deq->head = 0;
}

void resize(RingBuffer* deq, size_t leave_empty) {
    // вычисляем новый размер
    size_t new_size = (deq->size == 0) ? 4 : deq->size * 2;
    // создаем временный массив для копирования исходного
    int* temp = (int*)calloc(deq->size, sizeof(int));

    // если размер исходного массива больше нуля
    if (deq->size > 0) {
        /*
         * так как leave_empty показывает сколько полей
         * в начале необходимо оставить пустыми, то
         * начальная позиция вставки равна leave_empty
         */
        size_t target_index = leave_empty;

        // если массив закольцован
        if (deq->tail < deq->head) {
            // копируем от head до конца исходного массива
            for (size_t i = deq->head; i < deq->size; i++)
                temp[target_index++] = deq->arr[i];
            // копируем от начала до tail
            for (size_t i = 0; i <= deq->tail; i++)
                temp[target_index++] = deq->arr[i];
        }
        else { // если не зацольцован
            // копируем от head до tail
            for (size_t i = deq->head; i <= deq->tail; i++)
                temp[target_index++] = deq->arr[i];
        }

        // ставим начало кольцевого буфера на позцицию leave_empty
        deq->head = leave_empty;
        // ставим конец кольцевого буфера на позицию последнего копирования - 1
        deq->tail = target_index - 1;
        // всего записано элементов - target_index - leave_empty
        deq->factual_size = target_index - leave_empty;
    }

    free(deq->arr); // удаляем исходный массив
    // и пересоздаем с новым размером
    deq->arr = (int*)calloc(new_size, sizeof(int));
    // копируем весь temp
    for (size_t i = deq->head; i <= deq->tail; i++)
        deq->arr[i] = temp[i];
    deq->size = new_size; // обновляем размер
    free(temp); // чистим временный массив
}

void enqueue_first(RingBuffer* deq, int el) {
    if (deq->factual_size == deq->size) // если места нет
        resize(deq, 1); // увеличиваем размер
    // если head больше 0, есть место в начале массива
    if (deq->head > 0)
        deq->head--;
    else // если head стоит в нуле, кольцуем массив
        deq->head = deq->size - 1;
    deq->arr[deq->head] = el;
    deq->factual_size++;
    // если мы добавили элемент в пустую очередь, то он
    // же будет и последним
    if (deq->factual_size == 1)
        deq->tail = deq->head;
}

void enqueue_last(RingBuffer* deq, int el) {
    if (deq->factual_size == deq->size) // если места нет
        resize(deq, 0); // увеличиваем размер
    // если tail расположен в конце, нужно перейти в начало
    if (deq->tail == deq->size - 1)
        deq->tail = 0;
    else // если tail расположен где либо еще
        deq->tail++; // просто инкрементируем
    deq->arr[deq->tail] = el;
    deq->factual_size++;
    // если мы добавили элемент в пустую очередь, то он
    // же будет и первым
    if (deq->factual_size == 1)
        deq->head = deq->tail;
}

int dequeue_first(RingBuffer* deq) {
    assert(deq->size != 0);
    // запоминаем удаляемый элемент
    int first = deq->arr[deq->head];
    // если удаляем из очереди с одним элементом
    if (deq->factual_size == 1) {
        // обнуляем поля head, tail и factual_size
        deq->tail = deq->head = 0;
        deq->factual_size = 0;
        return first; // возвращаем значение
    }
    // если head в конце - двигаем в начало
    if (deq->head == deq->size - 1)
        deq->head = 0;
    else // иначе - двигаем head вперед
        deq->head++;
    deq->factual_size--; // декрементируем фактический размер
    return first; // возвращаем значение
}

int dequeue_last(RingBuffer* deq) {
    assert(deq->size != 0);
    // запоминаем удаляемый элемент
    int first = deq->arr[deq->tail];
    // если удаляем из очереди с одним элементом
    if (deq->factual_size == 1) {
        // обнуляем поля head, tail и factual_size
        deq->tail = deq->head = 0;
        deq->factual_size = 0;
        return first; // возвращаем значение
    }
    // если tail в начале - ставим в конец
    if (deq->tail == 0)
        deq->tail = deq->size - 1;
    else // иначе - двигаем tail назад
        deq->tail--;
    deq->factual_size--; // декрементируем фактический размер
    return first; // возвращаем значение
}

int peek_first(RingBuffer* deq) {
    assert(deq->size != 0);
    return deq->arr[deq->head];
}

int peek_last(RingBuffer* deq) {
    assert(deq->size != 0);
    return deq->arr[deq->tail];
}

void test_DequeArray() {
    RingBuffer deq;
    init_DequeArray(&deq);
    clear_DequeArray(&deq);
    init_DequeArray(&deq);

    for (int i = 0; i < 10; i++) {
        if (i % 2 == 0) {
            enqueue_first(&deq, 10 - i);
            printf("PeekFirst = %d\n", peek_first(&deq));
        }
        else {
            enqueue_last(&deq, i);
            printf("PeekLast = %d\n", peek_last(&deq));
        }
    }
    putchar('\n');

    for (int i = 0; i < 5; i++) {
        printf("[%d]DequeueFirst = %d\n", i, dequeue_first(&deq));
        printf("[%d]DequeueLast = %d\n", i, dequeue_last(&deq));
    }

    clear_DequeArray(&deq);
}

#endif //TECHNOPARK_DEQUE_ARRAY_H