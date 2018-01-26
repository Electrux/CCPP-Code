#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "../include/Tasks.hpp"
#include "../include/StringFuncs.hpp"

Tasks::Tasks( std::string _filename )
{
	this->_filename = _filename;

	std::fstream file;

	file.open( _filename, std::ios::in );

	if( !file ) {

		file.open( _filename, std::ios::out );
		if( !file ) {
			std::cerr << "Could not create/open file." << std::endl;
			return;
		}
		file.close();
		return;
	}

	std::string line;
	while( std::getline( file, line ) ) {

		Trim( line );
		tasks.push_back( line );
	}

	file.close();
}

bool Tasks::NewTask( std::string & task )
{
	if( !Trim( task ) )
		return false;

	tasks.push_back( task );

	return UpdateFile();
}

bool Tasks::DeleteTask( int taskid )
{
	if( !IsValidTask( taskid ) )
		return false;

	taskid--;

	int ctr = 0;
	for( auto it = tasks.begin(); it != tasks.end(); ++it ) {

		if( ctr == taskid ) {

			tasks.erase( it );
			break;
		}
		ctr++;
	}

	return UpdateFile();
}

bool Tasks::ChangeTask( int taskid, std::string & newtask, std::string & oldtask )
{
	if( !IsValidTask( taskid ) )
		return false;

	taskid--;

	oldtask = tasks[ taskid ];

	tasks[ taskid ] = newtask;

	return UpdateFile();
}

std::string Tasks::GetTask( int taskid )
{
	if( !IsValidTask( taskid ) )
		return "";

	taskid--;

	return tasks[ taskid ];
}

void Tasks::ShowTasks()
{
	if( tasks.empty() ) {

		std::cout << "You have nothing to do! Hoorraay!!" << std::endl;
		return;
	}

	std::cout << "\n\nTask ID\t\tTask\n" << std::endl;

	int ctr = 1;
	for( auto task : tasks ) {

		std::cout << ctr << "\t\t" << task << std::endl;
		ctr++;
	}

	std::cout << std::endl;
}

bool Tasks::IsValidTask( int taskid )
{
	taskid--;

	if( taskid > ( int )tasks.size() ) {

		std::cerr << "Entered task ID exceeds total tasks!" << std::endl;
		return false;
	}

	if( taskid < 0 ) {

		std::cerr << "Entered task ID is less than zero!" << std::endl;
		return false;
	}

	return true;
}

bool Tasks::UpdateFile()
{
	std::fstream file;

	file.open( _filename, std::ios::out | std::ios::trunc );
	file.close();

	file.open( _filename, std::ios::app );

	for( auto task : tasks ) {

		file << task << std::endl;
	}

	file.close();

	return true;
}

size_t Tasks::CountTasks()
{
	return tasks.size();
}
