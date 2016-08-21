#import "configuration.h"
#include "gib_hash.h"
#include "utils.h"
#include "debug.h"
#include "feh.h"
#include "filelist.h"
#include "options.h"

gib_hash *config = NULL;

void *get_config(char *option) {
    if (config != NULL) {
        return gib_hash_get(config, option);
    } else {
        return NULL;
    }
}

size_t get_config_array_size(char *option) {
    char* arrayCheck = estrjoin("", option, ".arraySize");
    if (get_config(arrayCheck) == NULL) {
        return 0;
    } else {
        return *((size_t *) get_config(arrayCheck));
    }
}

unsigned char parse_config_file(FILE* configFile) {
    // Initialize config map.
    config = gib_hash_new();

    // Create parsing error object and load file
    json_error_t *parse_error = malloc(sizeof(json_error_t));
    json_t *config_root = json_loadf(configFile, 0, parse_error);

    parse_object(config_root, "");

    return 0;
}

void parse_object(json_t *object, char *base) {
    const char *key;
    char *it_base;
    char *array_base;
    json_t *value;
    double actual;
    size_t arraySize;

    json_object_foreach(object, key, value) {
        if (strlen(base) > 0) {
            it_base = malloc((strlen(base) + 1 + strlen(key) + 1) * sizeof(char));
            sprintf(it_base, "%s.%s\0", base, key);
        } else {
            it_base = estrdup(key);
        }
        switch (json_typeof(value)) {
            case JSON_OBJECT:
                parse_object(value, it_base);
                break;
            case JSON_ARRAY:
                arraySize = json_array_size(value);
                array_base = malloc((strlen(it_base) + 1 + strlen("arraySize") + 1) * sizeof(char));
                sprintf(array_base, "%s.%s\0", it_base, "arraySize");
                gib_hash_set(config, array_base, &arraySize);
                parse_array(value, it_base);
                break;
            case JSON_STRING:
                gib_hash_set(config, it_base, (void *) json_string_value(value));
                break;
            case JSON_INTEGER:
                gib_hash_set(config, it_base, (void *) json_integer_value(value));
                break;
            case JSON_REAL:
                actual = json_real_value(value);
                void *value_pointer = malloc(sizeof(actual) + 1);
                memcpy(value_pointer, &actual, sizeof(actual));
                gib_hash_set(config, it_base, value_pointer);
                break;
            case JSON_TRUE:
            case JSON_FALSE:
                gib_hash_set(config, it_base, (void *) json_boolean_value(value));
                break;
            default:
                gib_hash_set(config, it_base, value);
                break;
        }
    }
}

void parse_array(json_t *array, char *base) {
    int index;
    const char *key;
    char *it_base;
    json_t *value;
    double actual;
    size_t arraySize;

    json_array_foreach(array, index, value) {
        key = itoa(index);
        if (strlen(base) > 0) {
            it_base = malloc((strlen(base) + 1 + strlen(key) + 1) * sizeof(char));
            sprintf(it_base, "%s.%s\0", base, key);
        } else {
            it_base = estrdup(key);
        }
        switch (json_typeof(value)) {
            case JSON_OBJECT:
                parse_object(value, it_base);
            break;
            case JSON_ARRAY:
                arraySize = json_array_size(value);
                gib_hash_set(config, estrjoin(".", it_base, "arraySize"), &arraySize);
                parse_array(value, it_base);
                break;
            case JSON_STRING:
                gib_hash_set(config, it_base, (void *) json_string_value(value));
            case JSON_INTEGER:
            case JSON_REAL:
                actual = json_number_value(value);
                void *value_pointer = malloc(sizeof(actual) + 1);
                memcpy(value_pointer, &actual, sizeof(actual));
                gib_hash_set(config, it_base, value_pointer);
            case JSON_TRUE:
            case JSON_FALSE:
                gib_hash_set(config, it_base, (void *) json_boolean_value(value));
            default:
                gib_hash_set(config, it_base, value);
        }
    }
}

float get_file_delay(char *file_path) {
    char* file_name = substr(file_path, (size_t) last_index_of(file_path, '/') + 1, strlen(file_path));
    char* file_dir = substr(file_path, 0, (size_t) last_index_of(file_path, '/'));
    char* file_dir_name = substr(file_dir, (size_t) last_index_of(file_dir, '/') + 1, strlen(file_dir));
    char* relative_path = rel_path(opt.config_file, file_path);
    char* dir_relative_path = rel_path(opt.config_file, file_dir);
    float delay = 0;
    void* check = NULL;

    // Try to use file delay
    if (relative_path != NULL) {
        char* rel_opt = malloc(sizeof(char) * (strlen("custom_delay.relative..delay") + strlen(relative_path) + 1));
        sprintf(rel_opt, "custom_delay.relative.%s.delay", relative_path);
        check = get_config(rel_opt);
        if (check != NULL) {
            delay = (float) *((double*) check);
        }
    }
    if (check == NULL) {
        char* absolute = malloc(sizeof(char) * (strlen("custom_delay.absolute..delay") + strlen(file_path) + 1));
        sprintf(absolute, "custom_delay.absolute.%s.delay", file_path);
        check = get_config(absolute);
        if (check != NULL) {
            delay = (float) *((double*) check);
        }
    }
    if (check == NULL) {
        char* named = malloc(sizeof(char) * (strlen("custom_delay.named..delay") + strlen(file_name) + 1));
        sprintf(named, "custom_delay.named.%s.delay", file_name);
        check = get_config(named);
        if (check != NULL) {
            delay = (float) *((double*) check);
        }
    }

    // Try to use directory delay
    if (dir_relative_path != NULL && check == NULL) {
        char* rel_opt = malloc(sizeof(char) * (strlen("custom_delay.relative..delay") + strlen(dir_relative_path) + 1));
        sprintf(rel_opt, "custom_delay.relative.%s.delay", dir_relative_path);
        check = get_config(rel_opt);
        if (check != NULL) {
            delay = (float) *((double*) check);
        }
    }
    if (check == NULL) {
        char* absolute = malloc(sizeof(char) * (strlen("custom_delay.absolute..delay") + strlen(file_dir) + 1));
        sprintf(absolute, "custom_delay.absolute.%s.delay", file_dir);
        check = get_config(absolute);
        if (check != NULL) {
            delay = (float) *((double*) check);
        }
    }
    if (check == NULL) {
        char* named = malloc(sizeof(char) * (strlen("custom_delay.named..delay") + strlen(file_dir_name) + 1));
        sprintf(named, "custom_delay.named.%s.delay", file_dir_name);
        check = get_config(named);
        if (check != NULL) {
            delay = (float) *((double*) check);
        }
    }

    // Try to use default delay
    if (check == NULL) {
        check = get_config("default_delay");
        if (check != NULL) {
            delay = (float) *((double*) check);
        }
    }

    return delay;
}
