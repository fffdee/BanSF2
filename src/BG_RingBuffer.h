#ifndef __BG_RINGBUFFER_H__
#define __BG_RINGBUFFER_H__

#include <stdint.h>

typedef struct {

    uint8_t *buffer;
    uint16_t data_start;
    uint16_t data_over;
    uint16_t data_count;
    uint16_t max_size;

}BG_RingBuffer_Data;

typedef struct BG_RingBuffer{

    BG_RingBuffer_Data Data;

    uint16_t (*SetData)(struct ringbuffer*, uint8_t *Data, uint16_t total);
    uint16_t (* GetData)(struct ringbuffer*,uint8_t *Data, uint16_t total);
    uint16_t (* GetRemian)(struct ringbuffer*);
    void (* CleanBuffer)(struct ringbuffer*);


}BG_RingBuffer;


BG_RingBuffer BG_RingBuffer_Init(uint8_t  *buffer, uint16_t buffer_size);


#endif