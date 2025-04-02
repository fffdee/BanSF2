#include "BG_RingBuffer.h"


static uint16_t ringbuffer_get_data(struct BG_RingBuffer *buffer, uint8_t *data, uint16_t size )
{

}

static void ringbuffer_set_data(struct BG_RingBuffer *buffer, uint8_t *data, uint16_t size )
{

}


BG_RingBuffer BG_RingBuffer_Init(uint8_t *buffer,uint16_t size)
{
    BG_RingBuffer BG_Buffer = {

        .Data.buffer = buffer,
        .Data.max_size = size,
        .Data.data_over = 0,
        .Data.data_start = 0,
    

    };
        

}

