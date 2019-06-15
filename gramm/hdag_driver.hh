#ifndef HDAG_DRIVER_HH
#define HDAG_DRIVER_HH
#include <string>
#include <map>
#include "hdag_parser.hh"
#include "../common/list.hpp"
#include "../common/common.hpp"
#include "../task/subtask.hpp"
#include "../task/task.hpp"

// Tell Flex the lexer's prototype ...
# define YY_DECL \
  yy::hdag_parser::symbol_type yylex (hdag_driver& driver)
// ... and declare it for the parser's sake.
YY_DECL;
// Conducting the whole scanning and parsing of Calc++.
class hdag_driver
{
public:
  hdag_driver ();
  virtual ~hdag_driver ();

  std::map<std::string, std::string> * temp_couples;
  common::List<std::string> * temp_ident;

  std::map<std::string, int> *  tags;
  std::map<std::string, int> *  sgraphs;
  std::map<std::string, int> *  graphs;
  std::map<std::string, int> *  conditions;
  std::map<std::string, task::Subtask *> * subtasks;

  std::map<std::string, task::Task *> * subgraphs;
  std::map<std::string, task::Task *> * tasks;

  // jen e sais pas si je dois 
  common::List<task::Task * > * temp_tasks;
  common::List<std::string> * subgraphs_names;
  common::List<std::string> * tasks_names;
  
  
  int subtask_id;

  // Handling the scanner.
  void scan_begin ();
  void scan_end ();
  bool trace_scanning;
  int parse (const std::string& f);
  std::string file;
  bool trace_parsing;
  void error (const yy::location& l, const std::string& m);
  void error (const std::string& m);
};
#endif // ! HDAG_DRIVER_HH
