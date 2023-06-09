#ifndef STREAMER_SHARED_MEMORY_H_
#define STREAMER_SHARED_MEMORY_H_

#include <memory>
#include <shared_mutex>
#include <gst/gst.h>
#include "types.h"



namespace streamer
{

struct Buffer
{
    std::shared_mutex mutex;
    size_t size;
    data_ptr_t data;
}


class Frame;

class SharedMemory
{
public:
    SharedMemory(size_t key, size_t size);
    ~SharedMemory();

    size_t GetSize() const;

    void WriteData(data_ptr_t data);

protected:
    void initBuffer(size_t key, size_t size);
    void deinitBuffer();

private:
    Buffer* shmBuff_;
    int shmID_;
    size_t size_;

};



} // namespace streamer


#endif // STREAMER_SHARED_MEMORY_H_


