/**********************************************************************

  utils.h - online judge system

  $Author$
  created at: Fri Jul 11 23:07:50 JST 2014

  Copyright (C) 2014-2015 Ryo Matsumoto

**********************************************************************/

#ifndef __UTILS_H__
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>


typedef struct{
    int debug;
    unsigned short int port;
}jj_options;

void starting_message(jj_options *opt);
void analyze_args(int argc, char* argv[], jj_options *opt);
int become_daemon();


#endif /* __UTILS_H__ */
