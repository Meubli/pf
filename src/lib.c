#include <ctype.h>
#include <dirent.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void list_projects(char* path, char*** all_projects, int* length, char** ignored_dirs, size_t ignored_dirs_length, char** matches, size_t matches_length)
{
    // printf("path: %s\n", path);
    // initialize an array of strings named directories_to_process
    char** directories_to_process = malloc(1024 * sizeof(char*));
    size_t directories_to_process_length = 0;

    // opendir() returns a pointer of DIR type.
    DIR* dr = opendir(path);

    struct dirent* entry;
    struct stat info;

    if (dr == NULL) // opendir returns NULL if couldn't open directory
    {
        perror("Could not open current directory");
        return;
    }

    // Refer http://pubs.opengroup.org/onlinepubs/7990989775/xsh/readdir.html
    // for readdir()
    bool is_project = false;
    while (!is_project && (entry = readdir(dr)) != NULL) {

        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        // printf("  %s\n", full_path);
        if (stat(full_path, &info) == -1) {
            perror("could not get file info for");
            perror(full_path);
            continue;
        }

        if (S_ISDIR(info.st_mode)) {
            // printf("  is a directory\n");
            bool shoud_avoid_dir = false;
            for (size_t i = 0; i < ignored_dirs_length; i++) {
                if (strcmp(entry->d_name, ignored_dirs[i]) == 0) {
                    // printf("  should avoid directory\n");
                    shoud_avoid_dir = true;
                }
            }
            if (!shoud_avoid_dir) {
                // copy the directory to directories_to_process
                directories_to_process[directories_to_process_length] = malloc(strlen(full_path) + 1);
                strcpy(directories_to_process[directories_to_process_length], full_path);
                directories_to_process_length++;
            }
        }
        for (size_t i = 0; i < matches_length; i++) {
            if (strcmp(entry->d_name, matches[i]) == 0) {
                is_project = true;
                // printf("  found %s\n", STRINGS_TO_MATCH[i]);
            }
        }
    }

    if (is_project) {
        // printf("  %s is a project\n", path);
        (*all_projects)[*length] = strdup(path);
        (*length)++;
    } else {
        for (size_t i = 0; i < directories_to_process_length; i++) {
            // printf(" %s has to be processed\n", directories_to_process[i]);
        }

        for (size_t i = 0; i < directories_to_process_length; i++) {
            // printf("  forward on %s\n", directories_to_process[i]);
            list_projects(directories_to_process[i], all_projects, length, ignored_dirs, ignored_dirs_length, matches, matches_length);
        }
    }

    closedir(dr);
}
