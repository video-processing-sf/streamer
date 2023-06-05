#include "shared_memory.h"
#include <iostream>
#include <cstring>
#include <sys/ipc.h>
#include <sys/shm.h>



namespace streamer
{

SharedMemory::SharedMemory(uint key, uint size)
 : size_{size}
{
    this->initBuffer(key, size);
}


SharedMemory::~SharedMemory()
{
    this->deinitBuffer();
}


void SharedMemory::initBuffer(uint key, uint size)
{
    int shmID = shmget(key, size, IPC_CREAT | 0666);

    if (shmID == -1)
    {
        std::cerr << "Failed to create shared memory.\n";
        return;
    }

    shmAddr_ = static_cast<char*>(shmat(shmID, nullptr, 0));
    if (shmAddr_ == (void*)-1)
        std::cerr << "Failed to attach to shared memory.\n";
}


void SharedMemory::deinitBuffer()
{
    shmdt(shmAddr_);
}


uint SharedMemory::GetSize() const
{
    return size_;
}


void SharedMemory::WriteData(data_ptr_t data)
{
    std::memcpy(shmAddr_, data, size_);
}


} // namespace streamer



