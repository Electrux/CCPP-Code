#include <iostream>
#include <vector>
#include <string>

#include "../include/StringFuncs.hpp"
#include "../include/FileFunctions.hpp"
#include "../include/Tasks.hpp"
#include "../include/TaskFunctions.hpp"

bool inserttask( std::vector< std::string > & args )
{
	if( args.size() < 3 ) {
		std::cerr << "Usage: " << args[ 0 ]
			  << " do [ Task ]" << std::endl;
		return false;
	}

	std::string task = Concatenate( args, 1 );

	std::string fileloc;
	if( !GetFile( fileloc ) )
		return false;

	Tasks tasker( fileloc );

	return tasker.NewTask( task );
}

bool altertask( std::vector< std::string > & args )
{
	if( args.size() < 4 ) {
		std::cerr << "Usage: " << args[ 0 ]
			  << " alter [ Task ID ] [ Alter task to ]" << std::endl;
		return false;
	}

	int taskid = std::stoi( args[ 2 ] );

	std::string task = Concatenate( args, 2 );

	std::string fileloc;
	if( !GetFile( fileloc ) )
		return false;

	Tasks tasker( fileloc );

	std::string oldtask;

	bool res = tasker.ChangeTask( taskid, task, oldtask );

	if( res )
		std::cout << "Changed:\n\t" << oldtask
			  << "\nto:\n\t" << task << std::endl;

	return res;
}

bool deletetask( std::vector< std::string > & args )
{
	if( args.size() < 3 ) {
		std::cerr << "Usage: " << args[ 0 ]
			  << " done [ Task ID ]" << std::endl;
		return false;
	}

	int taskid = std::stoi( args[ 2 ] );

	std::string fileloc;
	if( !GetFile( fileloc ) )
		return false;

	Tasks tasker( fileloc );

	return tasker.DeleteTask( taskid );
}

void showtasks()
{
	std::string fileloc;
	if( !GetFile( fileloc ) )
		return;

	Tasks tasker( fileloc );

	tasker.ShowTasks();
}

void HelpFunction()
{
	std::cout << "Help\n" << std::endl

		  << "\tOptions:\n" << std::endl

		  << "\t\tdo [ task ]" << std::endl
		  << "\t\t\tAdd a new task to perform\n" << std::endl

		  << "\t\talter [ task id ] [ new task ]" << std::endl
		  << "\t\t\t Change the task at task id to new task\n" << std::endl

		  << "\t\tlist" << std::endl
		  << "\t\t\tShow all undone tasks and their IDs\n" << std::endl

		  << "\t\tdone [ task id ]" << std::endl
		  << "\t\t\tFinish and delete a task by its ID which is a number >= 1\n"
		  << std::endl

		  << "\t\thelp" << std::endl
		  << "\t\t\tShow this information\n" << std::endl;
}
