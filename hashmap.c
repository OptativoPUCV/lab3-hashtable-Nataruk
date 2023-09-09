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
  if (map == NULL || key == NULL) {
      return;  // Verificar entradas inválidas
  }

  long index = hash(key, map->capacity);
  Pair * newPair = createPair(key, value);

  if (map->buckets[index] == NULL) {
    // Si el bucket está vacío, simplemente inserta el nuevo par
    map->buckets[index] = newPair;
  } else {
    // Si el bucket está ocupado debido a una colisión, busca el próximo bucket vacío
    long nextIndex = (index + 1) % map->capacity;
    while (nextIndex != index) {
      if (map->buckets[nextIndex] == NULL) {
        // Se encontró un bucket vacío, inserta el nuevo par aquí
        map->buckets[nextIndex] = newPair;
        break;
      }
      // Intenta el siguiente bucket en el ciclo
      nextIndex = (nextIndex + 1) % map->capacity;
    }

      
      
  }

  map->size++;
  map->current = index;
}

void enlarge(HashMap * map) {
  enlarge_called = 1; //no borrar (testing purposes)
  if (map == NULL) {
    return; // Verificar entrada inválida
  }

  // Guardar la información de la tabla actual
  Pair ** oldBuckets = map->buckets;
  long oldCapacity = map->capacity;

  // Calcular la nueva capacidad (por ejemplo, duplicarla)
  long newCapacity = oldCapacity * 2;

  // Crear una nueva tabla con la nueva capacidad
  Pair ** newBuckets = (Pair **)malloc(sizeof(Pair *) * newCapacity);

  if (newBuckets == NULL) {
    // Manejar el error de asignación de memoria, si es necesario
    return;
  }

  // Inicializar los nuevos buckets como nulos
  for (long i = 0; i < newCapacity; i++) {
    newBuckets[i] = NULL;
  }

  // Transferir los pares clave-valor de la tabla actual a la nueva tabla
  for (long i = 0; i < oldCapacity; i++) {
    if (oldBuckets[i] != NULL) {
      long newIndex = hash(oldBuckets[i]->key, newCapacity);
      newBuckets[newIndex] = oldBuckets[i];
    }
  }

  // Actualizar la estructura del mapa con la nueva información
  map->buckets = newBuckets;
  map->capacity = newCapacity;

  // Liberar la memoria de la tabla anterior (oldBuckets)
  free(oldBuckets);
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
  if((map == NULL)&&(key == NULL)){
    return;
  } 
  long index = hash(key, map -> capacity);

  while ((map -> buckets[index] != NULL) && ((map -> buckets[index] -> key == NULL)  (strcmp(map -> buckets[index] -> key, key) != 0))){
    index = (index + 1) % map -> capacity;
  }
    

  if ((map -> buckets[index] != NULL) && (map -> buckets[index] -> key != NULL) && (strcmp(map -> buckets[index] -> key, key) == 0)){
    map -> buckets[index] -> key = NULL;
    map -> size--;
  }
}

Pair * searchMap(HashMap * map,  char * key) {

  if((map == NULL)  (key == NULL)) return NULL;
  long index = hash(key, map -> capacity);

  while ((map -> buckets[index] != NULL) && ((map -> buckets[index] -> key == NULL)  (strcmp(map -> buckets[index] -> key, key) != 0))) index = (index + 1) % map -> capacity;

   if ((map -> buckets[index] != NULL) && (map -> buckets[index]->key != NULL) && (strcmp(map -> buckets[index] -> key, key) == 0)){
        map -> current = index;
        return map -> buckets[index];
    } else return NULL;
}
}

Pair * searchMap(HashMap * map,  char * key) {   
  if (map == NULL || key == NULL) {
    return NULL;  // Verificar entradas inválidas
  }

  long index = hash(key, map->capacity);

  if (map->buckets[index] != NULL) {
    // Si el bucket no está vacío, verifica si la clave coincide
    if (is_equal(map->buckets[index]->key, key)) {
      // La clave coincide, actualiza el índice actual y devuelve el valor correspondiente
      map->current = index;
      return map->buckets[index];
  } else {
    // La clave no coincide, busca en los siguientes buckets (si hay colisiones)
    long nextIndex = (index + 1) % map->capacity;
    while (nextIndex != index) {
      if (map->buckets[nextIndex] != NULL && is_equal(map->buckets[nextIndex]->key, key)) {
        // Se encontró la clave en un bucket posterior, actualiza el índice actual y devuelve el valor correspondiente
        map->current = nextIndex;
        return map->buckets[nextIndex];
      }
      // Intenta el siguiente bucket en el ciclo
      nextIndex = (nextIndex + 1) % map->capacity;
    }
  }
}

  // La clave no se encontró en ningún bucket, así que no se actualiza el índice actual
  return NULL;
}

Pair * firstMap(HashMap * map) {
  if (map == NULL) {
        return NULL;  // Verificar entrada inválida
    }

    map->current = -1; // Restablecer el índice actual

    // Iterar a través de los buckets para encontrar el primer par clave-valor no nulo
    for (long index = 0; index < map->capacity; index++) {
        if (map->buckets[index] != NULL) {
            map->current = index; // Actualizar el índice actual
            return map->buckets[index];
        }
    }

    // No se encontraron pares clave-valor en el mapa
    return NULL;
}

Pair * nextMap(HashMap * map) {
  if (map == NULL || map->current == -1) {
        return NULL; // Verificar entrada inválida o ningún elemento previamente accedido
    }

    // Comenzar desde el siguiente índice después del último elemento accedido
    long currentIndex = map->current + 1;

    // Buscar el siguiente par clave-valor no nulo
    for (long nextIndex = currentIndex; nextIndex < map->capacity; nextIndex++) {
        if (map->buckets[nextIndex] != NULL) {
            map->current = nextIndex; // Actualizar el índice actual
            return map->buckets[nextIndex];
        }
    }

    // No se encontraron más pares clave-valor en el mapa
    map->current = -1; // Restablecer el índice actual
    return NULL;
}
