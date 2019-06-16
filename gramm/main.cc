#include <iostream>
#include "hdag_driver.hh"


int
main (int argc, char *argv[])
{
  if (argc < 2)
    fatal_error("Usage: [Exec-Parser] [input-file]");

  int res = 0;
  hdag_driver driver;
  for (int i = 1; i < argc; ++i)
    if (argv[i] == std::string ("-p"))
      driver.trace_parsing = true;
    else if (argv[i] == std::string ("-s"))
      driver.trace_scanning = true;
    else if (!driver.parse (argv[i]))
      std::cout << "" << std::endl;
    else
      res = 1;
  return res;
}

