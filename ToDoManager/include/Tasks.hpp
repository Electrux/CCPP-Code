#ifndef TASKS_HPP
#define TASKS_HPP

#include <string>
#include <vector>
#include <fstream>

class Tasks
{
	std::vector< std::string > tasks;

	std::string _filename;

public:
	Tasks( std::string _filename );

	bool NewTask( std::string & task );

	bool DeleteTask( int taskid );

	bool ChangeTask( int taskid, std::string & newtask, std::string & oldtask );

	std::string GetTask( int taskid );

	void ShowTasks();

	bool IsValidTask( int taskid );

	bool IsFileOpen();

	bool UpdateFile();

	size_t CountTasks();
};

#endif // TASKS_HPP
