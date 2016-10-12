#include "BuildStartStrategy.h"
#include "ProjectLog.h"

#include <memory>

//-----------------------------------------------------------------------------

using namespace std;

//-----------------------------------------------------------------------------

BuildStartStrategy::BuildStartStrategy()
{
}

//-----------------------------------------------------------------------------

BuildStartStrategy::~BuildStartStrategy()
{
}

//-----------------------------------------------------------------------------

void BuildStartStrategy::Execute( const std::string& absProjectLogFilename )
{
  auto log = make_unique< ProjectLog >( absProjectLogFilename );

  log->AddEntry( "build_start" );
}

//-----------------------------------------------------------------------------