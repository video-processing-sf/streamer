#include "shared_memory.h"
#include "frame.h"



namespace streamer
{


SharedMemory::SharedMemory(unsigned int size)
{
    this->allocateBuffer(size);
}

SharedMemory::~SharedMemory()
{
    this->freeBuffer();
}

void SharedMemory::allocateBuffer(unsigned int size)
{
    
}

void SharedMemory::freeBuffer()
{

}

void SharedMemory::PushFrame(const std::shared_ptr<Frame> frame)
{

}


} // namespace streamer



