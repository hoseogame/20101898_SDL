#include "DWVideo.h"
#include "game.h"
#include "DWTime.h"

#define MAX_AUDIO_FRAME_SIZE 192000

DWAudioPacketQueue m_audio_q;
int quit = 0;  

AVFrame* m_audio_frame;

int audio_decode_frame(AVCodecContext *aCodecCtx, uint8_t *audio_buf,  
					   int buf_size) {  

						   static AVPacket pkt;
						   static uint8_t *audio_pkt_data = NULL;
						   static int audio_pkt_size = 0;

						   int len1, data_size = 0;

						   for(;;) {
							   while(audio_pkt_size > 0) {
								   int got_frame = 0;
								   len1 = avcodec_decode_audio4
									   (aCodecCtx, m_audio_frame, &got_frame, &pkt);

								   if(len1 < 0) 
								   {
									   audio_pkt_size = 0;
									   break;
								   }

								   audio_pkt_data += len1;
								   audio_pkt_size -= len1;
								   data_size = 0;

								   if(got_frame) 
								   {
									   data_size = 
										   av_samples_get_buffer_size(NULL, aCodecCtx->channels,
										   m_audio_frame->nb_samples,
										   aCodecCtx->sample_fmt, 1);
									   //assert(data_size <= buf_size);
									   memcpy(audio_buf, m_audio_frame->data[0], data_size);
								   }

								   if(data_size <= 0)
								   {
									   /* No data yet, get more frames */
									   continue;
								   }
								   /* We have data, return it and come back for more later */
								   return data_size;
							   }

							   if(pkt.data)
								   av_packet_unref(&pkt);

							   if(quit) {
								   return -1;
							   }

							   if(packet_queue_get(&m_audio_q, &pkt, 1) < 0) {
								   return -1;
							   }
							   audio_pkt_data = pkt.data;
							   audio_pkt_size = pkt.size;
						   }
}  

void AudioCallback(void *userdata, Uint8 *stream, int len)
{

	AVCodecContext *aCodecCtx = (AVCodecContext *)userdata;  
	int len1, audio_size;  

	static uint8_t audio_buf[(MAX_AUDIO_FRAME_SIZE * 3) / 2];  
	static unsigned int audio_buf_size = 0;  
	static unsigned int audio_buf_index = 0;  

	while(len > 0) {  
		if(audio_buf_index >= audio_buf_size) 
		{  
			/* We have already sent all our data; get more */  
			audio_size =
				audio_decode_frame(aCodecCtx, audio_buf,  
				sizeof(audio_buf));  
			if(audio_size < 0)
			{ 
				audio_buf_size = 1024;  
				memset(audio_buf, 0, audio_buf_size);
			}
			else
			{
				audio_buf_size = audio_size;  
			}

			audio_buf_index = 0;  
		} 

		len1 = audio_buf_size - audio_buf_index;  
		if(len1 > len)  
		{
			len1 = len;  
		}

		memcpy(stream, (uint8_t *)audio_buf + audio_buf_index, len1);  
		len -= len1;  
		stream += len1;  
		audio_buf_index += len1;  
	}  
}

void packet_queue_init(DWAudioPacketQueue *q) 
{  
	memset(q, 0, sizeof(DWAudioPacketQueue));  
	q->mutex = SDL_CreateMutex();  
	q->cond = SDL_CreateCond();  
}  

DWVideo::DWVideo(char* url)
{
	Init(url);

}

int packet_queue_put(DWAudioPacketQueue *q, AVPacket *pkt) {  

	AVPacketList *pkt1;  
	pkt1 = (AVPacketList*)av_malloc(sizeof(AVPacketList)); 

	if(av_packet_ref(&pkt1->pkt,pkt) < 0) {  
		av_free(pkt1);
		return -1;  
	}  

	if (!pkt1)  
		return -1;  
	pkt1->pkt = *pkt;  
	pkt1->next = NULL;  


	SDL_LockMutex(q->mutex);  

	if (!q->last_pkt)  
		q->first_pkt = pkt1;  

	else  
		q->last_pkt->next = pkt1;

	q->last_pkt = pkt1;  
	q->nb_packets++;  
	q->size += pkt1->pkt.size;  
	SDL_CondSignal(q->cond);  

	SDL_UnlockMutex(q->mutex);  
	return 0;  
} 


static int packet_queue_get(DWAudioPacketQueue * q, AVPacket * pkt, int block)  
{  
	AVPacketList   *pkt1;  

	int             ret;  

	SDL_LockMutex(q->mutex);  

	for (;;)  
	{  

		if (quit)  
		{  
			ret = -1;  
			break;  
		}  

		pkt1 = q->first_pkt;  
		if (pkt1 != nullptr)  
		{  
			q->first_pkt = pkt1->next;  
			if (q->first_pkt == nullptr) 
			{
				q->last_pkt = nullptr; 
			}
			q->nb_packets--;  
			q->size -= pkt1->pkt.size;  
			*pkt = pkt1->pkt;  
			av_free(pkt1);  
			ret = 1;  
			break;  
		}  
		else if (!block)  
		{  
			ret = 0;  
			break;  
		}  
		else  
		{  
			SDL_CondWait(q->cond, q->mutex);  
		}  
	}  
	SDL_UnlockMutex(q->mutex);  
	return ret;  
}  

int decode_interrupt_cb(void) {  
	return quit;  
}  

