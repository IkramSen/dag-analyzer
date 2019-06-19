
%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "3.0.4"
%defines
%define parser_class_name {hdag_parser}
%define api.token.constructor
%define api.value.type variant
%define parse.assert
%code requires
{
# include <string>
  class hdag_driver;
  // The alternative node must be fixed 
 
}
// The parsing context.
%param { hdag_driver& driver }
%locations
%initial-action
{
  // Initialize the initial location.
  @$.begin.filename = @$.end.filename = &driver.file;
};
%define parse.trace
%define parse.error verbose
%code
{
# include "hdag_driver.hh"
 int s_id = 0;
 bool forget =false;
 common::List<task::Subtask *> *last_cond = new common::List<task::Subtask *>();
}
%define api.token.prefix {TOK_}

%token END "End"
%token OPENB "{"
%token CLOSEB "}"
%token OPENP "("
%token TAG    "Tag" 
%token CLOSEP ")"
%token PAR "par"
%token ALTA "alta"
%token IF   "if"
%token ELSE "else" 
%token COMMA ","
%token NODE "Node"
%token DNODE "dNode"
%token SUBGRAPH "sGraph"
%token GRAPH "Graph"
%token CONDITION "Condition"
%token LOCK "lock"
%token COPY "copy"
%token LOCKV "Lock"
%token GENERATE "generate"
%token LEND ";"
%token EQUAL "="
%token COMMENT "comment"
%token SHARE "share"


%token <std::string> QUOTED "quoted"
%token <std::string> IDENTIFIER "identifier"
%token <int> NUMBER "number"

%printer { yyoutput << $$; } <*>;
%%
%start unit;
unit:
%empty
|unit node_exp
|unit dnode_exp
|unit subgraph_exp
|unit graph_exp
|unit condition_exp
|unit graph_remp
|unit copying
|unit ending 
|unit tagging
|unit generating
|unit commenting
|unit sharing
;

commenting: "comment" {printf("j'ai trouvé un cmme \n");}

copying: "copy" "(" "identifier" "," "identifier" ")" ";"
{
  PRINT_DEBUG("Copy operation recognized between "+$3+" and "+$5);
  if (!driver.subgraphs->count($3)>0)
    fatal_error(31,"In copying "+$3+ " : Copy operation is reserved to sub graphs only. ");
  if (driver.sgraphs->count($5)>0){
    task::Task * tau = (*(driver.subgraphs))[$3]->copy_partial(s_id);
    s_id+=tau->_subtasks()->size;
    driver.subgraphs->insert({$5,tau});
  }
  else
    fatal_error(1,"In copying "+$5+ " : Copy operation is reserved to sub graphs only. ");

  PRINT_DEBUG("Ending of the copy operation"); 
}


sharing: "share" "(" "identifier" "," "identifier" "," "identifier" ")" ";"
{

  // Houssam : I need to do the processing here of sharing !!
  // find the task, buffer, and subtasks
  //  add the communication to the task 
}


ending: "End"
{
  std::cout<<"Processing finished"<<std::endl;
  return 0;
}

generating:  "generate" "(" "identifier" "," "quoted" ")" ";"
{
  if (driver.subgraphs->count($3)>0){
    std::string s = $5;
    s.erase(remove( s.begin(), s.end(), '\"' ),s.end());
    (*(driver.subgraphs))[$3]->to_dot(s);
  }
  else if(driver.tasks->count($3)){
    std::string s = $5;
    s.erase(
	    remove( s.begin(), s.end(), '\"' ),
	    s.end()
	    );
    (*(driver.tasks))[$3]->to_dot(s);
  }
  else 
    fatal_error(20, $3+" must be a  graph or a sub-graph");

}


graph_remp :  "identifier" "=" "{" complex_exp "}" ";"
{
  
  PRINT_DEBUG("Expression of  "+ $1 +" has been correctly recongnized \n");
  if (driver.sgraphs->count($1)>0)
    driver.subgraphs->insert({$1,driver.temp_tasks->head->el});
  else if(driver.graphs->count($1))
    driver.tasks->insert({$1,driver.temp_tasks->head->el});
  else
    fatal_error(21, $1+" is not a graph nor a sub-graph");
  PRINT_DEBUG("Expression with "+ $1 +" has been correctly  added \n");
  driver.temp_tasks = new common::List<task::Task *>();
};

