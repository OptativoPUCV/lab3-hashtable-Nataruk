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
    Pair * newPair = createPair(key, value);

    // Verificar si el bucket ya tiene elementos
    if (map->buckets[index] == NULL) {
        // Si el bucket está vacío, simplemente asigna el nuevo par
        map->buckets[index] = newPair;
    } else {
        // Si el bucket ya tiene elementos, crea una tabla hash secundaria si aún no existe
        if (map->buckets[index]->value == NULL) {
            map->buckets[index]->value = createMap(map->capacity);
        }

        // Inserta el nuevo par en la tabla hash secundaria
        insertMap(map->buckets[index]->value, key, value);
    }

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
