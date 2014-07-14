/**********************************************************************

  utils.h - online judge system

  $Author$
  created at: Fri Jul 11 23:07:50 JST 2014

  Copyright (C) 2014-2015 Ryo Matsumoto

**********************************************************************/

#include "utils.h"
#include "time.h"

void starting_message(jj_options *opt)
{
    time_t timer;
    timer = time(NULL);
    printf("starting justitium server...\n");
    printf("time\t : %s",ctime(&timer));
    printf("url\t : 127.0.0.1:%d\n",opt->port);
    printf("justitium server is alive now!\n"
           "If you want to end this process, use kill command\n");
    return;
}


void analyze_args(int argc, char* argv[], jj_options *opt)
{
    char c;

    /* Command Line option jobs */
    while((c = getopt(argc, argv, "dhvp:")) != -1){
        switch(c){
            case 'd':
                opt->debug = 1;
                break;
            case 'h':
                printf("we have no help now \n");
                exit(1);
            case 'v':
                printf("justitium 0.0.1 (2014-07-13)\n");   
                exit(1);
            case 'p':
                opt->port = atoi(optarg);
                break;
            default:
                break;
        }
    }

    return;
}


int become_daemon()
{
    return daemon(0,0);
}