complex_exp:
%empty
|complex_exp suite
{
  PRINT_DEBUG("SUITE reconignzed");
}
|complex_exp  conditional
{
  PRINT_DEBUG("CONDITIAL reconignzed");
}
|complex_exp "par" "(" identifiers ")" ";"
{
  PRINT_DEBUG("par  reconignzed");
  common::List<task::Subtask *> * l = new common::List<task::Subtask *> ();
  task::Task * tau = new task::Task(111,l);
  for (int i=0;i<driver.temp_ident->size;i++){
    std::string curr =  driver.temp_ident->get(i);
    if (driver.subtasks->count(curr)>0)
      tau->add_subtask((*(driver.subtasks))[curr]);
    else if (driver.sgraphs->count(curr)>0)
      {
	if ((*(driver.subgraphs))[curr]==NULL)
	  fatal_error(41,curr+ " Subgraph is empty \n"); 
	tau->merge_task((*(driver.subgraphs))[curr]);
      }
    else
      fatal_error(22, curr+" must be  a subgraph or a node, exitting "); 
  }
  if (driver.temp_tasks->size == 0){
    common::List<task::Subtask  *> * l_ = new common::List<task::Subtask  *> ();
    task::Task * tau  = new task::Task(-1,l_);
    driver.temp_tasks->add_at_head(new common::Node<task::Task *>(tau)); 
  }
  driver.temp_tasks->tail()->el->link_task_after(tau);
  driver.temp_ident = new common::List<std::string>();
  PRINT_DEBUG("par  end");
}
|complex_exp "alta" "(" identifiers ")" ";"
{
  PRINT_DEBUG("alta  reconignzed");
  task::Subtask *s = new task::Subtask(s_id,0,0,ALTERNATIVE,-1);
  s->_label("ALT"+std::to_string(s_id));
  s_id ++;
  common::List<task::Subtask *> * l = new common::List<task::Subtask *> ();
  task::Task * tau = new task::Task(-1,l);
  for (int i=0;i<driver.temp_ident->size;i++){
    std::string curr =  driver.temp_ident->get(i);
    if (driver.subtasks->count(curr)>0)
      tau->add_subtask((*(driver.subtasks))[curr]);
    else if (driver.sgraphs->count(curr)>0) 
      tau->merge_task((*(driver.subgraphs))[curr]);
    else
      fatal_error(23, curr+" is must be a subtask or a subgraph");
  }
  if (driver.temp_tasks->size == 0){     
    common::List<task::Subtask  *> * l_ = new common::List<task::Subtask  *> ();
    task::Task * tau  = new task::Task(-1,l_);
    driver.temp_tasks->add_at_head(new common::Node<task::Task *>(tau)); 
  }
  printf("really \n");
  tau->to_dot("/tmp/ttol.dot");
  tau->link_new_entry(s);
  tau->to_dot("/tmp/attol.dot");
  driver.temp_tasks->tail()->el->link_task_after(tau);
  
}

suite: "identifier" ";"
{
   PRINT_DEBUG("identifier  reconignzed");
  if (driver.temp_tasks->size == 0){  
    common::List<task::Subtask  *> * l_ = new common::List<task::Subtask  *> ();
    task::Task * tau  = new task::Task(-1,l_);
    driver.temp_tasks->add_at_head(new common::Node<task::Task *>(tau)); 
  }
  if (driver.subgraphs->count($1)>0)
    driver.temp_tasks->tail()->el->link_task_after((*driver.subgraphs)[$1]);
  else if (driver.subtasks->count($1)>0)
    driver.temp_tasks->tail()->el->link_new_exit((*driver.subtasks)[$1]);
  else
    fatal_error(24, $1+"\" has not been declared in this scope");
  PRINT_DEBUG("identifier  process end");
}

conditional : identifier_c "{" complex_exp_r "}" next 
{

  if (driver.temp_tasks->tail()->el->_subtasks()->size==0){
    task::Subtask * s = new task::Subtask(s_id,0,0,DUMMY,-1);
    s->_label("dummy_"+std::to_string(s_id));
    s_id++;
    driver.temp_tasks->tail()->el->add_subtask(s);
      
  }
  common::Node<task::Subtask *> *s = driver.temp_tasks->before_before_tail()->el->_subtasks()->tail();  
  driver.temp_tasks->before_before_tail()->el->link_task_after(driver.temp_tasks->tail()->el);
  driver.temp_tasks->remove(driver.temp_tasks->tail()->el);
 

 
  driver.temp_tasks->before_tail()->el->link_task_after_subtask(driver.temp_tasks->tail()->el, s->el );
  // do not forget to set thaat this is the closing one 
  task::Subtask *s_e = new task::Subtask(s_id,0,0,CCONDITION,-1);


  s_e->_label(last_cond->tail()->el->_label()+"_c");
  s_e->_silent_subtask(last_cond->tail()->el);
  last_cond->remove(last_cond->tail()->el);


  
  
  driver.temp_tasks->before_tail()->el->link_new_exit(s_e);
  driver.temp_tasks->remove(driver.temp_tasks->tail()->el);

  
}

complex_exp_r: complex_exp
{
  common::List<task::Subtask  *> * l_ = new common::List<task::Subtask  *> ();
  task::Task * tau  = new task::Task(-1,l_);
  driver.temp_tasks->add_at_tail(new common::Node<task::Task *>(tau));
}

