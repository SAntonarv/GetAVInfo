#include <iostream>
extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
}

int main(int argc, const char *argv[]) {
    if (argc < 2) {
        std::cout << "Please specify media file\n";
        return -1;
    }

    AVFormatContext *pFormatContext = avformat_alloc_context();
    if (!pFormatContext) {
        std::cout << "Error with allocate RAM for format context\n";
        return -1;
    }

    if (avformat_open_input(&pFormatContext, argv[1], nullptr, nullptr) != 0) {
        std::cout << "Could not open the file\n";
        return -1;
    }

    if (avformat_find_stream_info(pFormatContext,  nullptr) < 0) {
        std::cout << "Could not get the stream info";
        return -1;
    }

    for (int i = 0; i < pFormatContext->nb_streams; i++) {
        AVCodecParameters *pLocalCodecParameters = pFormatContext->streams[i]->codecpar;
        std::cout << "\nStream " << i+1 <<":";
        if (pLocalCodecParameters->codec_type == AVMEDIA_TYPE_VIDEO) {
            std::cout << "\n\tVideo Codec name: " << avcodec_get_name(pLocalCodecParameters->codec_id) <<
            "\n\tContainer: " << pFormatContext->iformat->long_name <<
            "\n\tResolution: " << pLocalCodecParameters->width << " x " << pLocalCodecParameters->height <<
            "\n\tFrames count: " << pFormatContext->streams[i]->nb_frames;
        } else if (pLocalCodecParameters->codec_type == AVMEDIA_TYPE_AUDIO) {
            std::cout << "\n\tAudio Codec: " << avcodec_get_name(pLocalCodecParameters->codec_id) <<
            "\n\tChannels count: " << pLocalCodecParameters->channels <<
            "\n\tSample rate: " << pLocalCodecParameters->sample_rate <<
            "\n\tBitrate: " << pLocalCodecParameters->bit_rate/1024 << " kbit/s\n";
        }
    }
}