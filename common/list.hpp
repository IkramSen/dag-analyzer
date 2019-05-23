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

    Node(Data e){
      el=e;
      next=NULL;
      D = -1;
      empty=false;
      t_id=-1;
      D=-1;
      O=-1;

    }


    
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

    void display(){
      el->display();
      std::cout<<"\t [Additional: t_id : "<<t_id<<",D:"<<D<<", O: "<<O<<", empty: " << (empty ? "true":"false")<<" ]"<<std::endl;
    }
  };

  template < class Data > class List {
  public:
    Node<Data > *head;
    int size;
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

    Node<Data > * get(int idx){
      if(idx>size || idx < 0){
        return NULL;
      }
      Node<Data> * obj = head;
      for(int i=0;i<idx;i++){
        obj = obj->next;
      }
      return obj;
    }

    Node <Data> * find_element(Data e){
      Node<Data> * current = head;
      for (int i=0;i<size;i++){
	if (current->el == e)
	  return current;
        current = current->next;
      }
      return NULL;
    }

    bool contains(Data e){
      Node<Data> * el = find_element(e);
      return el!=NULL;
    }


    Node <Data>  * tail(){
      Node<Data> *last = head;
      for(int i=0;i<size-1;i++){
	last = last->next;
      }
      return last;
    }


    Node <Data>  * before_tail(){
      Node<Data> *last = head;
      for(int i=0;i<size-2;i++){
	last = last->next;
      }
      return last;
    }

    Node <Data>  * before_before_tail(){
      Node<Data> *last = head;
      for(int i=0;i<size-3;i++){
	last = last->next;
      }
      return last;
    }

    

    void add_at_tail(Node<Data > *e) {
      if (!head){
        head=e;
      }else {
        Node<Data> *last = tail();
        last->next = e;
	e->next= NULL;
      }
      size++;
    }

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

    List<Data> * copy(){
      List<Data> * l = new List<Data>();
      Node<Data> * current = head;
      for (int i=0;i<size;i++){
        l->add_at_tail(new Node<Data>(current,SAVE));
        current= current->next;
      }
      return l;
    }

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

    List(){
      head=NULL;
      size=0;
    }

    ~List(){
    }

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