next:
%empty 
| "else" "{" complex_exp "}";


subgraph_exp: "sGraph" identifiers ";"
{
  for (int i=0;i<driver.temp_ident->size;i++){
    std::string  curr = driver.temp_ident->get(i);
     if (driver.sgraphs->count(curr)>0)
      fatal_error(25,"Subgraph : \""+curr+"\" has been already declared"); 
    driver.sgraphs->insert({curr,driver.sgraphs->size()});
  }

  driver.temp_ident = new common::List<std::string>();
}
// Houssam : n'oublie pas d'ajouter la fonction print_debug 
graph_exp:  "Graph" "identifier" parenthesis_node ";"
{
  std::map<std::string, std::string>::iterator it;
  int D=-1, T=-1;
  for (it = driver.temp_couples->begin(); it != driver.temp_couples->end(); it++ ){
    if (it->first.compare("T")==0){
      try {
      T=std::stoi(it->second,nullptr,10);
	if (T < 0)
	  fatal_error(26, $2+"\" : The parameter T must be a positive integer");
	continue;
      }
      catch (std::invalid_argument e){
	fatal_error(27, $2+"\": The parameter T must be an integer "); 
      } 
    }
    else if (it->first.compare("D")==0){
      try {
      D=std::stoi(it->second,nullptr,10);
	if (D < 0)
	  fatal_error(30,"Node \""+$2+"\" : The parameter D must be a positive integer");
	continue;
      }
      catch (std::invalid_argument e){
	fatal_error(9, "\""+$2+"\": The parameter D must be an integer");
      } 
    }
    else
      fatal_error(10,"\""+$2+"\": is  a unknown option ");
  }
  if (D==-1 || T==-1)
    fatal_error(11, "Parameters D and T are mondatory");
  if (driver.graphs->count($2)>0)
    fatal_error(12,"Graph :\""+$2+"\"has been already declared");
    
  driver.graphs->insert({$2,driver.graphs->size()});
  driver.temp_couples = new std::map<std::string,std::string>();


  PRINT_DEBUG("The task "+$2+" Declaration end");

}

condition_exp: "Condition" identifiers ";"
{
  PRINT_DEBUG("*************************************************** ");
  for (int i=0;i<driver.temp_ident->size;i++){
    std::string curr = driver.temp_ident->get(i);
    PRINT_DEBUG("this is conditions: "+curr+"\n"); 
    if (driver.conditions->count(curr)>0)
      fatal_error(13, "Condition :\""+curr+"\" has been already declared");
    driver.conditions->insert({curr,driver.conditions->size()});
  }
  PRINT_DEBUG( "*************************************************** \n"); 
  driver.temp_ident = new common::List<std::string>();
}

tagging : "Tag" identifiers ";"
{
 
  for (int i=0;i<driver.temp_ident->size;i++){
    std::string curr = driver.temp_ident->get(i);
    if (driver.tags->count(curr)>0)
      fatal_error(14," Tag :"+curr+"has been already declared ");
    driver.tags->insert({curr,driver.tags->size()});
  }
  driver.temp_ident = new common::List<std::string>();
}

identifier_c : "if" "(" "identifier" ")"
{

#ifdef DEBUG
  std::cout<<"Number of conditions: "<< driver.conditions->size() << std::endl;
  std::cout<<"List of conditions :"<<std::endl;
  std::map<std::string, int>::iterator it;
  for ( it = driver.conditions->begin(); it != driver.conditions->end(); it++ )
    {
      std::cout << it->first  // string (key)
		<< ':'
		<< it->second   // string's value 
		<< std::endl ;
    }
  std::cout<<" This is the current condition " <<$3<<std::endl;
  std::cout<<"this is the lane found values " << (*(driver.conditions))["lane_found_1"]<<std::endl;
  std::cout<<"This is the count : " << driver.conditions->count($3)<<"This is the test  " << (*(driver.conditions))[$3]<<std::endl;
#endif
  if (driver.conditions->count($3)==0)
    fatal_error(15,"Condition :\""+$3+"\" has not been declared");

  task::Subtask * s = new task::Subtask(s_id,0,0,CONDITION,-1);
  s->_label($3);
  last_cond->add(s);
  s_id++;
  driver.temp_tasks->tail()->el->link_new_exit(s);
  
  common::List<task::Subtask  *> * l_ = new common::List<task::Subtask  *> ();
  task::Task * tau  = new task::Task(-1,l_);
  driver.temp_tasks->add_at_tail(new common::Node<task::Task *>(tau));
}

identifiers : "identifier"
{
  driver.temp_ident->add_at_head(new common::Node<std::string>($1));
}
|identifiers "," "identifier"
{
  driver.temp_ident->add_at_head(new common::Node<std::string>($3));
}

