#include <iostream>
#include <fstream>
#pragma once
#include <boost/iostreams/device/file_descriptor.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/stream_buffer.hpp>
#include <boost/algorithm/string.hpp>
#include <memory>
#include <vector>
#include <unordered_map>
#include "hfifo.hpp"


namespace io = boost::iostreams;


class HfifoTest
{
public:

using HyperMap = std::unordered_map<std::string, std::string>;

    HfifoTest();
    void init();
    HyperMap run_test(const std::string& url);
    void process_data(const std::vector<std::string>& data);
    ~HfifoTest();
    
private:
    std::unique_ptr<Hfifo> hiper_fifo_;
    std::fstream hpipe_;
    std::vector<std::string> fifo_input_;
    HyperMap results_;

};
