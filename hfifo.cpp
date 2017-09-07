#include "hfifo.hpp"


Hfifo::Hfifo() : _running ( false ), _pid ( -1 ), _status ( false )
    {
    }

void Hfifo::run()
    {

    pipe ( stdout_procfd );
    pipe ( stderr_procfd );

    _pid = fork();

    if ( _pid == 0 )
        {
        // Child
        dup2 ( stdout_procfd[ WRITE_FD ], STDOUT_FILENO );
        dup2 ( stderr_procfd[ WRITE_FD ], STDERR_FILENO );

        execl ( "hiperfifo/hiperfifo", "hiperfifo", NULL ); //TODO bring to to program parameters

        close ( stdout_procfd [ READ_FD  ] );
        close ( stdout_procfd [ WRITE_FD  ] ); //   try to be quiet
        close ( stderr_procfd [ WRITE_FD ] ); // 
        close ( stderr_procfd [ READ_FD  ] );
        }
    else if ( _pid > 0 )
        {
        // Parent
        _running = true;

        close ( stdout_procfd[ WRITE_FD ] );
        close ( stderr_procfd[ WRITE_FD ] );

        sleep ( 1 ); // let child create pipe
        }
    else
        {
        perror("cant fork");
        exit ( 1 );
        }

    }

const int* Hfifo::pipeFd ( const int fd ) const
    {
    switch ( fd )
        {
        case STDOUT_FILENO:
            return stdout_procfd;
        case STDERR_FILENO:
            return stderr_procfd;
        default:
            return stderr_procfd;
        }

    }
    

Hfifo::~Hfifo()
    {
    if ( _running && _pid!=0 )
        {
        kill ( _pid, SIGINT );
        }
    }
