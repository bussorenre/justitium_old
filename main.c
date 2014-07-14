/**********************************************************************

  main.c - online judge system

  $Author$
  created at: Tue Jul  8 11:58:53 JST 2014

  Copyright (C) 2014-2015 Ryo Matsumoto

**********************************************************************/

#include "justitium.h"

int main(int argc, char *argv[])
{
    jj_options opt;
    
    /* 設定ファイルの読み込み */
    opt.port = 10000;
    opt.debug = 0;

    /* parsing commandline arguments. */
    analyze_args(argc, argv, &opt);

    /* starting_server */
    starting_message(&opt);
    server_main(&opt);

    return 0;
}

