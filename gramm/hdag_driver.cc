#include "hdag_driver.hh"
#include "hdag_parser.hh"

hdag_driver::hdag_driver ()
  : trace_scanning (false), trace_parsing (false)
{
  temp_ident = new common::List<std::string>();
  temp_couples = new std::map<std::string,std::string>();
  tags = new std::map<std::string, int> ();
  sgraphs = new std::map<std::string, int> ();
  graphs = new std::map<std::string, int> ();
  conditions = new std::map<std::string, int> ();
  
  subtasks = new  std::map<std::string, task::Subtask *>();
  subgraphs = new std::map<std::string, task::Task *> () ;
  tasks = new std::map<std::string, task::Task *>();
  int subtask_id;
  temp_tasks = new common::List<task::Task * > ();
  subgraphs_names = new common::List<std::string>();
  tasks_names = new common::List<std::string>();
  subtask_id=0;
}

hdag_driver::~hdag_driver () {
}

int hdag_driver::parse (const std::string &f) {
  file = f;
  scan_begin ();
  yy::hdag_parser parser (*this);
  parser.set_debug_level (trace_parsing);
  int res = parser.parse ();
  scan_end ();
  return res;
}

void hdag_driver::error (const yy::location& l, const std::string& m){
  std::cerr << l << ": " << m << std::endl;
}

void hdag_driver::error (const std::string& m)
{
  std::cerr << m << std::endl;
}
