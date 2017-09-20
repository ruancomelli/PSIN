#ifndef PROGRAM_OPTIONS_HPP
#define PROGRAM_OPTIONS_HPP

#include <boost/program_options.hpp>

namespace psin {

namespace program_options = boost::program_options;

program_options::variables_map parseCommandLine(int argc, char * argv[], program_options::options_description & options);

} // psin

#endif //PROGRAM_OPTIONS_HPP
