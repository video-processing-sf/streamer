#ifndef STREAMER_CSI_CAMERA_H_
#define STREAMER_CSI_CAMERA_H_

#include <optional>
#include "types.h"



namespace streamer
{


class CSICamera
{
public:
    CSICamera(res_t resolution, const std::string& format, uint frame_rate);
    ~CSICamera();

    uint GetFrameSize() const;

    void SetResolution(res_t resolution);
    res_t GetResolution() const;

    void SetPixelFormat(const std::string& format);
    std::string GetPixelFormat() const;

    void SetFrameRate(uint rate);
    uint GetFrameRate() const;

    static std::optional<double> GetBytesPerPixel(const std::string& pixel_format);

private:
    res_t resolution_;
    std::string pixelFormat_;
    uint frameRate_;

};


} // namespace streamer


#endif // STREAMER_CSI_CAMERA_H_

