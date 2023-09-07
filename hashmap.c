#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap * map, char * key, void * value) {
 
  long index = hash(key, map->capacity);

  // Verificar si el bucket ya tiene elementos
  if (map->buckets[index] == NULL) {
      // Si el bucket está vacío, creamos un arreglo dinámico para almacenar los pares
      map->buckets[index] = (Pair **)malloc(sizeof(Pair *) * INITIAL_BUCKET_SIZE);
      for (int i = 0; i < INITIAL_BUCKET_SIZE; i++) {
          map->buckets[index][i] = NULL;
      }
  }

  // Verificar si la clave ya existe en el bucket
  for (int i = 0; map->buckets[index][i] != NULL; i++) {
      if (strcmp(map->buckets[index][i]->key, key) == 0) {
          // Si la clave ya existe, sobrescribe el valor y sale de la función
          map->buckets[index][i]->value = value;
          return;
      }
  }

  // Si la clave no existe en el bucket, buscamos un espacio vacío en el arreglo dinámico
  int position = 0;
  while (map->buckets[index][position] != NULL) {
      position++;
  }

  // Creamos un nuevo par y lo insertamos en el espacio vacío
  Pair * newPair = createPair(key, value);
  map->buckets[index][position] = newPair;
  map->size++;

}

void eraseMap(HashMap * map,  char * key) {    
  

}

Pair * searchMap(HashMap * map,  char * key) {   


    return NULL;
}

Pair * firstMap(HashMap * map) {

    return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}
