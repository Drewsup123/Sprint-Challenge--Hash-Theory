#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"
#include "ex1.h"
// I had to just copy and paste the Hash table function in here

Answer *get_indices_of_item_weights(int *weights, int length, int limit)
{
  HashTable *ht = create_hash_table(16);
//   * A brute-force solution would involve two nested loops, yielding a quadratic-runtime solution. 
//   * Can we use a hash table in order to implement a solution with a better runtime?
// * Think about what we can store in the hash table in order to help us to solve this problem more efficiently. 
// * What if we store each weight in the input list as keys? What would be a useful thing to store as the value 
// for each key? 
// * If we store each weight's list index as its value, we can then check to see if the hash table 
// contains an entry for `limit - weight`. If it does, then we've found the two items whose weights 
// sum up to the `limit`!
  
  // YOUR CODE HERE
  Answer *answer = malloc(sizeof(Answer));
  for (int i = 0; i < length; i++) {
    int value = hash_table_retrieve(ht, weights[i]);
    if(value != -1) {// checks to see if key exists because retrieve gives value of -1 if it does not
      answer->index_1 = i;
      answer->index_2 = value;
      return answer;
    }else {
      hash_table_insert(ht, limit-weights[i], i);
    }
  }
  return NULL;
  // Runs in O(n) / Linear time
}

void print_answer(Answer *answer)
{
  if (answer != NULL) {
    printf("%d %d\n", answer->index_1, answer->index_2);
  } else {
    printf("NULL\n");
  }
}

LinkedPair *create_pair(int key, int value)
{
  LinkedPair *pair = malloc(sizeof(LinkedPair));
  pair->key = key;
  pair->value = value;
  pair->next = NULL;

  return pair;
}

// djb2 hash function
unsigned int hash(unsigned int x, int max) {
  x = ((x >> 16) ^ x) * 0x45d9f3b;
  x = ((x >> 16) ^ x) * 0x45d9f3b;
  x = (x >> 16) ^ x;
  return x % max;
}

void destroy_pair(LinkedPair *pair)
{
  if (pair != NULL) free(pair);
}

HashTable *create_hash_table(int capacity)
{
  HashTable *ht = malloc(sizeof(HashTable));
  ht->capacity = capacity;
  ht->storage = calloc(capacity, sizeof(LinkedPair *));

  return ht;
}

void hash_table_insert(HashTable *ht, int key, int value)
{
  unsigned int index = hash(key, ht->capacity);

  LinkedPair *current_pair = ht->storage[index];
  LinkedPair *last_pair;

  while (current_pair != NULL && current_pair->key != key) {
    last_pair = current_pair;
    current_pair = last_pair->next;
  }

  if (current_pair != NULL) {
    current_pair->value = value;
  } else {
    LinkedPair *new_pair = create_pair(key, value);
    new_pair->next = ht->storage[index];
    ht->storage[index] = new_pair;
  }
}

void hash_table_remove(HashTable *ht, int key)
{
  unsigned int index = hash(key, ht->capacity);

  LinkedPair *current_pair = ht->storage[index];
  LinkedPair *previous_pair = NULL;

  while (current_pair != NULL && current_pair->key != key) {
    previous_pair = current_pair;
    current_pair = current_pair->next;
  }

  if (current_pair == NULL) {
    fprintf(stderr, "Unable to remove entry with key: %d\n", key);
  } else {
    if (previous_pair == NULL) {  // Removing the first element in the Linked List
      ht->storage[index] = current_pair->next;
    } else {
      previous_pair->next = current_pair->next;
    }

    destroy_pair(current_pair);
  }
}

int hash_table_retrieve(HashTable *ht, int key)
{
  unsigned int index = hash(key, ht->capacity);
  LinkedPair *current_pair = ht->storage[index];

  while (current_pair != NULL) {
    if (current_pair->key == key) {
      return current_pair->value;
    }

    current_pair = current_pair->next;
  }

  return -1;
}

void destroy_hash_table(HashTable *ht)
{
  LinkedPair *current_pair;
  LinkedPair *pair_to_destroy;

  for (int i = 0 ; i < ht->capacity; i++) {
    current_pair = ht->storage[i];
    while (current_pair != NULL) {
      pair_to_destroy = current_pair;
      current_pair = current_pair->next;
      destroy_pair(pair_to_destroy);
    }
  }

  free(ht->storage);
  free(ht);
}

HashTable *hash_table_resize(HashTable *ht)
{
  HashTable *new_ht = create_hash_table(2 * ht->capacity);

  LinkedPair *current_pair;
  for (int i = 0 ; i < ht->capacity ; i++) {
    current_pair = ht->storage[i];
    while (current_pair != NULL) {
      hash_table_insert(new_ht, current_pair->key, current_pair->value);
      current_pair = current_pair->next;
    }
  }

  destroy_hash_table(ht);
  return new_ht;
}

#ifndef TESTING
int main(void)
{

  // TEST 1
  int weights_1 = {9};
  Answer *answer_1 = get_indices_of_item_weights(&weights_1, 1, 9);
  print_answer(answer_1);  // NULL

  // TEST 2
  int weights_2[] = {4, 4};
  Answer* answer_2 = get_indices_of_item_weights(weights_2, 2, 8);
  print_answer(answer_2);  // {1, 0}

  // TEST 3
  int weights_3[] = {4, 6, 10, 15, 16};
  Answer* answer_3 = get_indices_of_item_weights(weights_3, 5, 21);
  print_answer(answer_3);  // {3, 1}

  // TEST 4
  int weights_4[] = {12, 6, 7, 14, 19, 3, 0, 25, 40};
  Answer* answer_4 = get_indices_of_item_weights(weights_4, 9, 7);
  print_answer(answer_4);  // {6, 2}

  return 0;
}
#endif
