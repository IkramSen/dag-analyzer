#ifndef LIST_HPP
#define LIST_HPP

#define  SAVE 1
#define  VOLA 0
#include<iostream>
#include <stdio.h>
#include <cmath>

namespace common {
  template <class Data> class Node {
  public:
    Data el;
    int t_id;
    int D;
    int O;
    bool empty;
    Node<Data> *next;

    /**
     * Constructor of the Node using the element of time Data
     */
    Node(Data e){
      el=e;
      next=NULL;
      D = -1;
      empty=false;
      t_id=-1;
      D=-1;
      O=-1;

    }

    /**
     * Constructor of the Node using another Node and saving parameters 
     * @param e the Node to copy and save 
     * @param save the parameter to set to SAVE of NOTSAVE 
     */
    Node(Node<Data> *e, int save){
      if (save == SAVE){
        el=e->el;
        t_id=e->t_id;
        D = e->D;
        O = e->O;
        empty = e->empty;
        next=NULL;
      }
    }


    
    /**
     * Display the current Node 
     */
    void display(){
      el->display();
      std::cout<<"\t [Additional: t_id : "<<t_id<<",D:"<<D<<", O: "<<O<<", empty: " << (empty ? "true":"false")<<" ]"<<std::endl;
    }
  };

  template < class Data > class List {
  public:
    Node<Data > *head;
    int size;

    /** 
     * Add an element to the head of the current list 
     * @param e The node to add 
     */
    void add_at_head(Node<Data > *e) {
      size++;
      if (!head){
        head=e;
	return;
      }else {
	e->next = head;
	head = e;
	return;
      }
    }

    /** 
     * Get an element by index 
     * @param idx  The index of the node to return 
     * @return The node of index idx if the idx is valid, otherwise it returns NULL
     */
    // Houssam :  to be optimized 
    Node<Data > * _get(int idx){
      if(idx>size || idx < 0){
	std::cerr<<"Index out of the array, exitting " << std::endl; 
	exit(-1);
      }
      Node<Data> * obj = head;
      for(int i=0;i<idx;i++){
        obj = obj->next;
      }
      return obj;
    }

    Data get(int idx){
      return  _get(idx)->el;
    }

    
    bool contains_string(std::string l){
      Node<Data> * obj = head;
      for(int i=0;i<size;i++){
	if (obj->el.compare(l)==0)
	  return true;
	obj = obj->next;
      }
      return false;
    }

    
    /** 
     * Find the node by the data it contains 
     * @param e the data we are looking for 
     * @return returns the Node reference if found, else returns NULL
     */
    Node <Data> * find_element(Data e){
      Node<Data> * current = head;
      for (int i=0;i<size;i++){
	if (current->el == e)
	  return current;
        current = current->next;
      }
      return NULL;
    }
    
    /** 
     * Checks wiether the task the element e is in the list 
     * @param e the element we are looking for 
     * @return True if found, else it returns false 
     */
    bool contains(Data e){
      Node<Data> * el = find_element(e);
      return el!=NULL;
    }

    /** 
     * Looks for the last element in the list 
     * @return the tail of the list  
     */
    Node <Data>  * tail(){
      Node<Data> *last = head;
      for(int i=0;i<size-1;i++){
	last = last->next;
      }
      return last;
    }

    /** 
     * Looks for the predecessor of last element in the list 
     * @return the predecessor of the  tail element 
     */
    Node <Data>  * before_tail(){
      Node<Data> *last = head;
      for(int i=0;i<size-2;i++){
	last = last->next;
      }
      return last;
    }

    /** 
     * Looks for the predecessor of the  predecessor of last element in the list 
     * @return the predecessor of  predecessor of the  tail element 
     */
    Node <Data>  * before_before_tail(){
      Node<Data> *last = head;
      for(int i=0;i<size-3;i++){
	last = last->next;
      }
      return last;
    }

    /** 
     * Adds an element to the tail of the list 
     * @param e the Node we want to add 
     */
    void add_at_tail(Node<Data > *e) {
#ifdef DEBUG
      std::cout<<"Adding to tail called"<<std::endl;      
#endif
      if (!head){
#ifdef DEBUG
	std::cout<<"The list is empty"<<std::endl;      
#endif
	head=e;
      }else {
#ifdef DEBUG
	std::cout<<"The list is empty"<<std::endl;      
#endif
        Node<Data> *last = tail();
        last->next = e;
	e->next= NULL;
      }
      size++;
#ifdef DEBUG
      std::cout<<"Exiting add_at_tail call"<<std::endl;      
#endif

    }


    void add(Data e) {
      add_at_tail(new Node<Data>(e));
    }

    
    /** 
     * Naive merging of the list l with the current list  
     * @param l the list to merge 
     */
    void merge(List<Data> *l) {
      if (size ==0){
	head = l->head;
	size=l->size;
	return;
      }
      Node<Data> * current = head;
      for (int i=0;i<size-1;i++){
	current = current->next;
      }
      current->next=l->head;
      size+=l->size;
    }

    /** 
     * Create a copy of the current list 
     * @return copy reference of the new list 
     */
    List<Data> * copy(){
      List<Data> * l = new List<Data>();
      Node<Data> * current = head;
      for (int i=0;i<size;i++){
        l->add_at_tail(new Node<Data>(current,SAVE));
        current= current->next;
      }
      return l;
    }

    /** 
     * Smart merging of the list l (do not merge elements with the same data) 
     * @param l the list to merge 
     */
    void merge_without_duplicates(List<Data> *l) {
      if (size ==0){
	head = l->head;
	size=l->size;
	return;
      }
      Node<Data> * current = l->head;
      for (int i=0;i<l->size;i++){
	Node<Data> * current_r = head;
	bool found = false ;
	for (int j=0;j<size;j++){
	  if (current->el==current_r->el){
	    found = true;
	    break;
	  }
	  current_r = current_r->next;
	}
	if (!found)
	  add_at_head(new Node<Data>(current->el));
	current= current->next;
      }
    }

    /** 
     * Returns the list without elements of list l 
     * @param l the list to delete elements 
     @return a new list containing the elements of the current list - elements of list l
    */
    List <Data> * set_minus(List<Data> *l) {
      List<Data> *L = new List<Data>();
      Node<Data> * current_l = head;
      for (int i=0;i<size;i++){
	Node<Data> * current_c = l->head;
	bool found =false;
	for (int j=0;j<l->size;j++){
	  if (current_c->el == current_l->el){
	    found = true;
	    break;
	  }
	  current_c=current_c->next;
	}
	if (!found)
	  L->add_at_head(new  Node<Data>(current_l->el));
	current_l = current_l->next;
      }
      return L;
    }

    /** 
     * Removes elements e from the current list 
     * @param e the element to delete 
     @return True of the element is deleted else false 
    */
    bool remove(Data e){
      Node<Data> * current = head;
      Node<Data> * last = head;
      for (int i=0;i<size;i++){
 	if (current->el == e)
	  break;
	last=current;
	current = current->next;
      }
      if (current == head) {
	head = head->next;
	size--;
	return true;
      }
      if (current == NULL)
        return false;
      last->next = current->next;
      size--;
      return true;
    }

    /** 
     * Constructor of a new list 
     */
    List(){
      head=NULL;
      size=0;
    }

    /** 
     * Delete the list
     */
    // Houssam: Need to be rewritten 
    ~List(){
    }
    
    /** 
     * Displays the list 
     */
    void display(){
      Node<Data> *temp = head;
      for (int i=0;i<size;i++) {
        temp->display();
        temp = temp->next;

      }
    }
  };
}
#endif
