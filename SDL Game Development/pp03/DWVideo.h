#pragma once

#include"ffmpegH.h"
#include "SDL.h"
#include"SDLGameObject.h"
#include "BaseCreator.h"

struct DWAudioPacketQueue
{
	AVPacketList *first_pkt, *last_pkt;
	int nb_packets;
	int size;
	SDL_mutex * mutex;
	SDL_cond *cond;
};

static int packet_queue_get(DWAudioPacketQueue * q, AVPacket * pkt, int block) ;
int audio_decode_frame(AVCodecContext *aCodecCtx, uint8_t *audio_buf,int buf_size);
void AudioCallback(void *userdata, Uint8 *stream, int len);
void packet_queue_init(DWAudioPacketQueue *q);
int packet_queue_put(DWAudioPacketQueue *q, AVPacket *pkt);


class DWVideo:
	public SDLGameObject
{
public:
	DWVideo(char* url);
	DWVideo() 
	{
	}

	virtual bool Init(const char* url);
	~DWVideo(void);

	
	virtual void draw();

	virtual void update();

	virtual void update2();

	virtual void clean();

	virtual void load(const LoadParams* pParams);

//	static AVFrame* m_audio_frame;

protected:
	int video_stream;
	int audio_stream;

	AVFormatContext* m_avformat_context;
	AVCodecParameters * m_codec_context_orig;
	AVCodecContext* m_codec_context;
	AVCodec* m_codec;
	AVFrame* m_frame;

	int FPS;
	int delay_time;
	Uint32 start_time;

	//audio
	AVCodecParameters * m_audio_codec_context_orig;
	AVCodecContext* m_audio_codec_context;
	AVCodec* m_audio_codec;
	SDL_AudioSpec m_wanted_spec;
	SDL_AudioSpec m_spec;

	
	SDL_Texture* m_texture;
	AVPacket packet;
	int frame_end;



};


class VideoCreator : public BaseCreator
{
public:
	virtual GameObject* createGameObject() const
	{
		return new DWVideo();
	}
};