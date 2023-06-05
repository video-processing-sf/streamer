#ifndef STREAMER_PIXEL_FORMATS_H_
#define STREAMER_PIXEL_FORMATS_H_

#include <map>



namespace streamer
{

const std::map<std::string, double> PIXEL_FORMAT_MAP =
{
    {"RGB",     3.0},
    {"RGBA",    4.0},
    {"YUYV",    2.0},
    {"NV12",    3.0},
    {"GRAY8",   1.0},
};



} // namespace streamer


#endif // STREAMER_PIXEL_FORMATS_H_

