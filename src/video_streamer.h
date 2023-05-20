#ifndef STREAMER_VIDEO_STREAMER_H_
#define STREAMER_VIDEO_STREAMER_H_

#include <memory>


namespace streamer
{

class SharedMemory;
class CSICamera;

class VideoStreamer
{
public:
    VideoStreamer(std::shared_ptr<CSICamera> camera,
                  std::shared_ptr<SharedMemory> memory);
    ~VideoStreamer();

    void StartCapturing();
    void StopCapturing();

protected:

private:
    std::shared_ptr<CSICamera> camera_;
    std::shared_ptr<SharedMemory> sharedMemory_;

};


} // namespace streamer


#endif // STREAMER_SHARED_MEMORY_H_

