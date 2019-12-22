/**
 * \file Args.hpp
 * @author Electrux Redsworth (ElectruxRedsworth@gmail.com)
 * \date 2019-12-20
 * 
 * @copyright Copyright (c) 2019, all rights reserved.<br/>
 * This project uses the BSD 3-clause license,<br/>
 * attached in the project root directory.<br/>
 * 
 */

#ifndef ARGS_HPP
#define ARGS_HPP

#include <cstdlib>
#include <vector>
#include <string>

// Option bit masks
extern const size_t OPT_A;
extern const size_t OPT_B; // show byte code
extern const size_t OPT_C; // (byte) compile
extern const size_t OPT_D; // dry run (no execute)
extern const size_t OPT_E; // REPL (eval)
extern const size_t OPT_F;
extern const size_t OPT_G;
extern const size_t OPT_H;
extern const size_t OPT_I;
extern const size_t OPT_L;
extern const size_t OPT_P; // show parse tree
extern const size_t OPT_R;
extern const size_t OPT_S;
extern const size_t OPT_T; // show tokens
extern const size_t OPT_V; // show version

namespace args
{
/**
 * \brief Parses command line arguments
 * 
 * \param argc Command ling argument count
 * \param argv Command ling argument value
 * \param args Arguments found after source file, including it, which will be the first non-dash-beginning argument
 * \return size_t A bitmask value, set for all found options in argv
 */
size_t get( const int argc, const char ** argv, std::vector< std::string > & args );
}

#endif // ARGS_HPP
