#ifndef STREAMER_CSI_CAMERA_H_
#define STREAMER_CSI_CAMERA_H_

#include <memory>
#include "types.h"


namespace streamer
{

class Frame;

class CSICamera
{
public:
    CSICamera(/*params*/);
    ~CSICamera();

    std::shared_ptr<Frame> CaptureFrame() const;

    unsigned int GetFrameSize() const;

private:

};



} // namespace streamer


#endif // STREAMER_CSI_CAMERA_H_


