#ifndef STREAMER_FRAME_H_
#define STREAMER_FRAME_H_

#include <cstdint>
#include "types.h"


namespace streamer
{

class Frame
{
public:
    Frame(data_ptr data, uint16_t w, uint16_t h);
    ~Frame();

    data_ptr GetData() const;
    uint16_t GetWidth() const;
    uint16_t GetHeight() const;


private:
    data_ptr data_;
    uint16_t width_;
    uint16_t height_;

};



} // namespace streamer


#endif // STREAMER_CSI_CAMERA_H_