DWVideo::~DWVideo(void)
{
	SDL_DestroyTexture(m_texture);
	quit = 1;

	av_frame_free(&m_frame);
	//이부분 수정 조심해야함 스테틱이라 다시 초기화시켜줘야함
	av_frame_free(&m_audio_frame);
	avcodec_close(m_codec_context);

	avformat_close_input(&m_avformat_context);

//	SDL_CloseAudio();

}

bool DWVideo::Init(const char* url)
{

	m_audio_frame = av_frame_alloc();

	if(avformat_open_input(&m_avformat_context,url,NULL,NULL))
	{
		exit(-1);
	}

	if(avformat_find_stream_info(m_avformat_context, NULL))
	{
		return false;
	}

	av_dump_format(m_avformat_context,0,url,0);


	video_stream = -1;
	audio_stream = -1;

	for(int i =0; i < m_avformat_context->nb_streams; i++)
	{
		if(m_avformat_context->streams[i]->
			codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
		{
			video_stream = i;
		}else if(m_avformat_context->streams[i]->
			codecpar->codec_type == AVMEDIA_TYPE_AUDIO)
		{
			audio_stream = i;
		}
	}

	if(video_stream == -1)
	{
		fprintf(stderr,"비디오 스트림 못찾음 !\n");
		return false;
	}
	if(audio_stream == -1)
	{
		fprintf(stderr,"오디오 스트림 못찾음 !\n");
		return false;
	}
/*
	m_audio_codec_context_orig =
		m_avformat_context->streams[audio_stream]->codecpar;

	m_audio_codec =
		avcodec_find_decoder(m_audio_codec_context_orig->codec_id);

	if(m_audio_codec == NULL)
	{
		fprintf(stderr,"오디오 코덱 못 열음!\n");
		return false;
	}

	m_audio_codec_context = avcodec_alloc_context3(m_audio_codec);
	if(avcodec_parameters_to_context(m_audio_codec_context,m_audio_codec_context_orig) != 0)
	{
		return false;
	}

	if(avcodec_open2(m_audio_codec_context,m_audio_codec,NULL)<0)
	{
		return false;
	}
	
	packet_queue_init(&m_audio_q);
	m_wanted_spec.freq = m_audio_codec_context->sample_rate;
	m_wanted_spec.format = AUDIO_S16SYS;
	m_wanted_spec.channels = m_audio_codec_context->channels;
	m_wanted_spec.silence = 0;
	//sdl이 추가 오디오 데이터를 요구할때 버퍼 사이즈
	m_wanted_spec.samples = 8000;
	m_wanted_spec.callback = AudioCallback;
	m_wanted_spec.userdata = m_audio_codec_context;

	if(SDL_OpenAudio(&m_wanted_spec,&m_spec) < 0)
	{
		fprintf(stderr,"오디오 오픈 실패 !\n");
		return false;
	}

	SDL_PauseAudio(0);*/
	
	m_codec_context_orig =
		m_avformat_context->streams[video_stream]->codecpar;


	m_codec = avcodec_find_decoder(m_codec_context_orig->codec_id);
	if(m_codec == NULL)
	{
		fprintf(stderr,"코덱 못찾음 !\n");
		return false;
	}

	m_codec_context = avcodec_alloc_context3(m_codec);
	if(avcodec_parameters_to_context(m_codec_context,m_codec_context_orig) != 0)
	{
		return false;
	}

	if(avcodec_open2(m_codec_context,m_codec,NULL)<0)
	{
		return false;
	}



	m_frame = av_frame_alloc();

	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO|SDL_INIT_TIMER))
	{
		fprintf(stderr, "SDL초기화 에러 \n");
		return false;
	}
	
	m_texture = SDL_CreateTexture
		(game::Instance()->getRenderer(),SDL_PIXELFORMAT_IYUV,SDL_TEXTUREACCESS_STREAMING,
		m_codec_context_orig->width,m_codec_context_orig->height);


	delay_time = 1000.0f/FPS;
	start_time = 0;
	return true;
}


void DWVideo::draw()
{
	if(frame_end)
	{
		SDL_UpdateYUVTexture(m_texture,NULL,m_frame->data[0],m_frame->width,
			m_frame->data[1],m_frame->linesize[1],m_frame->data[2],m_frame->linesize[2]);

		TextureManager::Instance()->drawVideo(m_texture,
			(int)m_position.getX(), (int)m_position.getY(),m_width, m_height,game::Instance()->getRenderer());
	}
}

void DWVideo::update()
{
	
}

void DWVideo::update2()
{
	start_time += DWTime::Instance()->GetDeltaTime();
	if(start_time > delay_time)
	{

		start_time = 0;
		if(av_read_frame(m_avformat_context,&packet) >= 0)
		{
			if(packet.stream_index == video_stream)
			{
				//if(m_codec_context != NULL)
					avcodec_decode_video2(m_codec_context,m_frame,&frame_end,&packet);
			}
			else if(packet.stream_index == audio_stream)
			{  
				//	packet_queue_put(&m_audio_q, &packet); 
			} 
			else 
			{  
				av_packet_unref(&packet);  
			}  
		}
	}
}

void DWVideo::clean()
{
}

void DWVideo::load(const LoadParams* pParams)
{
	first_set_params = pParams;

	m_position = Vector2D( pParams->getX(), pParams->getY() );

	m_velocity = Vector2D( 0.0f, 0.0f );

	m_acceleration = Vector2D( 0.0f, 0.0f );

	m_width = pParams->getWidth();

	m_height = pParams->getHeight();

	m_textureID = pParams->getTextureID();
	
	FPS = pParams->getNumFrames();

	Init(m_textureID.c_str());
}

