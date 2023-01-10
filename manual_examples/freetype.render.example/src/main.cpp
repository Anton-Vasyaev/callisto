// std
#include <iostream>
// 3rdparty
#include <boost/program_options.hpp>
// project
#include "examples.hpp"

namespace po = boost::program_options;

int main(int argc, char* argv[])
{
    std::string example_type;

    po::options_description desc("options");
    desc.add_options(
    )("example",
      po::value<std::string>(&example_type)->default_value("standard"),
      "type of example [standard, stroke]");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    std::cout << "example type:" << example_type << std::endl;

    call_example_standard();
}