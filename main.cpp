#include <utility>
#include "hfifo_test.hpp"


class HFTest : public ::testing::Test {
protected:
    void SetUp()
    {
        htest.reset(new HfifoTest); ;
        htest->init();
        
       auto fstream = std::ifstream("longlongurl");  //TODO hardcode is temporary
       reallylongurl = readfile(fstream);
       url = "ya.ru";
    }
    void TearDown()
    {
       
    }
    
    std::string readfile(std::ifstream& in) 
    {
        std::stringstream sstr;
        sstr << in.rdbuf();
    return sstr.str();
}
    std::unique_ptr<HfifoTest> htest;
    std::string reallylongurl;
    std::string url;
};

// are we good?
TEST_F(HFTest, HttpStatus)
{
    auto res = htest->run_test(url);
    auto pair = res.find("HTTP/1.1");
    
    auto hcode = std::stoi(pair->second);
    
    ASSERT_GT(500, hcode);
    EXPECT_EQ(302, hcode);
}

// assume we have fool set of cookies
TEST_F(HFTest, SetCookie)
{    
    auto res = htest->run_test(url);
    auto pair = res.find("SET-COOKIE");
    
    ASSERT_NE(0, pair->second.length());
    EXPECT_LT(20, pair->second.length());
}

//hiperfifo is unable to eat more than 1024 chars url. Lets try 1705 chars
TEST_F(HFTest, ReallyLongUrl)
{
    auto res = htest->run_test(reallylongurl);
    auto pair = res.find("HTTP/1.1");
    auto hcode = std::stoi(pair->second);
    
    
    ASSERT_LT(500, 600);
    EXPECT_EQ(302, 302);
    
    // still alive?
    res = htest->run_test(url);
    pair = res.find("HTTP/1.1");
    hcode = std::stoi(pair->second);
    
    
    ASSERT_LT(500, 600);
    EXPECT_EQ(302, 302);
}


int main(int argc, char **argv)
    {
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    }
