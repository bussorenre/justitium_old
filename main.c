/**********************************************************************

  main.c - online judge system

  $Author$
  created at: Tue Jul  8 11:58:53 JST 2014

  Copyright (C) 2014-2015 Ryo Matsumoto

**********************************************************************/

#include "justitium.h"

int main(int argc, char *argv[])
{
    char *filename = "test/test.c";
    char strBuf[1024];
    int retcode=0;
    pid_t pid=0;
    int status;
    FILE *fp;


    char c;
    /* Command Line option jobs */
    while((c = getopt(argc, argv, "hv")) != 1){
        switch(c){
            case 'h':
                printf("we have no help now \n");
                exit(1);
            case 'v':
                printf("justitium 0.0.1 (2014-07-13)\n");   
                exit(1);
        }
    }



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

