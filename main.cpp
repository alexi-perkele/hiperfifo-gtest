#include <gtest/gtest.h>
#include "hfifo_test.hpp"


int main(int argc, char **argv)
    {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    std::unique_ptr<HfifoTest> hypertest(new HfifoTest);
    std::string url = "ya.ru";
    
    hypertest->init();
    auto res = hypertest->run_test(url);
    
    for(auto m: res)
    {
        std::cout << "        " << m.first;
        std::cout << "        " << m.second << '\n';
    }
    std::cout << "that's it!" << std::endl;

    return 0;
    }
