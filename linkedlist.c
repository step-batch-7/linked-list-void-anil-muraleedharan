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
  Node_ptr *ptr_to_set = &list->last;
  if (list->last != NULL)
  {
      ptr_to_set = &list->last->next;
  }
  (*ptr_to_set) = new_node;
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
  list->length++;
  if(list->last == NULL)
  {
    list->last = new_node;
  }
  new_node->next = list->last;
  list->last = new_node;
  return Success;
}

Status insert_at(List_ptr list, Element element, int position)
{
  Node_ptr new_node = create_node(element);
  if(position > list->length || position < 0 || new_node == NULL)
  {
    return Failure;
  }
  if(position == 0)
  {
    return add_to_start(list, element);
  }
  if(position == list->length)
  {
    return add_to_list(list, element);
  }
  int length = 0;
  Node_pair_ptr node_pair = malloc(sizeof(Node_pair));
  node_pair->current = list->last;
  node_pair->prev = list->last;
  while (length < position)
  {
    node_pair->prev = node_pair->current;
    node_pair->current = node_pair->current->next;
    length++;
  }
  new_node->next = node_pair->prev->next;
  node_pair->prev->next = new_node;
  list->length++;
  return Success;
}

Status add_unique(List_ptr list, Element element, Matcher matcher)
{
  Node_ptr p_walk = list->last;
  while (p_walk != NULL)
  {
    if(matcher(p_walk->element, element))
    {
      return Failure;
    }
    p_walk = p_walk->next;
  }
  return add_to_list(list, element);
}
