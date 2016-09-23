#include <iostream>
#include <fstream>
#include "gtest/gtest.h"
#include <unistd.h>
#include <sys/select.h>
#include <bitset>

using namespace std;

class hfifo {
public:
  
  hfifo() : _running(false), _pid(-1), _status(1){
    
  }  
  
  void run()
  {
    cout << "RUN" << endl;
    
    pipe(childToParent);
    dup2( childToParent[ WRITE_FD ], STDOUT_FILENO );
    dup2( childToParent[ WRITE_FD ], STDERR_FILENO );
    
    _pid = fork();
    
    if (_pid == 0){
      // Child
     cout << "will exec" << endl;
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
      cout << "Can't fork " << endl;
      exit(1);
    }
  }
  
  void stop()
  {
    cout << "now we stop" << endl;
    kill (_pid, SIGINT);
    _running = false;
  }
  
  ~hfifo(){
    cout << "Destruction time" << endl;
    if(_running){
      kill (_pid, SIGINT);
    }
  }
    
private:
  bool _running;
  pid_t _pid;
  int _status;
  
  enum FILE_DESCRIPTORS {
    READ_FD = 0,
    WRITE_FD = 1
  };
  
  int childToParent[2];
  
  hfifo (const hfifo&);
  hfifo& operator = (const hfifo&);
};

int main() {
    
    
   int k;

    hfifo hiper_fifo;
    hiper_fifo.run();
    cout << "Yarrrrrrr" << endl;
    //sleep(1);
    fstream hpipe("hiper.fifo", ios::out | ios::app);
   
    cout << "pipe alive? " << hpipe.rdstate() << endl;
    if( hpipe.good()){
      hpipe << "ya.ru" << endl;
      cout << "pipe time!" << endl;
    }
    else {cout << "smthg wrong " << endl;}
    

   
   
    cin >> k;
 
    return 0;
}