#include "shared_memory.h"
#include <iostream>
#include <cstring>
#include <sys/ipc.h>
#include <sys/shm.h>



namespace streamer
{

SharedMemory::SharedMemory(size_t key, size_t size)
 : size_{size}
{
    this->initBuffer(key, size);
}


SharedMemory::~SharedMemory()
{
    this->deinitBuffer();
}


void SharedMemory::initBuffer(size_t key, size_t size)
{
    shmID_ = shmget(key, sizeof(Buffer) + size, IPC_CREAT | 0666);

    if (shmID_ == -1)
    {
        std::cerr << "Failed to create shared memory.\n";
        return;
    }

    shmBuff_ = static_cast<Buffer*>(shmat(shmID_, nullptr, 0));
    if (shmBuff_ == reinterpret_cast<Buffer*>(-1))
        std::cerr << "Failed to attach to shared memory.\n";
}


void SharedMemory::deinitBuffer()
{
    shmdt(shmAddr_);
    shmctl(shmid, IPC_RMID, NULL);
}


size_t SharedMemory::GetSize() const
{
    return size_;
}


void SharedMemory::WriteData(data_ptr_t data)
{
    std::memcpy(shmAddr_, data, size_);
}


} // namespace streamer



