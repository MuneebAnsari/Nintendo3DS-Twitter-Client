#include <3ds.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include <errno.h>
#include <stdarg.h>
#include <unistd.h>

#include <fcntl.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <citro2d.h>
#include <curl/curl.h>
#include <json-c/json.h>

#include "socket_service.h"
#include "http_client.h"
#include "twitter_data_service.h"
#include "json_parser.h"
#include "tweet_graphic.h"
#include "models.h"
#include "timeline.h"

#define SOC_ALIGN 0x1000
#define SOC_BUFFERSIZE 0x100000

void addTweet(Tweet **tweetLstPtr, char *text, int favCount);

void addTweet(Tweet **tweetLstPtr, char *text, int favCount)
{
	Tweet *new_tweet = (Tweet *)malloc(sizeof(Tweet));
	new_tweet->prev = NULL;
	new_tweet->next = NULL;
	new_tweet->text = (char *)malloc(strlen(text) + 1);
	strcpy(new_tweet->text, text);
	new_tweet->favCount = favCount;

	Tweet *last = *tweetLstPtr;

	// new tweet is the first tweet
	if (*tweetLstPtr == NULL)
	{
		new_tweet->prev = NULL;
		*tweetLstPtr = new_tweet;
	}
	else
	{
		// preserve tweet order on insert
		while (last->next != NULL)
		{
			last = last->next;
		}

		last->next = new_tweet;
		new_tweet->prev = last;
	}
}

int main()
{

	gfxInitDefault();

	// initialize citro2d w/ default buf size
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();

	consoleInit(GFX_BOTTOM, NULL);
	// create render target (top left screen)
	C3D_RenderTarget *top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
	C2D_TargetClear(top, C2D_Color32(0x00, 0xAC, 0xEE, 0xFF));

	/* 
	 * Initialize 3DS SOCKET SERVICE before using libcurl 
	 * reference: https://devkitpro.org/viewtopic.php?t=9020&p=16703
	*/
	static u32 *socCtxt = NULL;
	SocketService ss = SocketService(socCtxt, SOC_ALIGN, SOC_BUFFERSIZE);
	ss.init();

	/*
	 * Initialize 3DS read only filesystem (romfs)
	 * reference: https://www.3dbrew.org/wiki/RomFS
	*/
	Result romfsRes = romfsInit();
	if (romfsRes != 0)
	{
		printf("romfsInit: %08lX\n", romfsRes);
	}

	printf("\nTWITTER ON 3DS\n");

	/*
	 * Initialize HttpClient - uses libcurl to make HTTP requests
	 * reference: https://curl.haxx.se/libcurl/c/example.html
	 * 
	 * Initialize TwitterDataService - DAO to communicate with API Gateway 
	 * to (api.twitter.com).
	*/
	HttpClient httpClient;
	TwitterDataService tds = TwitterDataService(httpClient);
	Response userTweets = tds.getUserTweets((char *)"123");

	// printf("MAIN Data: %s\n", userTweets.data);
	printf("MAIN Size: %lu bytes retrieved\n", (unsigned long)userTweets.size);

	JsonParser jp;
	json_object *jsonUserTweets = (json_object *)json_tokener_parse(userTweets.data);
	int n_userTweets = json_object_array_length(jsonUserTweets);

	Tweet *head;
	jp.parseTweetObj(jsonUserTweets, n_userTweets, &head, addTweet);

	Tweet *last = head->prev;

	float xs = 20;
	float ys = 20;
	float screenSpace = GSP_SCREEN_HEIGHT_TOP;
	int pageNum = 1;
	int numTweetsOnPage = 0;

	// Main loop
	while (aptMainLoop())
	{
		gspWaitForVBlank();
		hidScanInput();
		u32 kDown = hidKeysDown();
		if (kDown & KEY_START)
			break; // break in order to return to hbmenu

		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_SceneBegin(top);

		// -- Scene --

		while (head != NULL)
		{
			TweetGraphic currTweetGraphic = TweetGraphic(head->text, xs, ys);

			if (screenSpace > 0)
			{
				currTweetGraphic.draw();
				numTweetsOnPage++;
				ys = ys + currTweetGraphic.getHeight() + 10;
				screenSpace -= ys;
				last = head;
				head = head->next;
			}
			else
			{
				break;
			}
		}

		if (screenSpace <= 0 && (kDown & KEY_DOWN) && head != NULL)
		{
			pageNum++;
			C3D_FrameEnd(0);
			C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
			// clear screen contents
			C2D_TargetClear(top, C2D_Color32(0x00, 0xAC, 0xEE, 0xFF));
			C2D_SceneBegin(top);
			// reset screen space
			screenSpace = GSP_SCREEN_HEIGHT_TOP;
			// reset tweet start position to top
			xs = 20;
			ys = 20;
			numTweetsOnPage = 0;
		}

		if ((kDown & KEY_UP) && pageNum > 1)
		{
			// tl.scrollUp();
			pageNum--;

			C3D_FrameEnd(0);
			C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
			// clear screen contents
			C2D_TargetClear(top, C2D_Color32(0x00, 0xAC, 0xEE, 0xFF));
			C2D_SceneBegin(top);
			// reset screen space
			screenSpace = GSP_SCREEN_HEIGHT_TOP;
			// reset tweet start position to top
			xs = 20;
			ys = 20;
			int i = 0;
			while ((i < numTweetsOnPage + 1) && last != NULL)
			{
				i++;
				last = last->prev;
			}
			head = last->prev;
			numTweetsOnPage = 0;
		}

		C3D_FrameEnd(0);
	}

	// Exit services

	// free tweets
	Tweet *tweetToFree;
	while (head != NULL)
	{
		tweetToFree = head;
		head = head->next;
		free(tweetToFree);
	}
	ss.shutdown();
	C2D_Fini();
	C3D_Fini();
	gfxExit();
	return 0;
}
