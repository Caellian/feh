#ifndef FEH_CONFIGURATION_H
#define FEH_CONFIGURATION_H

#include <stdio.h>
#include <jansson.h>

void* get(char* option);

size_t getArraySize(char *option);

unsigned char parseConfigFile(FILE configFile);

void parseObject(json_t *object, const char* base);

void parseArray(json_t *array, const char* base);

float getFileDelay(char* fileName);

#endif //FEH_CONFIGURATION_H
