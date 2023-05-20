#include "csi_camera.h"
#include "frame.h"



namespace streamer
{


CSICamera::CSICamera(/*params*/)
{

}

CSICamera::~CSICamera()
{

}

std::shared_ptr<Frame> CSICamera::CaptureFrame() const
{
    return {};
}

unsigned int CSICamera::GetFrameSize() const
{
    return {};
}


} // namespace streamer



