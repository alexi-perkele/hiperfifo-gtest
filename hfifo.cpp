#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <iostream>
#include <fstream>
#include "hfifo.h"



hfifo::hfifo() : _running(false), _pid(-1), _status(1)
{

}

void hfifo::run()
{

  std::cout << "RUN" << std::endl;
    
    pipe(childToParent);
  //  dup2( childToParent[ WRITE_FD ], STDOUT_FILENO );
    dup2( childToParent[ WRITE_FD ], STDERR_FILENO );
    
    _pid = fork();
    
    if (_pid == 0){
      // Child
     std::cout << "will exec" << std::endl;
      execl("hiperfifo/hiperfifo", " ", NULL);  
      close( childToParent [ READ_FD  ] );
    }
    else if (_pid > 0)
    {
      // Parent
      _running = true;
     
      close( childToParent [ WRITE_FD ] );
      
      sleep(1); // let child create pipe
    }
    else {
      std::cout << "Can't fork " << std::endl;
      exit(1);
    }
  
}

const int* hfifo::pipeFd() const
{

}

hfifo::~hfifo()
{
    if(_running){
      kill(_pid, SIGINT);
    }
}
