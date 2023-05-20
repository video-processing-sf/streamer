#include "video_streamer.h"
#include "frame.h"
#include "csi_camera.h"
#include "shared_memory.h"



namespace streamer
{

VideoStreamer::VideoStreamer(std::shared_ptr<CSICamera> camera,
                             std::shared_ptr<SharedMemory> memory)
 : camera_{camera}, sharedMemory_{memory}
{

}

VideoStreamer::~VideoStreamer()
{

}

void VideoStreamer::StartCapturing()
{

}

void VideoStreamer::StopCapturing()
{

}


} // namespace streamer



