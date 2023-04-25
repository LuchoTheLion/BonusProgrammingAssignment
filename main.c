#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct cache {
  int totalMissRates;
  int associativeCaching;
  int *leastRecentlyUsed;
  int sets;
  int **validArray;
  int totalHitRates;
  int size;
  char **dataArray;
  int sizeOfBlocks;
  int **tagArray;
};

void cacheCalculationFortotalHitRatess(int hexValue, struct cache *cache);

int main() {
  struct cache oneWayCacheVar;
  struct cache twoWayCacheVar;
  struct cache fourWayCacheVar;
  FILE *filePointer;
  filePointer = fopen("traces.txt", "r");

  oneWayCacheVar.size = 32;
  oneWayCacheVar.associativeCaching = 1;
  oneWayCacheVar.sets = 8;
  oneWayCacheVar.sizeOfBlocks = 4;
  oneWayCacheVar.validArray = (int **)malloc(8 * sizeof(int *));
  oneWayCacheVar.totalMissRates = 0;
  oneWayCacheVar.leastRecentlyUsed = (int *)malloc(8 * sizeof(int));
  oneWayCacheVar.dataArray = (char **)malloc(8 * sizeof(char *));
  oneWayCacheVar.totalHitRates = 0;
  oneWayCacheVar.tagArray = (int **)malloc(8 * sizeof(int *));
  memset(oneWayCacheVar.leastRecentlyUsed, 0, 8 * sizeof(int));
  for (int i = 0; i < 8; i++) {
    oneWayCacheVar.dataArray[i] = (char *)malloc(4 * sizeof(char));
    oneWayCacheVar.validArray[i] = (int *)malloc(sizeof(int));
    oneWayCacheVar.tagArray[i] = (int *)malloc(sizeof(int));
    oneWayCacheVar.tagArray[i][0] = -1;
    memset(&oneWayCacheVar.dataArray[i][0], 0, 4 * sizeof(char));
    oneWayCacheVar.validArray[i][0] = 0;
  }
  twoWayCacheVar.size = 32;
  twoWayCacheVar.associativeCaching = 2;
  twoWayCacheVar.sets = 4;
  twoWayCacheVar.sizeOfBlocks = 4;
  twoWayCacheVar.leastRecentlyUsed = (int *)malloc(4 * sizeof(int));
  twoWayCacheVar.validArray = (int **)malloc(4 * sizeof(int *));
  twoWayCacheVar.dataArray = (char **)malloc(4 * sizeof(char *));
  twoWayCacheVar.totalMissRates = 0;
  twoWayCacheVar.totalHitRates = 0;
  twoWayCacheVar.tagArray = (int **)malloc(4 * sizeof(int *));
  for (int i = 0; i < 4; i++) {
    twoWayCacheVar.dataArray[i] = (char *)malloc(4 * sizeof(char));
    twoWayCacheVar.validArray[i] = (int *)malloc(2 * sizeof(int));
    twoWayCacheVar.tagArray[i] = (int *)malloc(2 * sizeof(int));
    for (int k = 0; k < 4; k++) {
      twoWayCacheVar.tagArray[i][k] = -1;
      memset(&twoWayCacheVar.dataArray[i][k * 4], 0, 4 * sizeof(char));
      twoWayCacheVar.validArray[i][k] = 0;
    }
  }
  fourWayCacheVar.size = 32;
  fourWayCacheVar.associativeCaching = 4;
  fourWayCacheVar.sets = 2;
  fourWayCacheVar.sizeOfBlocks = 4;
  fourWayCacheVar.validArray = (int **)malloc(2 * sizeof(int *));
  fourWayCacheVar.dataArray = (char **)malloc(2 * sizeof(char *));
  fourWayCacheVar.leastRecentlyUsed = (int *)malloc(2 * sizeof(int));
  fourWayCacheVar.totalMissRates = 0;
  fourWayCacheVar.totalHitRates = 0;
  fourWayCacheVar.tagArray = (int **)malloc(2 * sizeof(int *));
  for (int i = 0; i < 2; i++) {
    fourWayCacheVar.dataArray[i] = (char *)malloc(4 * sizeof(char));
    fourWayCacheVar.validArray[i] = (int *)malloc(4 * sizeof(int));
    fourWayCacheVar.tagArray[i] = (int *)malloc(4 * sizeof(int));
    for (int k = 0; k < 4; k++) {
      fourWayCacheVar.tagArray[i][k] = -1;
      memset(&fourWayCacheVar.dataArray[i][k * 4], 0, 4 * sizeof(char));
      fourWayCacheVar.validArray[i][k] = 0;
    }
  }
  char input[9];
  for (int i = 0; i < 16; i++) {
    fscanf(filePointer, "%s", input);
    cacheCalculationFortotalHitRatess(((int)strtol(input, NULL, 16)),
                                      &oneWayCacheVar);
    cacheCalculationFortotalHitRatess(((int)strtol(input, NULL, 16)),
                                      &twoWayCacheVar);
    cacheCalculationFortotalHitRatess(((int)strtol(input, NULL, 16)),
                                      &fourWayCacheVar);
  }
  printf("Total Cache totalHitRatess: %d", oneWayCacheVar.totalHitRates);
  printf("\n");
  printf("Total Cache totalMissRateses: %d", oneWayCacheVar.totalMissRates);
  printf("\n");
  printf("Total Cache totalHitRatess: %d", twoWayCacheVar.totalHitRates);
  printf("\n");
  printf("Total Cache totalMissRateses: %d", twoWayCacheVar.totalMissRates);
  printf("\n");
  printf("Total Cache totalHitRatess: %d", fourWayCacheVar.totalHitRates);
  printf("\n");
  printf("Total Cache totalMissRateses: %d", fourWayCacheVar.totalMissRates);
  printf("\n");
}

void cacheCalculationFortotalHitRatess(int hexValue, struct cache *cache) {
  int tagArray = (hexValue / cache->sizeOfBlocks) / cache->sets;
  int currentSet = (hexValue / cache->sizeOfBlocks) % cache->sets;
  currentSet = (unsigned)((currentSet<0)?-currentSet:currentSet);
  bool nottotalHitRates = true;
  for (int i = 0; i < cache->associativeCaching; i++) {

    if (cache->tagArray[currentSet][i] == tagArray &&
        cache->validArray[currentSet][i]) {
      cache->totalHitRates += 1;
      nottotalHitRates = false;
      cache->leastRecentlyUsed[currentSet] = i;
      break;
    }
  }
  if (nottotalHitRates) {
    cache->totalMissRates += 1;
    int replacementResolutionCurrent = cache->leastRecentlyUsed[currentSet];
    for (int i = 0; i < cache->associativeCaching; i++) {
      if (!cache->validArray[currentSet][i]) {
        replacementResolutionCurrent = i;
        break;
      }
      if (cache->leastRecentlyUsed[currentSet] >
          cache->leastRecentlyUsed[currentSet + i]) {
        replacementResolutionCurrent = i;
      }
    }
    cache->leastRecentlyUsed[currentSet] = cache->leastRecentlyUsed[currentSet];
    if (replacementResolutionCurrent == cache->associativeCaching) {
      replacementResolutionCurrent = 0;
      cache->leastRecentlyUsed[currentSet] = 0;
    }
    cache->validArray[currentSet][replacementResolutionCurrent] = 1;
    memcpy(&cache->dataArray[currentSet][replacementResolutionCurrent *cache->sizeOfBlocks],
           &hexValue, cache->sizeOfBlocks * sizeof(char));
    cache->tagArray[currentSet][replacementResolutionCurrent] = tagArray;
  }
}