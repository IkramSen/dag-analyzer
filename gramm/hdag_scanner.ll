%{ /* -*- C++ -*- */
# include <cerrno>
# include <climits>
# include <cstdlib>
# include <string>
# include "hdag_driver.hh"
# include "hdag_parser.hh"

// Work around an incompatibility in flex (at least versions
// 2.5.31 through 2.5.33): it generates code that does
// not conform to C89.  See Debian bug 333231
// <http://bugs.debian.org/cgi-bin/bugreport.cgi?bug=333231>.
# undef yywrap
# define yywrap() 1

// The location of the current token.
static yy::location loc;
%}
%option noyywrap nounput batch debug noinput
id    [a-zA-Z][a-zA-Z_0-9]*
qt    \"\/*[a-zA-Z][a-zA-Z_0-9 \* \/ . \t]*\"
int   [0-9]+
blank [ \t]

%{
  // Code run each time a pattern is matched.
  # define YY_USER_ACTION  loc.columns (yyleng);
%}

%%

%{
  // Code run each time yylex is called.
  loc.step ();
%}

{blank}+   loc.step ();
[\n]+      loc.lines (yyleng); loc.step ();
"{"          return yy::hdag_parser::make_OPENB(loc);
"}"          return yy::hdag_parser::make_CLOSEB(loc);
"("          return yy::hdag_parser::make_OPENP(loc);
"Tag"        return yy::hdag_parser::make_TAG(loc);
")"          return yy::hdag_parser::make_CLOSEP(loc);
"par"        return yy::hdag_parser::make_PAR(loc);
"alta"       return yy::hdag_parser::make_ALTA(loc);
"if"         return yy::hdag_parser::make_IF(loc);
"else"       return yy::hdag_parser::make_ELSE(loc);
","          return yy::hdag_parser::make_COMMA(loc);
"Node"       return yy::hdag_parser::make_NODE(loc);
"dNode"      return yy::hdag_parser::make_DNODE(loc);
"Condition"  return yy::hdag_parser::make_CONDITION(loc);
"lock"       return yy::hdag_parser::make_LOCK(loc);
"copy"       return yy::hdag_parser::make_COPY(loc);
"share"       return yy::hdag_parser::make_SHARE(loc);
"Lock"       return yy::hdag_parser::make_LOCKV(loc);
";"          return yy::hdag_parser::make_LEND(loc);
"="          return yy::hdag_parser::make_EQUAL(loc);
"sGraph" return yy::hdag_parser::make_SUBGRAPH(loc);
"Graph"  return yy::hdag_parser::make_GRAPH(loc);
"generate"  return yy::hdag_parser::make_GENERATE(loc);
"\/\*([^*]|[\r\n]|(\*+([^*/]|[\r\n])))*\*+\/"   {printf("comment found \n");return yy::hdag_parser::make_COMMENT(loc);}

{int}      {
  errno = 0;
  long n = strtol (yytext, NULL, 10);
  if (! (INT_MIN <= n && n <= INT_MAX && errno != ERANGE))
    driver.error (loc, "integer is out of range");
  return yy::hdag_parser::make_NUMBER(n, loc);
}
{qt}       return yy::hdag_parser::make_QUOTED(yytext, loc);
{id}       return yy::hdag_parser::make_IDENTIFIER(yytext, loc);
.          driver.error (loc, "invalid character");
<<EOF>>    return yy::hdag_parser::make_END(loc);
%%

void
hdag_driver::scan_begin ()
{
  yy_flex_debug = trace_scanning;
  if (file.empty () || file == "-")
    yyin = stdin;
  else if (!(yyin = fopen (file.c_str (), "r")))
    {
      error ("cannot open " + file + ": " + strerror(errno));
      exit (EXIT_FAILURE);
    }
}


void hdag_driver::scan_end ()
{
  fclose (yyin);
}
