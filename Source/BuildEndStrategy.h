#ifndef BUILDENDSTRATEGY_H
#define BUILDENDSTRATEGY_H

#include "IBuildStrategy.h"

//-----------------------------------------------------------------------------

class BuildEndStrategy : public IBuildStrategy
{
public:
  BuildEndStrategy();
  virtual ~BuildEndStrategy();

  virtual void Execute(
    const std::string& appPath,
    const std::string& projectName ) override;
};

//-----------------------------------------------------------------------------

#endif