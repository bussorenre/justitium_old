/**********************************************************************

  main.c - online judge system

  $Author$
  created at: Tue Jul  8 11:58:53 JST 2014

  Copyright (C) 2014-2015 Ryo Matsumoto

**********************************************************************/

#include "justitium.h"

int main(int argc, char const *argv[])
{
    // とりあえず、ローカルのhello worold をコンパイルさせて動かす。
    char *filename = "test/test.c";
    char strBuf[1024];
    int retcode=0;
    pid_t pid=0;
    int status;
    FILE *fp;

    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        perror(NULL);
        exit(1);
    }

    retcode = system("gcc -o tmp test/test.c");
    if(retcode != 0)
    {
        exit(1);
    }


    /* 肝はここから。ulimitによってメモリや実行速度が適切に制限されているか。 */ 
    switch(pid=fork()) {
        case 0: /* child process */
            getcwd(strBuf, 1024);
            strcat(strBuf, "/tmp");
            execl(strBuf, "tmp", NULL);
            perror(NULL);
            break;
        case -1:
            perror(NULL);
            break;
        default:
            printf("pid = %d\n",pid);
            break;
    }
    waitpid(pid, &status, 0);

    return 0;
}

