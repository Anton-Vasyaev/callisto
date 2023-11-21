// std
#include <iostream>
// 3rd party
#include <boost/exception/all.hpp>
// project
#include "examples.hpp"
#include <callisto/framework/app/application_environment.hpp>

namespace c_f = callisto::framework;

int main(int argc, char* argv[])
{
    c_f::application_environment::exception_location_flag = true;
    c_f::application_environment::exception_trace_flag    = true;

    try
    {
        example_triangle(argc, argv);
    }
    catch (boost::exception& e)
    {
        std::cerr << boost::diagnostic_information(e);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}