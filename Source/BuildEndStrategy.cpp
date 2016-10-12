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

void BuildEndStrategy::Execute( const std::string& absProjectLogFilename )
{
  auto log = make_unique< ProjectLog >( absProjectLogFilename );

  log->AddEntry( "build_end" );
}

//-----------------------------------------------------------------------------