#include "csi_camera.h"
#include "pixel_formats.h"
#include <iostream>



namespace streamer
{

CSICamera::CSICamera(res_t resolution, const std::string& format, uint frame_rate)
 : resolution_{resolution}, pixelFormat_{format}, frameRate_{frame_rate}
{
}


CSICamera::~CSICamera()
{
}


uint CSICamera::GetFrameSize() const
{
    auto bytesPerPixel = GetBytesPerPixel(pixelFormat_);

    if (!bytesPerPixel)
    {
        std::cerr << "[ERROR][Streamer] No such format: " << pixelFormat_ << '\n';
        return 0;
    }

    return resolution_.first * resolution_.second * bytesPerPixel.value();
}


void CSICamera::SetResolution(res_t resolution)
{
    resolution_ = resolution;
}


res_t CSICamera::GetResolution() const
{
    return resolution_;
}


void CSICamera::SetPixelFormat(const std::string& format)
{
    pixelFormat_ = format;
}


std::string CSICamera::GetPixelFormat() const
{
    return pixelFormat_;
}


void CSICamera::SetFrameRate(uint rate)
{
    frameRate_ = rate;
}


uint CSICamera::GetFrameRate() const
{
    return frameRate_;
}


std::optional<double> CSICamera::GetBytesPerPixel(const std::string& pixel_format)
{
    if (PIXEL_FORMAT_MAP.find(pixel_format) == PIXEL_FORMAT_MAP.cend())
        return std::nullopt;

    return PIXEL_FORMAT_MAP.at(pixel_format);
}


} // namespace streamer

