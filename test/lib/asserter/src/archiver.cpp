#include <cstring>
#include <fstream>
#include <sstream>
#include <vector>

#include "archiver.h"

using namespace std;

namespace private_assert
{
	archiver & archiver::instance()
	{
		static archiver local;
		return local;
	}

	archiver::~archiver()
	{
		fstream out( "result.json", fstream::out );

		out << "{\n";
		out << "\"passed\": " << m_passed;

		if (m_failed.begin() != m_failed.end())
		{
			out << "," << endl;

			auto i( m_failed.begin() );
			out << "\"failed\": [" << endl << *(i++) << endl;
			while (i != m_failed.end())
				out << ", " << *(i++) << endl;
			out << "]" << endl;
		}
		else { 
			out << endl;
		}
		out << "}\n";
	}

	void archiver::pass()
	{
		++m_passed;
	}

	void archiver::fail( 
		const char * file, 
		int line, 
        const char * function, 
        const char * message )
	{
		
		stringstream entry; 
		entry << "{" << endl;

		if (strlen(message))
		{
			entry << "\"message\":\"" << message << "\"," << endl;
		}
		entry << "\"file\":\"" << file << "\"," << endl;
		entry << "\"function\":\"" << function << "\"," << endl;
		entry << "\"line\":" << line << endl;
		entry << "}" << endl;

		m_failed.push_back( entry.str() );
	}
}	// private_assert