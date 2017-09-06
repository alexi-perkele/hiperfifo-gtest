#include "hfifo_test.hpp"


HfifoTest::HfifoTest() {}


void HfifoTest::init()
{
    hiper_fifo_.reset(new Hfifo());
    
    hiper_fifo_->run();
    
    hpipe_ = std::fstream("hiper.fifo", std::ios::out);

}

HfifoTest::HyperMap HfifoTest::run_test(const std::string& url)
{
    io::stream_buffer<io::file_descriptor_source> fpstream (
        io::file_descriptor_source ( hiper_fifo_->pipeFd ( STDERR_FILENO ) [0], io::close_handle ) );

    std::istream in ( &fpstream );
    std::fstream hpipe("hiper.fifo", std::ios::out);
    std::string input_line;
    if ( hpipe.good() )
        {
        hpipe << url << std::endl;
        sleep ( 1 ); // make sure all data pulled
        }
    else
        {
        std::cout << "smthg wrong " << std::endl;
        }
    do
        {
        getline ( in, input_line );
        if (input_line.length() < 4) continue; // suppose to be empty
        std::cout << input_line << std::endl;
        fifo_input_.push_back(input_line);
        }
    while ( fpstream.in_avail() );
 
    process_data(fifo_input_);
        
    return results_;
}

void HfifoTest::process_data(const std::vector<std::string>& data)
{
    for(auto s: fifo_input_ ) 
    {
         boost::trim_left_if(s,boost::is_any_of("< "));
         boost::trim_left_if(s,boost::is_any_of("* "));
         boost::trim(s);
         
         std::size_t pos = s.find(" ");   
         if (pos >= s.length()) continue;
         
         std::string token1 = s.substr(0,pos);
         std::string token2 = s.substr(pos+1);
         boost::trim(token2);
         boost::trim_right_if(token1,boost::is_any_of(":"));
         boost::to_upper(token1);
         
         results_.insert( HyperMap::value_type(token1, token2));
    }
}


HfifoTest::~HfifoTest()
{
}

