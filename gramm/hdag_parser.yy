
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
 //#define DEBUG 
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
;

commenting: "comment" {printf("j'ai trouvé un cmme \n");}

copying: "copy" "(" "identifier" "," "identifier" ")" ";"
{
  if (driver.subgraphs->count($5)>0){
    task::Task * tau = (*(driver.subgraphs))[$5]->copy_partial(s_id);
    s_id+=tau->_subtasks()->size;
    driver.subgraphs->insert({$3,tau});
    driver.temp_ident = new common::List<std::string>();
  }
  else {
    std::cerr<<"Error:"<<$5<<" Only sub-graphs are clonable, Not a Sub-graph or empty subgraph"<<std::endl;
    exit(-1);
  }
}


ending: "End"
{
  std::cout<<"Input file was parsed succefully \n";
  return 0;
}

generating:  "generate" "(" "identifier" "," "quoted" ")" ";"
{
  if (driver.subgraphs->count($3)>0){
    std::string s = $5;
    s.erase(
	    remove( s.begin(), s.end(), '\"' ),
	    s.end()
	    );
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
  else {
    std::cerr<<"Error: dot generation error"<<$3<<" is not a graph nor a sub-graph"<<std::endl;
    exit(-1);
  }
}


graph_remp :  "identifier" "=" "{" complex_exp "}" ";"
{
#ifdef DEBUG
  std::cout<<"Expression with "<< $1 <<" has been correctly recongnized"<<std::endl;
#endif

  if (driver.sgraphs->count($1)>0){
    driver.subgraphs->insert({$1,driver.temp_tasks->head->el});
  }
  else if(driver.graphs->count($1)){
    driver.tasks->insert({$1,driver.temp_tasks->head->el});
  }else {
    std::cerr<<"Error:"<<$1<<" is not a graph nor a sub-graph"<<std::endl;
    exit(-1);
  }
#ifdef DEBUG
  std::cout<<"Expression with "<< $1 <<" has been correctly  added as a graph or subgraph"<<std::endl;
#endif

  driver.temp_tasks = new common::List<task::Task *>();
};

complex_exp:
%empty
|complex_exp suite
|complex_exp  conditional
|complex_exp "par" "(" identifiers ")" ";"
{

  common::List<task::Subtask *> * l = new common::List<task::Subtask *> ();
  task::Task * tau = new task::Task(-1,l);
  common::Node<std::string> * curr =  driver.temp_ident->head;
  for (int i=0;i<driver.temp_ident->size;i++){
    if (driver.subtasks->count(curr->el)>0){
      tau->add_subtask((*(driver.subtasks))[curr->el]);
    }else if (driver.sgraphs->count(curr->el)>0) {
      tau->merge_task((*(driver.subgraphs))[curr->el]);
    }
    else {
      std::cerr<<curr->el<<" is not a subgraph or a node \n"<<std::endl;
      exit(-1);
    }
    curr = curr->next;
  }
  if (driver.temp_tasks->size == 0){
    common::List<task::Subtask  *> * l_ = new common::List<task::Subtask  *> ();
    task::Task * tau  = new task::Task(-1,l_);
    driver.temp_tasks->add_at_head(new common::Node<task::Task *>(tau)); 
  }
  driver.temp_tasks->tail()->el->link_task_after(tau);


}
|complex_exp "alta" "(" identifiers ")" ";"
{

  task::Subtask *s = new task::Subtask(s_id,0,0,ALTERNATIVE,-1);
  s->_label("ALT"+std::to_string(s_id));
  s_id ++;


  common::List<task::Subtask *> * l = new common::List<task::Subtask *> ();
  task::Task * tau = new task::Task(-1,l);
  common::Node<std::string> * curr =  driver.temp_ident->head;
  for (int i=0;i<driver.temp_ident->size;i++){
    if (driver.subtasks->count(curr->el)>0){

      tau->add_subtask((*(driver.subtasks))[curr->el]);
    }else if (driver.sgraphs->count(curr->el)>0) {
      tau->merge_task((*(driver.subgraphs))[curr->el]);
    }
    else {
      std::cout<<"Error : Node "<<curr->el<<" is not a subtask nor a subgraph"<<std::endl;
      exit(-1);
    }
     
        

    curr = curr->next;
  }

  if (driver.temp_tasks->size == 0){     
    common::List<task::Subtask  *> * l_ = new common::List<task::Subtask  *> ();
    task::Task * tau  = new task::Task(-1,l_);
    driver.temp_tasks->add_at_head(new common::Node<task::Task *>(tau)); 
  }
  tau->link_new_entry(s);
  driver.temp_tasks->tail()->el->link_task_after(tau);

}



suite: "identifier" ";"
{
  if (driver.temp_tasks->size == 0){
     
    common::List<task::Subtask  *> * l_ = new common::List<task::Subtask  *> ();
    task::Task * tau  = new task::Task(-1,l_);
    driver.temp_tasks->add_at_head(new common::Node<task::Task *>(tau)); 
  }

  if (driver.subgraphs->count($1)>0){
    driver.temp_tasks->tail()->el->link_task_after((*driver.subgraphs)[$1]);
  }
  else if (driver.subtasks->count($1)>0){
    driver.temp_tasks->tail()->el->link_new_exit((*driver.subtasks)[$1]);
  }
  else {
    std::cout<<"Error:  \""<<$1<<"\" has not been declared in this scope \n";

    exit(-1);
  }
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
  common::Node<std::string> * curr = driver.temp_ident->head;
  for (int i=0;i<driver.temp_ident->size;i++){
    if (driver.sgraphs->count(curr->el)>0){
      std::cout<<"Error: Subgraph :"<<curr->el<<"has been already declared \n";
      exit(-1);
    }
    driver.sgraphs->insert({curr->el,driver.sgraphs->size()});
    curr = curr -> next;
  }

  
  driver.temp_ident = new common::List<std::string>();
}



graph_exp: "Graph" identifiers ";"
{
  common::Node<std::string> * curr = driver.temp_ident->head;
  for (int i=0;i<driver.temp_ident->size;i++){
    if (driver.graphs->count(curr->el)>0){
      std::cout<<"Error: Graph :"<<curr->el<<"has been already declared \n";
      exit(-1);
    }
    driver.graphs->insert({curr->el,driver.graphs->size()});
    curr = curr -> next;
  }
  driver.temp_ident = new common::List<std::string>();
}
condition_exp: "Condition" identifiers ";"
{
  common::Node<std::string> * curr = driver.temp_ident->head;
#ifdef DEBUG 
    std::cout<<"*************************************************** "<<std::endl;
#endif
  for (int i=0;i<driver.temp_ident->size;i++){
#ifdef DEBUG 
    std::cout<<"this is conditions: "<<curr->el<<std::endl;
#endif
    if (driver.conditions->count(curr->el)>0){
      std::cout<<"Error: Condition :"<<curr->el<<"has been already declared \n";
      exit(-1); 
    }
    driver.conditions->insert({curr->el,driver.conditions->size()});
    curr = curr -> next;
  }
#ifdef DEBUG 
    std::cout<<"*************************************************** "<<std::endl;
#endif

    
  driver.temp_ident = new common::List<std::string>();
}


tagging : "Tag" identifiers ";"
{
  common::Node<std::string> * curr = driver.temp_ident->head;
  for (int i=0;i<driver.temp_ident->size;i++){
    if (driver.tags->count(curr->el)>0){
      std::cout<<"Error: Tag :"<<curr->el<<"has been already declared \n";
      exit(-1);
    }
    driver.tags->insert({curr->el,driver.tags->size()});
    curr = curr -> next;
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


  
  // I need to check that the condition exists !!
  if (driver.conditions->count($3)==0){
      std::cout<<"Error: Condition :"<<$3<<" has not been declared \n";
      exit(-1);
    }
  
  // process me like I am a new Id
  task::Subtask * s = new task::Subtask(s_id,0,0,CONDITION,-1);
  s->_label($3);
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
  /// add all tags and check that they do not exisit
  // define the rules of a correct node 
  std::map<std::string, std::string>::iterator it;
  std::map<std::string, std::string> * properties = new std::map<std::string, std::string>();
  int C=-1, PC=0;
  std::string tag="EMPTY_TAG"; 
  for (it = driver.temp_couples->begin(); it != driver.temp_couples->end(); it++ ){
    bool tag_found= false;
    //    checking if the tag exist
    if (it->first.compare("TAG")==0){
      if (driver.tags->count(it->second)==0){
	std::cerr<<"Tag "<<it->second<<" was not declared in this scope.\n";
	exit(-1);
      }
      tag= it->second;
      continue;
    }
    else if (it->first.compare("C")==0){
      try {
	C=std::stoi(it->second,nullptr,10);
	if (C < 0){
	  std::cerr<<"Error in declaring Node \""<<$2<<"\" : The parameter C must be a positive integer  \n";
	  exit(-1);
	}
	continue;
      }
      catch (std::invalid_argument e){
	std::cerr<<"Error in declaring Node \""<<$2<<"\": The parameter C must be an integer  \n";
	exit(-1);
      }
    }
    else if (it->first.compare("PC")==0){
      try {
	PC=std::stoi(it->second,nullptr,10);
	if (PC < 0){
	  std::cerr<<"Error in declaring Node \""<<$2<<"\" : The parameter PC must be a positive integer  \n";
	  exit(-1);
	}
	continue;
      }
      catch (std::invalid_argument e){
	std::cerr<<"Error in declaring Node \""<<$2<<"\" : The parameter PC must be an integer  \n";
	exit(-1);
      }
    }
    properties->insert({it->first,it->second});
  }
  if (C==-1){
    std::cout<<"Error in declaring Node \""<<$2<<"\" : The parameter C is mondatory \n";
    exit(-1);
  }
  if (tag.compare("EMPTY_TAG")==0){
    std::cerr<<"Warning: Tag not declared for  Node \""<<$2<<"\", it will be set to default TAG \n";
  }

  task::Subtask * st = new task::Subtask(s_id, C, PC, COMPUTE, (*(driver.tags))[tag]);
  st->_label($2);
  driver.subtasks->insert({$2,st});

  
  driver.temp_couples = new std::map<std::string,std::string>();
  s_id+=1; 
};

dnode_exp:  "dNode" "identifier" parenthesis_node ";"
{
  std::map<std::string, std::string>::iterator it;
  std::map<std::string, std::string> * properties = new std::map<std::string, std::string>();
  int size = -1;
  for (it = driver.temp_couples->begin(); it != driver.temp_couples->end(); it++ ){
    properties->insert({it->first,it->second});
    if (it->first.compare("Size")==0){
      try {
	size=std::stoi(it->second,nullptr,10);
	if (size < 0){
	  std::cerr<<"Error in declaring dNode \""<<$2<<"\" : The parameter Size must be a positive integer \n";
	  exit(-1);
	}
      }
      catch (std::invalid_argument e){
	std::cout<<"Error in declaring Node \""<<$2<<"\" : The parameter Size must be an integer  \n";
	exit(-1);
      }
    }
  }
  if (properties->count("Type") == 0){
    std::cerr<<"Error in declaring dNode \""<<$2<<"\" : The parameter Type  is mondatory \n";
    exit(-1);
  }
  if (size==-1){
    std::cerr<<"Error in declaring dNode \""<<$2<<"\" : The parameter size is mondatory \n";
    exit(-1);
  }
  driver.temp_couples = new std::map<std::string,std::string>();
  driver.subtask_id++;
};

parenthesis_node : "(" equality  ")"                    {};

equality : "identifier" "=" "identifier"
{
      
  if (driver.temp_couples->count($1) > 0){
    std::cerr<<$1<<" property has already been declared for the current element \n";
    exit(-1);
  }  
  driver.temp_couples->insert({$1,$3});
}
| equality  ","  "identifier" "=" "identifier"          {
  if (driver.temp_couples->count($3) > 0){
    std::cerr<<$3<<" property has already been declared for the current element \n";
    exit(-1);
  }  
  driver.temp_couples->insert({$3,$5});
  }

| "identifier" "=" "number"
{
  
  if (driver.temp_couples->count($1) > 0){
    std::cerr<<$1<<" property has already been declared for the current element 1 \n";
    exit(-1);
  }  
  driver.temp_couples->insert({$1,std::to_string($3)});
}

| equality  ","  "identifier" "=" "number"          {
  
  if (driver.temp_couples->count($3) > 0){
    std::cerr<<$3<<" property has already been declared for the current element 2 \n";
    exit(-1);
  }
   
  driver.temp_couples->insert({$3,std::to_string($5)});
  }
| "identifier" "=" "quoted"
{
  
  if (driver.temp_couples->count($1) > 0){
    std::cerr<<$1<<" property has already been declared for the current element 1 \n";
    exit(-1);
  }
  driver.temp_couples->insert({$1,$3});
}

| equality  ","  "identifier" "=" "quoted"          {
  if (driver.temp_couples->count($3) > 0){
    std::cerr<<$3<<" property has already been declared for the current element 2 \n";
    exit(-1);
  }
   
  driver.temp_couples->insert({$3,$5});
  }

%%
void
yy::hdag_parser::error (const location_type& l,
			const std::string& m)
{
  driver.error (l, m);
}
