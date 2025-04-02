#include "BG_RingBuffer.h"
#include <string.h>



static uint16_t ringbuffer_get_remian(struct BG_RingBuffer *ringbuffer)
{
    uint16_t size = 0;
    if (ringbuffer->Data.data_start > ringbuffer->Data.data_over)
    {
        size = (ringbuffer->Data.max_size - ringbuffer->Data.data_start) + ringbuffer->Data.data_over;
    }
    else
    {
        size = ringbuffer->Data.data_over - ringbuffer->Data.data_start;
    }
    return size;
}


static uint16_t ringbuffer_get_data(struct BG_RingBuffer *ringbuffer, uint8_t *data, uint16_t size)
{
    uint16_t count = 0;
    uint16_t real_size = 0;

    ringbuffer->Data.data_count = ringbuffer->Data.max_size - ringbuffer_get_remian(ringbuffer);

    if(size > ringbuffer->Data.data_count )
    {
        real_size = ringbuffer->Data.data_count ;
    }else
    {
        real_size = size;
    }

    for (count = 0; count < real_size ; count++)
    {
        uint16_t index = count + ringbuffer->Data.data_start;
        if (index > ringbuffer->Data.max_size)
        {
            index = index - ringbuffer->Data.max_size;
        }
        data[count] = ringbuffer->Data.buffer[index];
    }
    ringbuffer->Data.data_start = ringbuffer->Data.data_start + real_size;
    if(ringbuffer->Data.data_start>ringbuffer->Data.max_size){
        ringbuffer->Data.data_start = ringbuffer->Data.data_start - ringbuffer->Data.max_size;
    }
    return real_size;

}

static uint16_t ringbuffer_set_data(struct BG_RingBuffer *ringbuffer, uint8_t *data, uint16_t size)
{
    uint8_t count = 0;
    uint16_t real_size = 0;

    if(size > ringbuffer_get_remian(ringbuffer) )
    {
        real_size = ringbuffer_get_remian(ringbuffer) ;
    }else
    {
        real_size = size;
    }
    for (count = 0; count < real_size; count++)
    {
        uint16_t index = count + ringbuffer->Data.data_over;
        if (index > ringbuffer->Data.max_size)
        {
            index = index - ringbuffer->Data.max_size;
        }
        ringbuffer->Data.buffer[index] = data[count];
    }
    return real_size;
}

static void ringbuffer_clean_buffer(struct BG_RingBuffer *ringbuffer)
{
    memset(ringbuffer->Data.buffer, 0, ringbuffer->Data.max_size);
    ringbuffer->Data.data_over = 0;
    ringbuffer->Data.data_start = 0;
}

BG_RingBuffer BG_RingBuffer_Init(uint8_t *buffer, uint16_t size)
{
    BG_RingBuffer BG_Buffer = {

        .Data.buffer = buffer,
        .Data.max_size = size,
        .Data.data_over = 0,
        .Data.data_start = 0,
        .SetData = ringbuffer_set_data,
        .GetData = ringbuffer_get_data,
        .GetRemian = ringbuffer_get_remian,
        .CleanBuffer = ringbuffer_clean_buffer,
    };

    return BG_Buffer;
}
