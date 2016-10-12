#include "BuildEndStrategy.h"
#include "ProjectLog.h"

#include <memory>

//-----------------------------------------------------------------------------

using namespace std;

//-----------------------------------------------------------------------------

BuildEndStrategy::BuildEndStrategy()
{
}

//-----------------------------------------------------------------------------

BuildEndStrategy::~BuildEndStrategy()
{
}

//-----------------------------------------------------------------------------

void BuildEndStrategy::Execute(
  const std::string& appPath,
  const std::string& projectName )
{
  const string filename( appPath + projectName );

  auto log = make_unique< ProjectLog >( filename );

  log->AddEntry( "build_end" );
}

//-----------------------------------------------------------------------------