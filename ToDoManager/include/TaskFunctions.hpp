#ifndef TASKFUNCTIONS_HPP
#define TASKFUNCTIONS_HPP

#include <vector>
#include <string>

bool inserttask( std::vector< std::string > & args );

bool altertask( std::vector< std::string > & args );

bool deletetask( std::vector< std::string > & args );

void showtasks();

void HelpFunction();

#endif // TASKFUNCTIONS_HPP
