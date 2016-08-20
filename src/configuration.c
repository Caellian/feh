#import "configuration.h"
#include "gib_hash.h"
#include "utils.h"
#include "debug.h"
#include "feh.h"

gib_hash *config = NULL;

void *get(char *option) {
    if (config != NULL) {
        return gib_hash_get(config, option);
    } else {
        return NULL;
    }
}

size_t getArraySize(char *option) {
    char* arrayCheck = estrjoin("", option, ".arraySize");
    if (get(arrayCheck) == NULL) {
        return 0;
    } else {
        return *((size_t *) get(arrayCheck));
    }
}

unsigned char parseConfigFile(FILE configFile) {
    // Initialize config map.
    config = gib_hash_new();

    // Create parsing error object and load file
    json_error_t *parse_error = malloc(sizeof(json_error_t));
    json_t *config_root = json_loadf(&configFile, 0, parse_error);

    parseObject(config_root, "");

    return 0;
}

void parseObject(json_t *object, const char *base) {
    const char *key;
    json_t *value;
    double actual;
    size_t arraySize;

    json_object_foreach(object, key, value) {
        str_prepend(key, base)
        switch (json_typeof(value)) {
            case JSON_OBJECT: str_append(key, ".");
                parseObject(value, key);
                break;
            case JSON_ARRAY: str_append(key, ".");
                arraySize = json_array_size(value);
                gib_hash_set(config, estrjoin("", key, "arraySize"), &arraySize);
                parseArray(value, key);
                break;
            case JSON_STRING:
                gib_hash_set(config, key, (void *) json_string_value(value));
                break;
            case JSON_INTEGER:
                gib_hash_set(config, key, (void *) json_integer_value(value));
                break;
            case JSON_REAL:
                actual = json_real_value(value);
                void *value_pointer = malloc(sizeof(actual) + 1);
                memcpy(value_pointer, &actual, sizeof(actual));
                gib_hash_set(config, key, value_pointer);
                break;
            case JSON_TRUE:
            case JSON_FALSE:
                gib_hash_set(config, key, (void *) json_boolean_value(value));
                break;
            default:
                gib_hash_set(config, key, value);
                break;
        }
    }
}

void parseArray(json_t *array, const char *base) {
    int index;
    const char *key;
    json_t *value;
    double actual;
    size_t arraySize;

    json_array_foreach(array, index, value) {
        key = itoa(index);
        str_prepend(key, base)
        switch (json_typeof(value)) {
            case JSON_OBJECT: str_append(key, ".");
            parseObject(value, key);
            break;
            case JSON_ARRAY: str_append(key, ".");
                arraySize = json_array_size(value);
                gib_hash_set(config, estrjoin("", key, "arraySize"), &arraySize);
                parseArray(value, key);
                break;
            case JSON_STRING:
                gib_hash_set(config, key, (void *) json_string_value(value));
            case JSON_INTEGER:
                gib_hash_set(config, key, (void *) json_integer_value(value));
            case JSON_REAL:
                actual = json_real_value(value);
                void *value_pointer = malloc(sizeof(actual) + 1);
                memcpy(value_pointer, &actual, sizeof(actual));
                gib_hash_set(config, key, value_pointer);
            case JSON_TRUE:
            case JSON_FALSE:
                gib_hash_set(config, key, (void *) json_boolean_value(value));
            default:
                gib_hash_set(config, key, value);
        }
    }
}

float getFileDelay(char *fileName) {
    return 1;
}
