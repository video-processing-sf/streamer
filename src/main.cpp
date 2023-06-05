#include "csi_camera.h"
#include "shared_memory.h"
#include "video_streamer.h"
#include <iostream>




int main(int argc, char** argv)
{
    int shmKey = 12345;
    gst_init(nullptr, nullptr);

    auto camera = std::make_shared<streamer::CSICamera>(
        std::make_pair(2592, 1944),
        "NV12",
        30);

    int shmSize = camera->GetResolution().first *
                  camera->GetResolution().second *
                  streamer::CSICamera::GetBytesPerPixel("GRAY8").value();
    auto memory = std::make_shared<streamer::SharedMemory>(shmKey, shmSize);
    auto videoStreamer = std::make_shared<streamer::VideoStreamer>(camera, memory);
	
    videoStreamer->StartCapturing();
    std::cout << "[INFO] Capturing started!" << std::endl;

    gst_deinit();
    return 0;
}

