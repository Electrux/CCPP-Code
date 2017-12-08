#ifndef EXECUTECOMMAND_HPP
#define EXECUTECOMMAND_HPP

#include <vector>
#include <string>

#include "CompileCommandData.hpp"

int ExecuteCommand( std::string command );

void DisplayBuildResults( CCData & commands, int res, int percent );

int ExecuteAllCommands( std::vector< CCData > & commands, int count );

#endif // EXECUTECOMMAND_HPP
