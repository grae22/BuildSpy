#include <boost/log/utility/setup/file.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/filesystem.hpp>
#include <string>

//-----------------------------------------------------------------------------

using namespace std;

namespace fs = boost::filesystem;

//-----------------------------------------------------------------------------

// Logging.

namespace logging = boost::log;
namespace loggingKeywords = boost::log::keywords;

#define LOG_INFO( msg ) BOOST_LOG_TRIVIAL( info ) << msg;
#define LOG_ERR( msg ) BOOST_LOG_TRIVIAL( error ) << msg;

//-----------------------------------------------------------------------------

// Function prototypes.

void InitLog();

//-----------------------------------------------------------------------------

// Args:
// 0: Executable path.
// 1: Project name.
// 2: Build started (0) or ended (1).

int main( int argc, char* argv[] )
{
  InitLog();

  // Not enough args?
  if( argc < 3 )
  {
    LOG_ERR( "Called with too few arguments." );
    return 1;
  }

  // Executable path.
  fs::path execPath( fs::path( argv[ 0 ] ).parent_path() );
  execPath += fs::path::preferred_separator;

  const string buildSpyPath( execPath.string() );

  LOG_INFO( "BuildSpy path: " + buildSpyPath );

  // Project name.
  const string projectName( argv[ 1 ] );

  LOG_INFO( "Project: " + projectName );

  // Build started/ended.
  const char mode = argv[ 2 ][ 0 ];

  if( mode == '0' )
  {
    LOG_INFO( "Mode: Build started." );
  }
  else if( mode == '1' )
  {
    LOG_INFO( "Mode: Build ended." );
  }
  else
  {
    LOG_ERR( "Unknown mode specified." );
  }

  LOG_INFO( "Bye." );

  return 0;
}

//-----------------------------------------------------------------------------

void InitLog()
{
  logging::add_common_attributes();

  logging::add_file_log
  (
    loggingKeywords::file_name = "buildspy.log",
    loggingKeywords::format = "[%TimeStamp%] %Message%"
  );

  LOG_INFO( "Log initialised." );
}

//-----------------------------------------------------------------------------