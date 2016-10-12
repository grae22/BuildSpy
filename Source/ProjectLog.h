#ifndef PROJECTLOG_H
#define PROJECTLOG_H

#include <string>
#include <fstream>

//-----------------------------------------------------------------------------

class ProjectLog
{
public:
  ProjectLog( const std::string& filename );
  virtual ~ProjectLog();

  void AddEntry( const std::string& text );

private:
  std::ofstream m_file;
};

//-----------------------------------------------------------------------------

#endif