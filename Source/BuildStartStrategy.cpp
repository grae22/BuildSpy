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

void BuildStartStrategy::Execute(
  const std::string& appPath,
  const std::string& projectName )
{
  const string filename( appPath + projectName );

  auto log = make_unique< ProjectLog >( filename );

  log->AddEntry( "build_start" );
}

//-----------------------------------------------------------------------------