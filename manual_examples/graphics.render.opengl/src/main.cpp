// std
#include <iostream>
// 3rd party
#include <boost/exception/all.hpp>
// project
#include "examples.hpp"


int main(int argc, char* argv[])
{  
    try
    {
        example_triangle(argc, argv);
    }
    catch(boost::exception& e)
    {
        std::cerr << boost::diagnostic_information(e);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}