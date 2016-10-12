#ifndef IBUILDSTRATEGY_H
#define IBUILDSTRATEGY_H

#include <string>

//-----------------------------------------------------------------------------

class IBuildStrategy
{
public:
  virtual ~IBuildStrategy() { }

  virtual void Execute(
    const std::string& appPath,
    const std::string& projectName ) = 0;
};

//-----------------------------------------------------------------------------

#endif