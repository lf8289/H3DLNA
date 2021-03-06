#ifndef _CRENDERER_H
#define _CRENDERER_H

#include <iostream>
#include <sys/types.h>
#include <sys/param.h>
#include <sys/wait.h>
#include <errno.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/wait.h>
#include <string.h>

#define DEBUG
//#define DEFAULT_WEB_DIR "/etc/renderer"
#define DESC_URL_SIZE 200
#define	DUP2CLOSE(oldfd, newfd)	(dup2(oldfd, newfd) == 0  &&  close(oldfd) == 0)

#define	DATABUFSIZE	4096	/* the length of the buffer read in "fd" */
#define CMDBUFSIZE 4096

using namespace std;

typedef struct
{
        char buf[DATABUFSIZE];	/* buffer */
        int pos;	/*the pointer of read positon */
        int size;	/* the length of the buffer */
} DATABUF_TYPE;




enum
{
	STOP,
	PLAY,
	PAUSE
};


class cRenderer {
private:

	char* web_root;
	enum {
		ConnectionManager,
		AVTransport,
		RenderingControl
	};


	// thread
	pthread_t thread;
	int iret;
	#define	PARENT_READ	readpipe[0]
	#define	CHILD_WRITE	readpipe[1]
	#define CHILD_READ	writepipe[0]
	#define PARENT_WRITE	writepipe[1]
	FILE* readfp;
	

	//pipe file
	int	writepipe[2],	/* parent -> child */
		readpipe [2],	/* child -> parent */
		errpipe[2];
	pid_t childpid;


	
public:
	
    // global variables
	char* udn;
	char friendlyName[100];
	char xmlIcon[100];
	char *ip_addr;
	char *mplayer_bin;
    char* fullscreen;

    int registerfd;


	cRenderer();
	~cRenderer();
	void initVar();
	//int mypopen(char* uri);
	int mypopen();
	static void* threadCreate( void *ptr );

	char* mplayer_cmd(int commandtype,int param1,int param2,bool output);
	//void mplayer_start( char * p);
	int mplayer_start();
	string showOutput(int type);
	void mplayer_loadfile(char *fileaddr,int loadandplay);
	

	bool mplayer_is_running;
	int positionToSeek;
	int speed;
	int playstatus;
	

	void routon_get_scrub(float * duration,float *position ); 
	int routon_is_playing() ; //播放器是否正在播放 非暂停状态  
	void routon_set_scrub(int position); //seek至指定位置
	int routon_is_seekable();//是否可以seek
	void routon_pause();
	void routon_stop();
	void routon_play();
	void routon_add_to_playlist(char *location,int addorplay); //添加到播放列表并开始缓冲
	int routon_mplayer_is_running();//mplayer是否已经启动
	int routon_mplayer_start();


};



#endif /* _CRENDERER_H */


