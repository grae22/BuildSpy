#ifndef BUILDSTARTSTRATEGY_H
#define BUILDSTARTSTRATEGY_H

#include "IBuildStrategy.h"

//-----------------------------------------------------------------------------

class BuildStartStrategy : public IBuildStrategy
{
public:
  BuildStartStrategy();
  virtual ~BuildStartStrategy();

  virtual void Execute(
    const std::string& appPath,
    const std::string& projectName ) override;
};

//-----------------------------------------------------------------------------

#endif