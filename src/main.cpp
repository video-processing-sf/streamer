#include <iostream>
#include "csi_camera.h"
#include "shared_memory.h"
#include "video_streamer.h"





int main()
{
	// todo: support for CLI configuration

	auto camera = std::make_shared<streamer::CSICamera>(/*camera configuration*/);
	auto memory = std::make_shared<streamer::SharedMemory>(camera->GetFrameSize());
	
	auto videoStreamer = std::make_shared<streamer::VideoStreamer>(camera, memory);
	videoStreamer->StartCapturing();
	std::cout << "[INFO] Capturing started!" << std::endl;


	return 0;
}


