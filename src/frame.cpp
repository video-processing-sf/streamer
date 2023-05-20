#include "frame.h"



namespace streamer
{


Frame::Frame(data_ptr data, uint16_t w, uint16_t h)
 : data_{data}, width_{w}, height_{h}
{

}

Frame::~Frame()
{
    
}

data_ptr Frame::GetData() const
{
    return data_;
}

uint16_t Frame::GetWidth() const
{
    return width_;
}

uint16_t Frame::GetHeight() const
{
    return height_;
}



} // namespace streamer



