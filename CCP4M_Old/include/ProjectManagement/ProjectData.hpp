#ifndef PROJECTDATA_HPP
#define PROJECTDATA_HPP

#include <vector>
#include <string>

struct ProjectData
{
	std::string name;
	std::vector< std::string > deps;
	std::string dir;
};

const std::string DEFAULTMAIN =
	"#include <iostream>\n"
	"\n"
	"int main()\n"
	"{\n"
	"\treturn 0;\n"
	"}\n";

ProjectData GetProjectData( std::vector< std::string > & args );

#endif // PROJECTDATA_HPP
