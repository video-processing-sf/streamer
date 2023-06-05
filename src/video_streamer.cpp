#include "video_streamer.h"
#include "csi_camera.h"
#include "shared_memory.h"
#include <sstream>
#include <iostream>


namespace streamer
{


VideoStreamer::VideoStreamer(std::shared_ptr<CSICamera> camera,
                             std::shared_ptr<SharedMemory> memory)
 : camera_{camera}, sharedMemory_{memory}
{
    this->configPipeline();
}


VideoStreamer::~VideoStreamer()
{
    this->destroyPipeline();
}


void VideoStreamer::configPipeline()
{
    auto cameraRes = camera_->GetResolution();
    std::stringstream pipelineCMD;
    pipelineCMD << "nvarguscamerasrc ! "
                << "video/x-raw(memory:NVMM)"
                        << ", width=" <<  camera_->GetResolution().first
                        << ", height=" << camera_->GetResolution().second
                        << ", format=" << camera_->GetPixelFormat()
                        << ", framerate=" << camera_->GetFrameRate() << "/1 ! "
                << "nvvidconv ! "
                << "video/x-raw,format=GRAY8 ! "
                << "appsink name=sink";

    pipeline_ = gst_parse_launch(pipelineCMD.str().c_str(), nullptr);
    sink_ = GST_APP_SINK(gst_bin_get_by_name(GST_BIN(pipeline_), "sink"));

    GstAppSinkCallbacks callbacks;
    callbacks.eos = eosCB;
    callbacks.new_preroll = prerollCB;
    callbacks.new_sample = sampleCB;

    gst_app_sink_set_callbacks(
        sink_,
        &callbacks,
        this,
        nullptr);

    loop_ = g_main_loop_new(nullptr, FALSE);
}


void VideoStreamer::destroyPipeline()
{
    GstState state;
    GstStateChangeReturn ret = gst_element_get_state(pipeline_, &state, NULL, GST_CLOCK_TIME_NONE);
    if (state == GST_STATE_PLAYING)
        gst_element_set_state(GST_ELEMENT(pipeline_), GST_STATE_NULL);

    g_main_loop_unref(loop_);
    gst_object_unref(sink_);
    gst_object_unref(pipeline_);
    g_print("[INFO][Streamer] Pipeline was destroyed.\n");
}


bool VideoStreamer::IsCapturing()
{
    return isCapturing_.load();
}


void VideoStreamer::StartCapturing()
{
    gst_element_set_state(GST_ELEMENT(pipeline_), GST_STATE_PLAYING);
    g_main_loop_run(loop_);
    isCapturing_.store(true);
    g_print("[INFO][Streamer] Pipeline stared playing.\n");

}


void VideoStreamer::StopCapturing()
{
    g_main_loop_quit(loop_);
    gst_element_set_state(GST_ELEMENT(pipeline_), GST_STATE_NULL);
    isCapturing_.store(false);
    g_print("[INFO][Streamer] Pipeline was stopped.\n");
}


void VideoStreamer::shmemWrite(data_ptr_t data)
{
    if(sharedMemory_)
        sharedMemory_->WriteData(data);
}


void VideoStreamer::eosCB(GstAppSink* appsink, gpointer user_data)
{
    std::cout << "[INFO][Streamer] End-Of-Stream callback\n";
}


GstFlowReturn VideoStreamer::prerollCB(GstAppSink* appsink, gpointer user_data)
{
    return GST_FLOW_OK;
}


GstFlowReturn VideoStreamer::sampleCB(GstAppSink* appsink, gpointer user_data)
{
    GstSample* sample = gst_app_sink_pull_sample(appsink);
    GstBuffer* buffer = gst_sample_get_buffer(sample);

    GstMapInfo map_info;
    gst_buffer_map(buffer, &map_info, GST_MAP_READ);

    auto videoStreamer = static_cast<VideoStreamer*>(user_data);
    videoStreamer->shmemWrite(map_info.data);

    gst_buffer_unmap(buffer, &map_info);
    gst_sample_unref(sample);

    return GST_FLOW_OK;
}



} // namespace streamer



