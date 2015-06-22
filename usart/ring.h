/* 
 * File:   ring.h
 * Author: mannyb
 *
 * Created on November 24, 2013, 12:12 PM
 */

#ifndef RING_H
#define	RING_H
#include<stdint.h>

#define RINGBUF_SIZE (256)

typedef struct {
    volatile uint16_t head;
    volatile uint16_t tail;
    volatile uint8_t data[RINGBUF_SIZE];
} RingBuffer;

int Enqueue(RingBuffer *buf, uint8_t data);
int Dequeue(RingBuffer *buf, uint8_t *data);

#endif	/* RING_H */

