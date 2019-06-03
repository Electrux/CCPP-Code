#ifndef ARGS_HPP
#define ARGS_HPP

#include <vector>
#include <string>
#include <unordered_map>

typedef std::unordered_map< std::string, std::string > OptMap;
typedef std::vector< std::string > ArgVec;

class CmdParams
{
	OptMap m_opts;
	ArgVec m_args;

	void ParseDoubleDashArg( const std::string & arg, bool & options_stopped );
	void ParseSingleDashArg( const std::string & arg );
public:
	void Parse( const ArgVec & args );
	const ArgVec & Args() const;
	const OptMap & Opts() const;
	std::string Opt( const std::string & key ) const;

#ifdef __DEBUG
	void DispAll() const;
#endif
};

#endif // ARGS_HPP