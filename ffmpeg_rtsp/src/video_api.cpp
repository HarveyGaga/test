/*
 * 这个文件是获取视频api文件
 *
 *
 */
#include <stdio.h>
#include "logger.h"
#include "video_api.h"
#include "opencv2/core/core.hpp" 
#include "opencv2/highgui/highgui.hpp" 
#include "opencv2/imgproc/imgproc.hpp"
//#include "opencv2/gpu/gpu.hpp"
#include <sys/types.h>
#include <unistd.h>
#include "utimer.hpp"

AVPacket *av_packet_alloc(void) {
	AVPacket *pkt = (AVPacket *) av_mallocz(sizeof(AVPacket));
	if (!pkt)
		return pkt;

	av_packet_unref(pkt);

	return pkt;
}

void av_packet_free(AVPacket **pkt) {
	if (!pkt || !*pkt)
		return;

	av_packet_unref(*pkt);
	av_freep(pkt);
}

AVPacket *av_packet_clone(const AVPacket *src) {
	AVPacket *ret = av_packet_alloc();

	if (!ret)
		return ret;

	if (av_packet_ref(ret, src))
		av_packet_free(&ret);

	return ret;
}
#if 0
void av_init_packet1(AVPacket *pkt)
{
	pkt->pts = AV_NOPTS_VALUE;
	pkt->dts = AV_NOPTS_VALUE;
	pkt->pos = -1;
	pkt->duration = 0;
	pkt->convergence_duration = 0;
	pkt->flags = 0;
	pkt->stream_index = 0;
	pkt->buf = NULL;
	pkt->side_data = NULL;
	pkt->side_data_elems = 0;
	pkt->destruct = NULL;
	pkt->priv = NULL;
}
#endif
/*将avcodec_decode_video2解码数据转成rgb图片数据*/
int yuv420torgb(char *yuvbuf, int yuvsize) {

	return 0;
}

/*打开rtsp数据流*/
int ffmpeg_open_rtsp(char *rtsppath, AVFormatContext **pFormatCtx) {
	AVDictionary *optionsDict = NULL;

	//av_dict_set(&optionsDict, "pixel_format", "yuv420p", 0);
	//av_dict_set(&optionsDict, "pixel_format", "rgb24", 0);
	av_dict_set(&optionsDict, "rtsp_transport", "tcp", 0);

	// Open video file
	if (avformat_open_input(pFormatCtx, rtsppath, NULL, &optionsDict) != 0)
		return -1; // Couldn't open file
	return 0;
}

