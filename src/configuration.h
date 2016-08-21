#ifndef FEH_CONFIGURATION_H
#define FEH_CONFIGURATION_H

#include <stdio.h>
#include <jansson.h>

void* get_config(char *option);

size_t get_config_array_size(char *option);

unsigned char parse_config_file(FILE* configFile);

void parse_object(json_t *object, char *base);

void parse_array(json_t *array, char *base);

float get_file_delay(char *file_path);

#endif //FEH_CONFIGURATION_H
