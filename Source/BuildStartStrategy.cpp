#include "BuildStartStrategy.h"

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
  const string filename( appPath + projectName + "_buildStart" );
}

//-----------------------------------------------------------------------------