/*视频流初始化*/
int ffmpeg_init(char *rtsppath, AVFormatContext **pFormatCtx, AVCodecContext **pCodecCtx, int *videoStream, struct SwsContext **sws_ctx, AVFrame **pFrameRGB) {
	int i;
	AVCodec *pCodec = NULL;
	AVStream *pStream = NULL;

	int numBytes;
	uint8_t *buffer = NULL;
	AVDictionary *optionsDict = NULL;

	int ret;
	int fps;

	/*ffmpeg 打开rtsp数据流*/
	ret = ffmpeg_open_rtsp(rtsppath, pFormatCtx);
	if (ret < 0) {
		ERR("ffmpeg_open_rtsp err.");
		return -1;
	}

	// Retrieve stream information
	if (avformat_find_stream_info(*pFormatCtx, NULL) < 0)
		return -1; // Couldn't find stream information

	// Dump information about file onto standard error
	av_dump_format(*pFormatCtx, 0, rtsppath, 0);

	// Find the first video stream
	*videoStream = av_find_best_stream(*pFormatCtx, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0);
#if 1
	*videoStream = -1;
	for (i = 0; i < (*pFormatCtx)->nb_streams; i++) {
		if ((*pFormatCtx)->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
			*videoStream = i;
			break;
		}
	}
#endif
	DBG("pFormatCtx->nb_streams = %d", (*pFormatCtx)->nb_streams);
	DBG("videoStream = %d", *videoStream);
	if (*videoStream == -1)
		return -1; // Didn't find a video stream

	// Get a pointer to the codec context for the video stream
	pStream = (*pFormatCtx)->streams[*videoStream];
	fps = pStream->avg_frame_rate.num / pStream->avg_frame_rate.den;
	DBG("[info]pStream->avg_frame_rate.num = %d", pStream->avg_frame_rate.num);
	DBG("[info]pStream->avg_frame_rate.den = %d", pStream->avg_frame_rate.den);

	*pCodecCtx = (*pFormatCtx)->streams[*videoStream]->codec;

	// Find the decoder for the video stream
	pCodec = avcodec_find_decoder((*pCodecCtx)->codec_id);
	if (pCodec == NULL) {
		ERR("Unsupported codec!");
		return -1; // Codec not found
	}
	// Open codec
	if (avcodec_open2(*pCodecCtx, pCodec, &optionsDict) < 0)
		return -1; // Could not open codec

	DBG("[info]pCodecCtx->pix_fmt = %d", (*pCodecCtx)->pix_fmt);

	// Allocate an AVFrame structure
	*pFrameRGB = av_frame_alloc();
	if (*pFrameRGB == NULL)
		return -1;

	// Determine required buffer size and allocate buffer
	numBytes = avpicture_get_size(AV_PIX_FMT_BGR24, (*pCodecCtx)->width, (*pCodecCtx)->height);
	buffer = (uint8_t *) av_malloc(numBytes * sizeof(uint8_t));

	printf("pix_fmt = %d\n", (*pCodecCtx)->pix_fmt);

#if 1
	*sws_ctx = sws_getContext((*pCodecCtx)->width, (*pCodecCtx)->height, (*pCodecCtx)->pix_fmt, (*pCodecCtx)->width, (*pCodecCtx)->height, AV_PIX_FMT_BGR24,
	SWS_BICUBIC,
	NULL,
	NULL,
	NULL);
#endif
#if 1
	// Assign appropriate parts of buffer to image planes in pFrameRGB
	// Note that pFrameRGB is an AVFrame, but AVFrame is a superset
	// of AVPicture
	// AV_PIX_FMT_BGR24
	avpicture_fill((AVPicture *) (*pFrameRGB), buffer, AV_PIX_FMT_BGR24, (*pCodecCtx)->width, (*pCodecCtx)->height);
	av_freep(buffer);
#endif
	return 0;
}

/*关闭ffmpeg*/
int ffmpeg_close(AVFormatContext *pFormatCtx, AVCodecContext *pCodecCtx, struct SwsContext *sws_ctx, AVFrame *pFrameRGB) {
	sws_freeContext(sws_ctx);
	av_frame_unref(pFrameRGB);
	av_frame_free(&pFrameRGB);
	avcodec_close(pCodecCtx);

	avformat_close_input(&pFormatCtx);
	avcodec_free_context(&pCodecCtx);
	pFormatCtx = NULL;
	pCodecCtx = NULL;

	sws_ctx = NULL;
	pFrameRGB = NULL;
	return 0;
}

/*读取视频流帧*/
int ffmpeg_read_frame(AVFormatContext *pFormatCtx, AVPacket *tmppacket) {
	//AVPacket  packet;
	int ret = 0;

	//av_init_packet(&packet);
	//av_init_packet(tmppacket);
	//DBG("begin av_read_frame.");
	ret = av_read_frame(pFormatCtx, tmppacket);
	if (ret < 0) {
		ERR("av_read_frame error.");
		return -1;
	}
	//*tmppacket = av_packet_clone(&packet);
	//av_packet_unref(&packet);
	//av_free_packet(&packet);
	return 0;
}

/*旋转函数*/
int rotation(cv::Mat src, cv::Mat &dst, double angle) {

	cv::Point2f center(src.cols / 2, src.rows / 2);
	cv::Mat rot = cv::getRotationMatrix2D(center, angle, 1);
	cv::Rect bbox = cv::RotatedRect(center, cv::Size(src.cols / 3 * 2, src.rows), angle).boundingRect();
	rot.at<double>(0, 2) += bbox.width / 2.0 - center.x;
	rot.at<double>(1, 2) += bbox.height / 2.0 - center.y;
	cv::warpAffine(src, dst, rot, bbox.size());
	return 0;
}

