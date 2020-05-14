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

Status is_position_invalid_to_add(int position, int list_length)
{
  return position > list_length || position < 0;
}

Status insert_at(List_ptr list, Element element, int position)
{
  if(position == 0 || position == list->length)
  {
    return position == 0 ? add_to_start(list, element) : add_to_list(list, element);
  }
  Node_ptr new_node = create_node(element);
  if(is_position_invalid_to_add(position, list->length) || new_node == NULL)
  {
    return Failure;
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

Status add_unique(List_ptr list, Element element, Matcher matcher)
{
  Node_ptr p_walk = list->first;
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

Element remove_from_start(List_ptr list)
{
  if (list->length == 0) 
  {
    return NULL;
  }
  if (list->length == 1) 
  {
    Element element = list->first->element;
    list->first = NULL;
    list->last = NULL;
    list->length = 0;
    return element;
  }
  Node *first_node = list->first;
  list->first = first_node->next;
  list->length--;
  return first_node->element;
}

Element remove_from_end(List_ptr list)
{
  if(list->length == 0)
  {
    return NULL;
  }
  if(list->length == 1)
  {
    return remove_from_start(list);
  }
  Node_pair_ptr node_pair = malloc(sizeof(Node_pair));
  node_pair->current= list->first;
  Node_ptr p_walk = list->first;
  while (p_walk != NULL)
  {
    node_pair->prev = node_pair->current;
    node_pair->current = node_pair->current->next;
  }
  node_pair->prev->next = NULL;
  list->last = node_pair->prev;
  Element element = node_pair->current->element;
  free(node_pair);
  list->length--;
  return element;
}

Status is_position_invalid_to_remove(int position, int list_length)
{
  return list_length == 0 || position > list_length - 1;
}

Element remove_at(List_ptr list, int position)
{
  if(is_position_invalid_to_remove(position,list->length) || position < 0)
  {
    return NULL;
  }
  if(position == list->length - 1 || position == 0)
  {
    return position == 0 ? remove_from_start(list) : remove_from_end(list);
  }
  int length = 0;
  Node_ptr p_walk = list->first;
  while (length < position - 1)
  {
    p_walk = p_walk->next;
    length++;
  }
  Node_ptr temp = p_walk->next;
  Element element = temp->element;
  p_walk->next = temp->next;
  list->length--;
  return element;
}

Element remove_first_occurrence(List_ptr list, Element element, Matcher matcher)
{
  Node_ptr p_walk = list->first;
  int position = 0;
  while (p_walk != NULL)
  {
    if (matcher(p_walk->element, element))
    {
      return remove_at(list, position);
    }
    p_walk = p_walk->next;
    position++;
  }
  return NULL;
}


List_ptr remove_all_occurrences(List_ptr list, Element element, Matcher matcher)
{
  Node_ptr p_walk = list->first;
  int position = 0;
  List_ptr removed_elements = create_list();
  while (p_walk != NULL)
  {
    if (p_walk->element == element)
    {
      Element removed_element = remove_at(list, position);
      add_to_list(removed_elements, removed_element);
      position--;
    }
    p_walk = p_walk->next;
    position++;
  }
  return removed_elements;
}

List_ptr reverse(List_ptr list)
{
  List_ptr reversed_list = create_list();
  if (list->first == NULL)
  {
    return reversed_list;
  }
  Node_ptr p_walk = list->first;
  while(p_walk != NULL)
  {
    add_to_start(reversed_list, p_walk->element);
    p_walk = p_walk->next;
  }
  return reversed_list;
}

Status clear_list(List_ptr list)
{
  Node_ptr p_walk = list->first;
  while(p_walk != NULL){
    Node_ptr next = p_walk->next;
    free(p_walk);
    p_walk = next;
  }
  list->first = NULL;
  list->last = NULL;
  list->length = 0;
  return Success;
}