node_exp:  "Node" "identifier" parenthesis_node ";"
{
  std::map<std::string, std::string>::iterator it;
  std::map<std::string, std::string> * properties = new std::map<std::string, std::string>();
  int C=-1, PC=0;
  std::string tag="EMPTY_TAG"; 
  for (it = driver.temp_couples->begin(); it != driver.temp_couples->end(); it++ ){
    bool tag_found= false;
    if (it->first.compare("TAG")==0){
      if (driver.tags->count(it->second)==0)
	fatal_error(16,"Tag \""+it->second+"\" was not declared in this scope");
      tag= it->second;
      continue;
    }
    else if (it->first.compare("C")==0){
      try {
	C=std::stoi(it->second,nullptr,10);
	if (C < 0)
	  fatal_error(17," \""+$2+"\" : The arameter C must be a positive integer");
	continue;
      }
      catch (std::invalid_argument e){
	fatal_error(18, " Node \""+$2+"\": The parameter C must be an integer");
      }
    }
    else if (it->first.compare("PC")==0){
      try {
	PC=std::stoi(it->second,nullptr,10);
	if (PC < 0)
	  fatal_error(19," \""+$2+"\" : The parameter PC must be a positive integer");
	continue;
      }
      catch (std::invalid_argument e){
	fatal_error(28," Node \""+$2+"\" : The parameter PC must be an integer");
      }
    }
    properties->insert({it->first,it->second});
  }
  if (C==-1)
    fatal_error(29,"Node \""+$2+"\" : The parameter C is mondatory");
  if (tag.compare("EMPTY_TAG")==0)
    std::cerr<<"Warning: Tag not declared for  Node \""<<$2<<"\", it will be set to default TAG \n";

  task::Subtask * st = new task::Subtask(s_id, C, PC, COMPUTE, (*(driver.tags))[tag]);
  st->_label($2);
  driver.subtasks->insert({$2,st});

  
  driver.temp_couples = new std::map<std::string,std::string>();
  s_id+=1; 
};

dnode_exp:  "dNode" "identifier" parenthesis_node ";"
{
  std::map<std::string, std::string>::iterator it;
  int size = -1;
  std::string type="type";
  for (it = driver.temp_couples->begin(); it != driver.temp_couples->end(); it++ ){
    if (it->first.compare("Size")==0){
      try {
	size=std::stoi(it->second,nullptr,10);
	if (size < 0)
	  fatal_error(8,"Error in declaring dNode \""+$2+"\" : The parameter Size must be a positive integer");
      }
      catch (std::invalid_argument e){
	fatal_error(31," Node \""+$2+"\" : The parameter Size must be an integer");
      }
    }
    else   if (it->first.compare("Type")==0)
      type=it->second;
    else
      fatal_error(42,"dNodes support only Type and Size attributes");
  }
  if (type.compare("type") == 0)
    fatal_error(32, "dNode \""+$2+"\" : The parameter Type  is mondatory");
  if (size==-1)
    fatal_error(33, "dNode \""+$2+"\" : The parameter size is mondatory");


  task::Buffer *b = new task::Buffer($2,type,size);
  driver.buffers->insert({$2,b});
  driver.temp_couples = new std::map<std::string,std::string>();
  driver.subtask_id++;
};

parenthesis_node : "(" equality  ")"                    {};

equality : "identifier" "=" "identifier"
{
  if (driver.temp_couples->count($1) > 0)
    fatal_error(2, $1+" property has already been declared for the current element");   
  driver.temp_couples->insert({$1,$3});
}
| equality  ","  "identifier" "=" "identifier"
{
  if (driver.temp_couples->count($3) > 0)
    fatal_error(3,$3+" property has already been declared for the current element");  
  driver.temp_couples->insert({$3,$5});
}
| "identifier" "=" "number"
{
  if (driver.temp_couples->count($1) > 0)
    fatal_error(4, $1+" property has already been declared for the current element");
  driver.temp_couples->insert({$1,std::to_string($3)});
}

| equality  ","  "identifier" "=" "number"          {  
  if (driver.temp_couples->count($3) > 0)
    fatal_error(5,$3+" property has already been declared for the current element");     
  driver.temp_couples->insert({$3,std::to_string($5)});
  }
| "identifier" "=" "quoted"
{
  if (driver.temp_couples->count($1) > 0)
    fatal_error(6,$1+" property has already been declared for the current element");
  driver.temp_couples->insert({$1,$3});
}
| equality  ","  "identifier" "=" "quoted"
{
  if (driver.temp_couples->count($3) > 0)
    fatal_error(7,$3+" property has already been declared for the current element");  
  driver.temp_couples->insert({$3,$5});
}

%%
void
yy::hdag_parser::error (const location_type& l,
			const std::string& m)
{
  driver.error (l, m);
}