int ffmpeg_decode_video(AVCodecContext *pCodecCtx, struct SwsContext *sws_ctx, AVPacket *packet, int videoStream, AVFrame *pFrameRGB) {
	AVFrame *pFrame = NULL;
	int frameFinished = 1;
	static int index = 0;
	char tmpbuf[64] = { 0x0 };
	char *yuvbuf;
	struct timespec time_begin, time_end;

	yuvbuf = (char *) malloc(1920 * 1080 * 3);

	pFrame = av_frame_alloc();

	if (packet->stream_index == videoStream) {
		if (packet->flags & AV_PKT_FLAG_KEY) {
			//DBG("1has_b_frames = %d,refs = %d",pCodecCtx->has_b_frames,pCodecCtx->refs);
			//DBG("thread:%u-关键帧:%d.",pthread_self(),packet->flags);
			//avcodec_flush_buffers(pCodecCtx);
			//DBG("2has_b_frames = %d,refs = %d",pCodecCtx->has_b_frames,pCodecCtx->refs);
		} else {
			//DBG("thread:%u-其他帧:%d.",pthread_self(),packet->flags);
			//return 0;
		}
//        DBG("packet->flags = %d.",packet->flags);
//        DBG("packet->size = %d.",packet->size);
#if 0
		FILE *fp;
		fp = fopen("tmp.jpg","wb+");
		if (fp)
		{
			fwrite(packet->data,sizeof(char),packet->size,fp);
			fclose(fp);
		}

		printf("height = %d;width = %d;packet.size = %d;\n",pCodecCtx->height, pCodecCtx->width,packet->size);
		cv::Mat picimg(pCodecCtx->height, pCodecCtx->width, CV_8UC3, packet->data, packet->size);
		cv::imshow("TEST", picimg);

		cvWaitKey(1);
#endif
#if 1
//		while (1) {
		UTimer timer;
		timer.Start();
		avcodec_decode_video2(pCodecCtx, pFrame, &frameFinished, packet);
		printf("over time:%f\n", timer.Elapse() * 1000);
//		}
#endif
		clock_gettime(CLOCK_REALTIME, &time_end);

		// Did we get a video frame?
		if (frameFinished) {
#if 1
//			UTimer timer;
//			timer.Start();
//			sws_scale(sws_ctx, (uint8_t const * const *) pFrame->data, pFrame->linesize, 0, pCodecCtx->height, pFrameRGB->data, pFrameRGB->linesize);
//			printf("over time:%f\n", timer.Elapse() * 1000);

//			cv::Mat picimg(pCodecCtx->height, pCodecCtx->width, CV_8UC1, pFrame->data[0], pFrameRGB->linesize[0]);
//			cv::Mat picimg(pCodecCtx->height, pCodecCtx->width, CV_8UC3, pFrameRGB->data[0], pFrameRGB->linesize[0]);
			//cv::Mat picimg(pCodecCtx->height, pCodecCtx->width, CV_8UC3, pFrameRGB->data[0], pFrameRGB->linesize[0]);
//			cv::imshow("TEST", picimg);
//			cvWaitKey(1);
			//clock_gettime(CLOCK_REALTIME,&time_end);
			//printf("over time:%d\n",time_end.tv_sec *1000 + time_end.tv_nsec/1000000 - time_begin.tv_sec *1000 - time_begin.tv_nsec/1000000);

#endif
#if 0
			YUV420_To_BGR24(pFrame->data[0],pFrame->data[1],
					pFrame->data[2],(unsigned char *)yuvbuf,1920,1080);
			cv::Mat picimg(1920, 1080, CV_8UC3, (void*)yuvbuf);
			cv::imshow("TEST", picimg);

			cvWaitKey(1);
#endif
#if 0
			//clock_gettime(CLOCK_REALTIME,&time_begin);
			memcpy(yuvbuf,pFrame->data[0],1920*1080);
			memcpy(yuvbuf + 1920*1080,pFrame->data[1],1920*1080>>2);
			memcpy(yuvbuf + 1920*1080 + (1920*1080>>2),pFrame->data[2],1920*1080>>2);
			cv::Mat src(1080*3/2, 1920, CV_8UC1, (void*)yuvbuf);
			cv::Mat picimg;
			clock_gettime(CLOCK_REALTIME,&time_begin);
			cv::cvtColor(src, picimg, CV_YUV420p2RGB);
			cv::imshow("TEST", picimg);

			cvWaitKey(1);
			clock_gettime(CLOCK_REALTIME,&time_end);
			printf("over time:%d\n",time_end.tv_sec *1000 + time_end.tv_nsec/1000000 - time_begin.tv_sec *1000 - time_begin.tv_nsec/1000000);
#endif
#if 0
			memcpy(yuvbuf,pFrame->data[0],1920*1080);
			memcpy(yuvbuf + 1920*1080,pFrame->data[1],1920*1080>>2);
			memcpy(yuvbuf + 1920*1080 + (1920*1080>>2),pFrame->data[2],1920*1080>>2);
			cv::Mat src(1080*3/2, 1920, CV_8UC1, (void*)yuvbuf);
			cv::gpu::GpuMat d_src, d_dst;
			cv::Mat picimg;
			d_src.upload(src);
			DBG("1");
			cv::gpu::cvtColor(d_src, d_dst, CV_YCrCb2BGR);
			DBG("2");
			d_dst.download(picimg);
			//cv::cvtColor(yuvImg, rgbImg, CV_YUV2RGB_YUYV);
			//cv::cvtColor(src, picimg, CV_YUV420p2RGB);
			//cv::Mat picimg(pCodecCtx->height, pCodecCtx->width, CV_8UC3, pFrameRGB->data[0], pFrameRGB->linesize[0]);
			cv::imshow("TEST", picimg);

			cvWaitKey(1);

#endif
#if 0
			memcpy(yuvbuf,pFrame->data[0],1920*1080);
			memcpy(yuvbuf + 1920*1080,pFrame->data[1],1920*1080>>2);
			memcpy(yuvbuf + 1920*1080 + (1920*1080>>2),pFrame->data[2],1920*1080>>2);
			cv::Mat src(1080*3/2, 1920, CV_8UC1, (void*)yuvbuf);
			cv::gpu::GpuMat d_src, d_dst;
			cv::Mat picimg;
			cv::Mat picimg2;
			cv::cvtColor(src, picimg, CV_YUV420p2RGB);
#if 0
			clock_gettime(CLOCK_REALTIME,&time_begin);
			d_src.upload(picimg);
			cv::Size tmpsize(1920,1080);
			cv::gpu::rotate(d_src, d_dst,tmpsize, 180,1920,1080);
			d_dst.download(picimg);
			clock_gettime(CLOCK_REALTIME,&time_end);
			DBG("gpu rotate overtime:%ld",time_end.tv_sec*1000000 + time_end.tv_nsec/1000 - time_begin.tv_sec*1000000 - time_begin.tv_nsec/1000);
#endif
#if 0
			//cv::imwrite("test_gpu.jpg",picimg);
			clock_gettime(CLOCK_REALTIME,&time_begin);
			rotation(picimg,picimg2,180);
			clock_gettime(CLOCK_REALTIME,&time_end);
			DBG("cpu rotate overtime:%ld",time_end.tv_sec*1000000 + time_end.tv_nsec/1000 - time_begin.tv_sec*1000000 - time_begin.tv_nsec/1000);
			//cv::imwrite("test_cpu.jpg",picimg2);
#endif
			//cv::cvtColor(yuvImg, rgbImg, CV_YUV2RGB_YUYV);
			//cv::cvtColor(src, picimg, CV_YUV420p2RGB);
			//cv::Mat picimg(pCodecCtx->height, pCodecCtx->width, CV_8UC3, pFrameRGB->data[0], pFrameRGB->linesize[0]);
			cv::imshow("TEST", picimg);

			cvWaitKey(1);

#endif
		}

		av_frame_unref(pFrame);
		av_frame_free(&pFrame);
		free(yuvbuf);
	}
	return 0;
}

