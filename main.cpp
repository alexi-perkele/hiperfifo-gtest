#include <iostream>
#include <fstream>
#include "gtest/gtest.h"
#include <unistd.h>
#include <sys/select.h>
#include <boost/iostreams/device/file_descriptor.hpp>
#include <boost/iostreams/stream.hpp>
#include "hfifo.h"

using namespace std;
namespace io = boost::iostreams;

int main() {
    
    
   int k;

    hfifo hiper_fifo;
    hiper_fifo.run();
    
    fstream hpipe("hiper.fifo", ios::out | ios::app);


    io::stream_buffer<io::file_descriptor_source> fpstream(
            io::file_descriptor_source(hiper_fifo.pipeFd()[0], io::never_close_handle) );

    std::istream in(&fpstream);
    std::string line;


    if( hpipe.good()){
      hpipe << "ya.ru" << endl;
    }
    else {cout << "smthg wrong " << endl;}

    while (in)
    {

        std::getline(in, line);
        cout << "piped out!!! " << line.length() << endl;
    //    std::cout << line << std::endl;
    }

    cin >> k;
 
    return 0;
}