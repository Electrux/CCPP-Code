#ifdef __DEBUG
#include <iostream>
#endif
#include <vector>
#include <string>
#include <unordered_map>

#include "Str.hpp"
#include "CmdParams.hpp"

void CmdParams::Parse( const ArgVec & args )
{
	bool options_stopped = false;
	for( auto it = args.begin(); it != args.end(); ++it ) {
		const std::string & arg = * it;

		if( arg.size() == 0 ) continue;
		if( !options_stopped && arg.size() >= 2 && arg[ 0 ] == '-' && arg[ 1 ] == '-' ) {
			ParseDoubleDashArg( arg, options_stopped );
		} else if( !options_stopped && arg[ 0 ] == '-' ) {
			ParseSingleDashArg( arg );
		} else {
			m_args.push_back( arg );
		}
	}
}

const ArgVec & CmdParams::Args() const { return m_args; }
const OptMap & CmdParams::Opts() const { return m_opts; }
std::string CmdParams::Opt( const std::string & key ) const
{
	return m_opts.find( key ) != m_opts.end() ? m_opts.at( key ) : "";
}

// Privates

void CmdParams::ParseDoubleDashArg( const std::string & arg, bool & options_stopped )
{
	auto delimvec = Str::DelimitOnce( arg, '=' );
	if( delimvec.size() < 2 ) {
		if( arg.size() == 2 ) {
			options_stopped = true;
			return;
		}
		m_opts[ arg.substr( 2 ) ] = "_";
		return;
	}
	m_opts[ delimvec[ 0 ].substr( 2 ) ] = delimvec[ 1 ];
}

void CmdParams::ParseSingleDashArg( const std::string & arg )
{
	if( arg == "-" ) return;
	auto delimvec = Str::DelimitOnce( arg, '=' );
	for( auto it = delimvec[ 0 ].begin() + 1; it != delimvec[ 0 ].end() - 1; ++it ) {
		m_opts[ std::string( 1, * it ) ] = "_";
	}
	const std::string last_ch_str = std::string( 1, delimvec[ 0 ][ arg.size() - 1 ] );
	m_opts[ last_ch_str ] = delimvec.size() > 1 ? delimvec[ 1 ] : "_";
}

// Debug function

#ifdef __DEBUG
void CmdParams::DispAll() const
{
	std::cout << "Arguments:\n";
	for( auto & arg : m_args ) {
		std::cout << arg << "\n";
	}

	std::cout << "\nOptions:\n";
	for( auto & opt : m_opts ) {
		std::cout << opt.first << ": " << opt.second << "\n";
	}
}
#endif