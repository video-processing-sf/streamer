#ifndef STREAMER_SHARED_MEMORY_H_
#define STREAMER_SHARED_MEMORY_H_

#include <memory>
#include <mutex>
#include <gst/gst.h>
#include "types.h"



namespace streamer
{

class Frame;

class SharedMemory
{
public:
    SharedMemory(uint key, uint size);
    ~SharedMemory();

    uint GetSize() const;

    void WriteData(data_ptr_t data);

protected:
    void initBuffer(uint key, uint size);
    void deinitBuffer();

private:
    std::mutex mutex_;
    char* shmAddr_;
    uint size_;

};



} // namespace streamer


#endif // STREAMER_SHARED_MEMORY_H_


