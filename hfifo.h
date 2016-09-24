#ifndef HFIFO_H
#define HFIFO_H

class hfifo {
public:  
  hfifo();
  void run();
  const int* pipeFd() const;
  ~hfifo();
  
private: 
  bool _running;
  pid_t _pid;
  int _status;
  
  enum FILE_DESCRIPTORS {
    READ_FD = 0,
    WRITE_FD = 1
  };
  
  int childToParent[2];
  
  // No implimintation for this:
  hfifo (const hfifo&);
  hfifo& operator = (const hfifo&);
  
};



#endif