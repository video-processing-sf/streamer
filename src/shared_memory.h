#ifndef STREAMER_SHARED_MEMORY_H_
#define STREAMER_SHARED_MEMORY_H_

#include <memory>


namespace streamer
{

class Frame;

class SharedMemory
{
public:
    SharedMemory(unsigned int size);
    ~SharedMemory();

    void PushFrame(const std::shared_ptr<Frame> frame);
    

protected:
    void allocateBuffer(unsigned int size);
    void freeBuffer();

private:
    unsigned int size_;
};



} // namespace streamer


#endif // STREAMER_SHARED_MEMORY_H_


