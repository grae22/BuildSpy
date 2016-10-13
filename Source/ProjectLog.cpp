#include "ProjectLog.h"

#include <boost/filesystem.hpp>
#include <iomanip>

//-----------------------------------------------------------------------------

using namespace std;

//-----------------------------------------------------------------------------

ProjectLog::ProjectLog( const string& filename )
:
  m_file( filename, ios::out | ios::app )
{
  if( m_file.is_open() == false )
  {
    throw new exception(
      ( string( "Failed to open file: " ) + filename ).c_str() );
  }
}

//-----------------------------------------------------------------------------

ProjectLog::~ProjectLog()
{
  m_file.close();
}

//-----------------------------------------------------------------------------

void ProjectLog::AddEntry( const string& text )
{
  time_t t = time( nullptr );

  m_file
    << put_time( localtime( &t ), "%Y-%m-%d %H:%M:%S" )
    << '|'
    << text
    << '|'
    << endl;

  m_file.flush();
}

//-----------------------------------------------------------------------------