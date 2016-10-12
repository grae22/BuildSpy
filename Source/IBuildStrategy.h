#ifndef IBUILDSTRATEGY_H
#define IBUILDSTRATEGY_H

#include <string>

//-----------------------------------------------------------------------------

class IBuildStrategy
{
public:
  virtual ~IBuildStrategy() { }

  virtual void Execute( const std::string& absProjectLogFilename ) = 0;
};

//-----------------------------------------------------------------------------

#endif