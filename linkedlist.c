#include "linkedlist.h"

Node_ptr create_node(Element element)
{
  Node_ptr new_node = malloc(sizeof(Node));
  new_node->element = element;
  new_node->next = NULL;
  return new_node;
}

List_ptr create_list(void)
{
  List_ptr list = malloc(sizeof(LinkedList));
  list->last = NULL;
  list->last = NULL;
  list->length = 0;
  return list;
}

Status add_to_list(List_ptr list, Element element)
{
  Node_ptr new_node = create_node(element);
  if(new_node == NULL) 
  {
    return Failure;
  }
  new_node->element = element;
  if (list->first == NULL)
  {
    list->first = new_node;
  } 
  else 
  {
    list->last->next = new_node;
  }
  list->last = new_node;
  list->length++;
  return Success;
}

Status add_to_start(List_ptr list, Element element)
{
  Node_ptr new_node = create_node(element);
  if(new_node == NULL) 
  {
    return Failure;
  }
  if(list->first == NULL)
  {
    list->last = new_node;
  }
  new_node->next = list->first;
  list->first = new_node;
  list->length++;
  return Success;
}

Status insert_at(List_ptr list, Element element, int position)
{
  Node_ptr new_node = create_node(element);
  if(position > list->length || position < 0 || new_node == NULL)
  {
    return Failure;
  }
  if(position == 0 || position == list->length)
  {
    return position == 0 ? add_to_start(list, element) : add_to_list(list, element);
  }
  int pos = 0;
  Node_pair_ptr node_pair = malloc(sizeof(Node_pair));
  node_pair->current = list->first;
  node_pair->prev = list->first;
  while (pos < position)
  {
    node_pair->prev = node_pair->current;
    node_pair->current = node_pair->current->next;
    pos++;
  }
  new_node->next = node_pair->prev->next;
  node_pair->prev->next = new_node;
  list->length++;
  return Success;
}
