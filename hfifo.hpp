#ifndef HFIFO_H
#define HFIFO_H

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <iostream>
#include <fstream>
#include <map>

class Hfifo
    {
    public:
        Hfifo();
        void run();
        const int* pipeFd ( const int ) const;
        ~Hfifo();

    private:
        bool _running;
        pid_t _pid;
        bool _status;

        enum FILE_DESCRIPTORS
            {
            READ_FD = 0,
            WRITE_FD = 1
            };

        int stdout_procfd[2];
        int stderr_prcofd[2];


        // No implimintation for this:
        Hfifo ( const Hfifo& );
        Hfifo& operator = ( const Hfifo& );

    };



#endif
