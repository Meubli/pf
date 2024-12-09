#include "lib.c"
#include <assert.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

// comma separated environment variables
#define PROJECT_FINDER_IGNORES "PROJECT_FINDER_IGNORES"
#define PROJECT_FINDER_MATCHES "PROJECT_FINDER_MATCHES"

size_t STRINGS_TO_MATCH_LENGTH = 6;
char* STRINGS_TO_MATCH[256] = {
    ".git",
    "pom.xml",
    "package.json",
    "Makefile",
    "build.zig",
    "composer.json",
    "Cargo.toml",
};
size_t DIRECTORIES_TO_AVOID_LENGTH = 9;
char* DIRECTORIES_TO_AVOID[256] = {
    ".",
    "..",
    "node_modules",
    ".git",
    "target",
    "build",
    "vendor",
    ".metadata",
    ".idea",
    ".plugins",
};

char** str_split(char* a_str, const char a_delim, size_t* count)
{
    char** result = 0;
    char* tmp = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp) {
        if (a_delim == *tmp) {
            (*count)++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    *count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    // (*count)++;

    result = malloc(sizeof(char*) * *count);

    if (result) {
        size_t idx = 0;
        char* token = strtok(a_str, delim);

        while (token) {
            assert(idx < *count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        // assert(idx == *count - 1);
        // *(result + idx) = 0;
    }

    return result;
}

void manage_array(char*** array, size_t* length, char* element, size_t default_size, char* default_strings[])
{
    char* project_finder_matches_env = getenv(element);
    if (project_finder_matches_env == NULL) {
        for (int i = 0; i < default_size; i++) {
            (*array)[i] = default_strings[i];
        }
        *length = default_size;
    } else {
        (*array) = str_split(project_finder_matches_env, ',', length);
        if (!*array) {
            printf("Error allocating array\n");
        }
    }
}

int main(int argc, char* argv[])
{

    if (argc < 2) {
        printf("Usage: %s <path1> <path2> ...\n", argv[0]);
        return 1;
    }

    char** all = malloc(1024 * sizeof(char*));
    int total = 0;

    // manage ignores
    char** project_finder_ignores = malloc(256 * sizeof(char*));
    size_t project_finder_ignores_length = 0;
    manage_array(&project_finder_ignores, &project_finder_ignores_length, PROJECT_FINDER_IGNORES, DIRECTORIES_TO_AVOID_LENGTH, DIRECTORIES_TO_AVOID);

    // manage matches
    char** project_finder_matches = malloc(256 * sizeof(char*));
    size_t project_finder_matches_length = 0;
    manage_array(&project_finder_matches, &project_finder_matches_length, PROJECT_FINDER_MATCHES, STRINGS_TO_MATCH_LENGTH, STRINGS_TO_MATCH);

    for (int i = 1; i < argc; i++) {
        list_projects(argv[i], &all, &total, project_finder_ignores, project_finder_ignores_length, project_finder_matches, project_finder_matches_length);
    }

    for (size_t i = 0; i < total; i++) {
        printf("%s\n", all[i]);
        free(all[i]);
    }
    free(all);
    free(project_finder_ignores);
    free(project_finder_matches);
    return 0;
}