/*ffmpeg获取rtsp视频*/
void* ffmpeg_get_video(void* lpParam) {
	AVFormatContext *pFormatCtx = NULL;
	AVCodecContext *pCodecCtx = NULL;
	int videoStream;
	struct SwsContext *sws_ctx = NULL;
	AVFrame *pFrameRGB = NULL;
	AVPacket packet;
	int ret;
	int count = 0;

	struct timespec time_begin, time_end;

	//cv::namedWindow("TEST", CV_WINDOW_NORMAL);

	DBG("ffmpeg_init.");
	pFormatCtx = NULL;
	pCodecCtx = NULL;
	sws_ctx = NULL;
	pFrameRGB = NULL;
	/*ffmpeg初始化*/
	ret = ffmpeg_init((char *) lpParam, &pFormatCtx, &pCodecCtx, &videoStream, &sws_ctx, &pFrameRGB);
	if (ret < 0) {
		DBG("ffmpeg_init error.");
		return NULL;
	}

	while (1) {
		//DBG("begin to ffmpeg_read_frame.");
		/*读取视频流*/
		ret = ffmpeg_read_frame(pFormatCtx, &packet);
		if (ret < 0) {
			DBG("ffmpeg_read_frame error.");
			//ffmpeg_close(pFormatCtx,pCodecCtx,sws_ctx,pFrameRGB);
			//goto FFMPEG_INIT;
			exit(0);
		}
#if 0
		if (packet->flags & AV_PKT_FLAG_KEY)
		{
			DBG("thread:%u-读取帧个数:%d.",pthread_self(),count);
			//avcodec_flush_buffers(pCodecCtx);
			count = 0;
		} else
		{
			count++;
			//DBG("thread:%u-其他帧:%d.",pthread_self(),packet->flags);
		}
#endif
#if 1

		clock_gettime(CLOCK_REALTIME, &time_begin);
		//DBG("begin to ffmpeg_decode_video.");
		ret = ffmpeg_decode_video(pCodecCtx, sws_ctx, &packet, videoStream, pFrameRGB);
		clock_gettime(CLOCK_REALTIME, &time_end);

		//DBG("begin time:%ld-%ld",time_begin.tv_sec,time_begin.tv_nsec);
		//DBG("end time:%ld-%ld",time_end.tv_sec,time_end.tv_nsec);
		//DBG("overtime:%ld",time_end.tv_sec*1000000 + time_end.tv_nsec/1000 - time_begin.tv_sec*1000000 - time_begin.tv_nsec/1000);
#endif
		av_packet_unref(&packet);
		av_free_packet(&packet);
	}
	return NULL;
}

