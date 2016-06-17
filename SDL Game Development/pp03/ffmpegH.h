#ifndef FFMPEGH_H_

#define FFMPEGH_H_

extern "C" //FFmpeg�� C���̺귯���̱� ������ �̺κ��� �ʿ��ϴ�.
{
#include "libavcodec\avcodec.h"
#include "libavdevice\avdevice.h"
#include "libavfilter\avfilter.h"
#include "libavformat\avformat.h"
#include "libavutil\avutil.h"
#include "libswresample\swresample.h"
#include "libswscale\swscale.h"
}
 
#pragma comment ( lib, "avcodec.lib" )
#pragma comment ( lib, "avdevice.lib")
#pragma comment ( lib, "avfilter.lib")
#pragma comment ( lib, "avformat.lib")
#pragma comment ( lib, "avutil.lib")
#pragma comment ( lib, "swresample.lib")
#pragma comment ( lib, "swscale.lib")

#endif