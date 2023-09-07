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

//Insertar en el mapa
void insertMap(HashMap * map, char * key, void * value) {
  long index = hash(key, map->capacity);
  Pair * newPair = createPair(key, value);

  // Verificar si la clave ya existe y sobrescribir el valor
  Pair * existingPair = searchMap(map, key);
  if (existingPair != NULL) {
    existingPair->value = value;
    return;
  }

  // Insertar el nuevo par en el bucket
  map->buckets[index] = newPair;
  map->size++;

  // Actualizar el índice actual
  map->current = index;
}

void enlarge(HashMap * map) {
  enlarge_called = 1; //no borrar (testing purposes)
}


HashMap * createMap(long capacity) {
HashMap * map = (HashMap *)malloc(sizeof(HashMap));
map->buckets = (Pair **)malloc(sizeof(Pair *) * capacity);
map->size = 0;
map->capacity = capacity;
map->current = -1;
for (long i = 0; i < capacity; i++) {
  map->buckets[i] = NULL;
}
return map;

}

void eraseMap(HashMap * map,  char * key) {    


}

Pair * searchMap(HashMap * map,  char * key) {   
  long index = hash(key, map->capacity);
  Pair * pair = map->buckets[index];

  // Verificar si el bucket está vacío
  if (pair == NULL) {
    return NULL; // El bucket está vacío, la clave no existe en el mapa
  }

  // Realizar una búsqueda lineal en el bucket
  while (pair != NULL) {
    if (strcmp(pair->key, key) == 0) {
      return pair; // Se encontró la clave, devolvemos el par correspondiente
    }
    index = (index + 1) % map->capacity;
    pair = map->buckets[index]; // Avanzar al siguiente elemento en caso de colisión
  }

  return NULL; // La clave no se encontró en el bucket

}

Pair * firstMap(HashMap * map) {

    return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}