void ffmpeg_all_init() {
	// Register all formats and codecs
	av_register_all();

	avformat_network_init();
}

void *ffmpeg_get_video_direct(void* lpParam) {
	int i;
	AVCodec *pCodec = NULL;
	AVStream *pStream = NULL;

	int numBytes;
	uint8_t *buffer = NULL;
	AVDictionary *optionsDict = NULL;
	AVFormatContext *pFormatCtx = NULL;
	AVCodecContext *pCodecCtx = NULL;
	int videoStream;
	struct SwsContext *sws_ctx = NULL;
	AVFrame *pFrameRGB = NULL;
	int ret;
	int fps;
	AVPacket packet;
	struct timespec time_begin, time_end;
	unsigned int count = 0;
	char filenamebuf[256] = { 0x0 };

	sprintf(filenamebuf, "%lu.h264", pthread_self());
	av_dict_set(&optionsDict, "pixel_format", "rgb24", 0);
	//av_dict_set(&optionsDict, "codec", AV_CODEC_ID_RAWVIDEO, 0);
	//av_dict_set(&optionsDict, "rtsp_transport", "tcp", 0);
	//DBG("1filenamebuf = %s.",filenamebuf);
	// Open video file
	if (avformat_open_input(&pFormatCtx, (char *) lpParam, NULL, &optionsDict) != 0)
		return NULL; // Couldn't open file

	// Retrieve stream information
	if (avformat_find_stream_info(pFormatCtx, NULL) < 0)
		return NULL; // Couldn't find stream information

	// Dump information about file onto standard error
	av_dump_format(pFormatCtx, 0, (char *) lpParam, 0);

	// Find the first video stream
	videoStream = av_find_best_stream(pFormatCtx, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0);
#if 0
	videoStream = -1;
	for(i = 0; i < (pFormatCtx)->nb_streams; i++)
	{
		if((pFormatCtx)->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
		{
			videoStream = i;
			break;
		}
	}
	//DBG("5filenamebuf = %s.",filenamebuf);
#endif
	//DBG("pFormatCtx->nb_streams = %d",(pFormatCtx)->nb_streams);
	DBG("videoStream = %d", videoStream);
	if (videoStream == -1)
		return NULL; // Didn't find a video stream
	// Get a pointer to the codec context for the video stream
	pStream = (pFormatCtx)->streams[videoStream];
	fps = pStream->avg_frame_rate.num / pStream->avg_frame_rate.den;
	DBG("[info]pStream->avg_frame_rate.num = %d", pStream->avg_frame_rate.num);
	DBG("[info]pStream->avg_frame_rate.den = %d", pStream->avg_frame_rate.den);
	DBG("7filenamebuf = %s.", filenamebuf);
	pCodecCtx = (pFormatCtx)->streams[videoStream]->codec;
	DBG("8filenamebuf = %s.", filenamebuf);
	// Find the decoder for the video stream
	pCodec = avcodec_find_decoder((pCodecCtx)->codec_id);
	if (pCodec == NULL) {
		ERR("Unsupported codec!");
		return NULL; // Codec not found
	}

	DBG("9filenamebuf = %s.", filenamebuf);
	// Open codec
	if (avcodec_open2(pCodecCtx, pCodec, &optionsDict) < 0)
		return NULL; // Could not open codec

	DBG("10filenamebuf = %s.", filenamebuf);
	DBG("[info]pCodecCtx->pix_fmt = %d", (pCodecCtx)->pix_fmt);

	// Allocate an AVFrame structure
	pFrameRGB = av_frame_alloc();
	if (pFrameRGB == NULL)
		return NULL;
	DBG("11filenamebuf = %s.", filenamebuf);
	// Determine required buffer size and allocate buffer
	numBytes = avpicture_get_size(AV_PIX_FMT_BGR24, (pCodecCtx)->width, (pCodecCtx)->height);
	DBG("12filenamebuf = %s.", filenamebuf);
	DBG("numBytes = %d.", numBytes);
	buffer = (uint8_t *) av_malloc(numBytes * sizeof(uint8_t));
#if 1
	sws_ctx = sws_getContext((pCodecCtx)->width, (pCodecCtx)->height, (pCodecCtx)->pix_fmt, (pCodecCtx)->width, (pCodecCtx)->height, AV_PIX_FMT_BGR24,
	SWS_BICUBIC,
	NULL,
	NULL,
	NULL);
#endif

#if 1
	// Assign appropriate parts of buffer to image planes in pFrameRGB
	// Note that pFrameRGB is an AVFrame, but AVFrame is a superset
	// of AVPicture
	// AV_PIX_FMT_BGR24
	avpicture_fill((AVPicture *) (pFrameRGB), buffer, AV_PIX_FMT_BGR24, (pCodecCtx)->width, (pCodecCtx)->height);
	av_freep(buffer);
#endif

	while (1) {
		av_init_packet(&packet);
		DBG("16filenamebuf = %s.", filenamebuf);
		//DBG("pFormatCtx->nb_streams = %d",(pFormatCtx)->nb_streams);
		ret = av_read_frame(pFormatCtx, &packet);
		if (ret < 0) {
			ERR("av_read_frame error.");
			return NULL;
		}
		//*tmppacket = av_packet_clone(&packet);
		DBG("15filenamebuf = %s.", filenamebuf);
		if (packet.flags & AV_PKT_FLAG_KEY) {
			DBG("pthread:%lu-帧个数:count = %u.", pthread_self(), count);
			count = 0;
		} else {
			count++;
		}

		//clock_gettime(CLOCK_REALTIME,&time_begin);
		FILE *fp = fopen(filenamebuf, "ab+");
		if (fp) {
			fwrite(packet.data, sizeof(char), packet.size, fp);
			fclose(fp);
		}
		//clock_gettime(CLOCK_REALTIME,&time_end);
		//DBG("overtime:%ld",time_end.tv_sec*1000000 + time_end.tv_nsec/1000 - time_begin.tv_sec*1000000 - time_begin.tv_nsec/1000);

#if 1
		clock_gettime(CLOCK_REALTIME, &time_begin);
		ret = ffmpeg_decode_video(pCodecCtx, sws_ctx, &packet, videoStream, pFrameRGB);
		clock_gettime(CLOCK_REALTIME, &time_end);

		//DBG("begin time:%ld-%ld",time_begin.tv_sec,time_begin.tv_nsec);
		//DBG("end time:%ld-%ld",time_end.tv_sec,time_end.tv_nsec);
		//DBG("overtime:%ld",time_end.tv_sec*1000000 + time_end.tv_nsec/1000 - time_begin.tv_sec*1000000 - time_begin.tv_nsec/1000);
#endif
		av_packet_unref(&packet);
		av_free_packet(&packet);
	}

	return 0;
}

void create_ffmpeg_thread(pthread_t *thread_id, char *param) {
	//pthread_create(thread_id, NULL, &ffmpeg_get_video_direct, (void*)(param));
	pthread_create(thread_id, NULL, &ffmpeg_get_video, (void*) (param));
}
