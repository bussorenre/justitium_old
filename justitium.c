/**********************************************************************

  justitum.c - online judge system justitium

  $Author$
  created at: Fri Jul 11 23:02:21 JST 2014

  Copyright (C) 2014-2015 Ryo Matsumoto

**********************************************************************/

#include "justitium.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <semaphore.h>
#include <pthread.h>


typedef struct _judge_request{
    struct sockaddr_in addr;
    int s;
    socklen_t addrsize;
    pthread_t thid;
}judge_request;

void *judge_thread_func(void *param);

int server_main(jj_options *opt)
{
    int max_clients = 40;       // ベトナム実験用に40は耐えて欲しい
    int i=0, num_clients=0;
    int listen_s, s;
    judge_request *jr;
    struct sockaddr_in addr;

    /* initialize listen port */
    jr = (judge_request *)malloc(sizeof(judge_request) * max_clients);

    memset(jr, 0, sizeof(judge_request) * max_clients);
    memset(&addr, 0, sizeof(struct sockaddr_in));
    addr.sin_port = htons(opt->port);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    listen_s = socket(AF_INET, SOCK_STREAM, 0);
    bind(listen_s, (struct sockaddr*) &addr, sizeof(struct sockaddr_in));
    listen(listen_s, 5);

    /* listenning loop */
    do
    {
        if (num_clients==max_clients)
            continue;

        for (i = 0; i < max_clients; i++)
        {
            if (jr[i].s == 0)
            {
                break;
            }
        }
        jr[i].addrsize = sizeof(struct sockaddr_in);
        jr[i].s = accept(listen_s, (struct sockaddr *) &jr[i].addr, &jr[i].addrsize);
//        num_clients++;
//        num_clients--;

        if (pthread_create(&jr[i].thid, NULL, judge_thread_func, (void*)&jr[i]) != 0)
        {
            perror(NULL);
            exit(1);
        }
 //       pthread_join(&jr[i].thid, NULL);

    } while (1);

    close(listen_s);
    free(jr);
    return 0;
}




void *judge_thread_func(void *param)
{
    char filename[NAME_MAX] = {0};
    char currentPath[PATH_MAX] = {0};
    char command[_POSIX_ARG_MAX] = {0};
    char gcc[] = "gcc -o a.out ";
    int retcode = 0;
    pid_t pid = 0;
    int status;
    judge_request *request;

    /* accepting connect */
    request = (judge_request*)param;
    read(request->s, filename, NAME_MAX-1);

    printf("accepted connection from %s, port=%d\n"
           "requested filename is \"%s\"\n",
           inet_ntoa(request->addr.sin_addr), ntohs(request->addr.sin_port),filename);


    
    /* complie */
    strcat(command, gcc);
    strcat(command, filename);
    retcode = system(command);
    if(retcode != 0)
    {
        perror(NULL);
        exit(1);
    }

    getcwd(currentPath, PATH_MAX);
    strcat(currentPath, "/a.out");

    /* 肝はここから。ulimitによってメモリや実行速度が適切に制限されているか。 */ 
    switch(pid=fork()) {
        case 0: /* child process */
            execl(currentPath, "a.out", NULL);
            perror(NULL);
            break;
        case -1:
            perror(NULL);
            break;
        default:
            break;
    }

    waitpid(pid, &status, 0);
    printf("pid = %d, status = %d\n", pid, status);


    write(request->s, (const void *)"AC\n", 4);
    close(request->s);
    request->s = 0;

    return NULL;
}

