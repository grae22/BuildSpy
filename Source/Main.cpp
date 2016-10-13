#include "BuildStartStrategy.h"
#include "BuildEndStrategy.h"

#include <boost/log/utility/setup/file.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/filesystem.hpp>
#include <boost/asio/ip/host_name.hpp>
#include <string>
#include <iomanip>

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

// Constants.

const boost::uintmax_t c_maxLogFileSize = 1024 * 1024;
const string c_projectLogExt( ".buildspy-prj-log" );
const boost::uintmax_t c_copyToServerLogSizeThreshold = 256;
const string c_separator( "-+-" );

//-----------------------------------------------------------------------------

// Function prototypes.

void InitLog( const string& absLogFilename );
void CopyLogsToServer( const string& appPath, const string& serverPath );

//-----------------------------------------------------------------------------

// Args:
// 0: Executable path.
// 1: Project name.
// 2: Build started (0) or ended (1).
// 3: Server path to copy logs to.

int main( int argc, char* argv[] )
{
  // Init the log file.
  if( argc == 0 )
  {
    return 1;
  }

  fs::path execPath( fs::path( argv[ 0 ] ).parent_path() );
  execPath += fs::path::preferred_separator;

  const string buildSpyPath( execPath.string() );

  InitLog( buildSpyPath + "Build-Spy.log" );

  LOG_INFO( "BuildSpy path: " + buildSpyPath );

  // Not enough args?
  if( argc < 4 )
  {
    LOG_ERR( "Called with too few arguments." );
    return 1;
  }

  // Project name.
  const string projectName( argv[ 1 ] );

  LOG_INFO( "Project: " + projectName );

  // Project log filename.
  const string absProjectLogFilename( buildSpyPath + projectName + c_projectLogExt );

  // Server path.
  const string serverPath( argv[ 3 ] );

  // Build started/ended.
  const char mode = argv[ 2 ][ 0 ];
  unique_ptr< IBuildStrategy > buildStrategy = nullptr;

  if( mode == '0' )
  {
    LOG_INFO( "Mode: Build started." );

    buildStrategy = make_unique< BuildStartStrategy >();
  }
  else if( mode == '1' )
  {
    LOG_INFO( "Mode: Build ended." );

    buildStrategy = make_unique< BuildEndStrategy >();
  }
  else
  {
    LOG_ERR( "Unknown mode specified." );
  }

  if( buildStrategy != nullptr )
  {
    try
    {
      buildStrategy->Execute( absProjectLogFilename );
    }
    catch( exception* ex )
    {
      LOG_ERR( string( "Failed to execute strategy: " ) + ex->what() );
    }
  }

  // Copy logs to server.
  CopyLogsToServer( buildSpyPath, serverPath );

  // Closing.
  LOG_INFO( "Bye." );

  return 0;
}

//-----------------------------------------------------------------------------

void InitLog( const string& absLogFilename )
{
  // Log too big?
  fs::path logPathOb( absLogFilename );

  if( fs::exists( logPathOb ) &&
      fs::file_size( logPathOb ) > c_maxLogFileSize )
  {
    fs::remove( logPathOb );
  }

  // Initialise boost logging.
  logging::add_common_attributes();

  logging::add_file_log
  (
    loggingKeywords::file_name = absLogFilename,
    loggingKeywords::format = "[%TimeStamp%] %Message%",
    loggingKeywords::open_mode = ios_base::app
  );

  LOG_INFO( "Log initialised." );
}

//-----------------------------------------------------------------------------

void CopyLogsToServer( const string& appPath,
                       const string& serverPath )
{
  try
  {
    LOG_INFO( "Attempting to copy logs..." );

    // Server available?
    if( fs::exists( serverPath ) == false )
    {
      LOG_ERR( string( "Server path not found: " ) + serverPath );
      return;
    }

    // Create timestamp.
    time_t t = time( nullptr );
    stringstream ss;
    ss << put_time( localtime( &t ), "%Y%m%d%H%M%S" );
    const string timestamp( ss.str() );

    // Copy each log to the server.
    boost::system::error_code errorCode;
    fs::directory_iterator endIt;

    for( fs::directory_iterator it( appPath );
         it != endIt;
         ++it )
    {
      if( fs::is_regular_file( *it ) &&
          it->path().extension() == c_projectLogExt &&
          fs::file_size( it->path() ) > c_copyToServerLogSizeThreshold )
      {
        const string logServerFilename(
          serverPath +
          timestamp +
          c_separator +
          boost::asio::ip::host_name() +
          c_separator +
          it->path().filename().string() );

        LOG_INFO( "Attemping to copy to: " + logServerFilename );

        fs::copy_file(
          it->path(),
          fs::path( logServerFilename ),
          fs::copy_option::none,
          errorCode );

        if( errorCode == 0 )
        {
          LOG_INFO( "Copied: " + logServerFilename );

          fs::remove( it->path() );
        }
      }
    }
  }
  catch( exception* ex )
  {
    LOG_ERR( ex->what() );
  }
  catch( exception& ex )
  {
    LOG_ERR( ex.what() );
  }
}

//-----------------------------------------------------------------------------