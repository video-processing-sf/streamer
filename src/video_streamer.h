#ifndef STREAMER_VIDEO_STREAMER_H_
#define STREAMER_VIDEO_STREAMER_H_

#include <memory>
#include <atomic>
#include "gst/app/gstappsink.h"
#include "gst/gst.h"
#include "types.h"


namespace streamer
{

class SharedMemory;
class CSICamera;

class VideoStreamer
{
public:
    VideoStreamer(std::shared_ptr<CSICamera> camera,
                  std::shared_ptr<SharedMemory> memory);
    ~VideoStreamer();

    void StartCapturing();
    void StopCapturing();

    bool IsCapturing();

protected:
    void configPipeline();
    void destroyPipeline();
    void shmemWrite(data_ptr_t data);

    static void eosCB(GstAppSink* appsink, gpointer user_data);
    static GstFlowReturn prerollCB(GstAppSink* appsink, gpointer user_data);
    static GstFlowReturn sampleCB(GstAppSink* appsink, gpointer user_data);


private:
    std::shared_ptr<CSICamera> camera_;
    std::shared_ptr<SharedMemory> sharedMemory_;

    GstElement* pipeline_ = nullptr;
    GstAppSink* sink_ = nullptr;
    GMainLoop* loop_ = nullptr;
    std::atomic<bool> isCapturing_ = false;
};


} // namespace streamer


#endif // STREAMER_SHARED_MEMORY_H_

