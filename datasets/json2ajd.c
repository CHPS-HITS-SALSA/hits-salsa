#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UUID_LEN 10

size_t pos(char* ids_str, char* id, size_t* ids_count, size_t* alloc_ids) {
    char* id_location = strstr(ids_str, id);

    if (id_location) {
        return (size_t)id_location / (UUID_LEN + 1);
    }
    else {
        if (*ids_count >= *alloc_ids) {
            *alloc_ids *= 2;
            if (!realloc(ids_str, sizeof(char) * *alloc_ids * (UUID_LEN + 1)))
                return EXIT_FAILURE;
        }
        strcat(ids_str, id);
        strcat(ids_str, " ");
    }
    return ++*ids_count;
}

int main(int argc, char* argv[argc]) {
    if (argc <= 1) {
        printf("Transform the uncleaned json data to readable adjcacency matrix\nUsage : %s "
               "<file.json>\n",
               argv[0]);
        return EXIT_FAILURE;
    }

    FILE* fp;
    char* line = NULL;
    size_t len = 0;
    int read;

    size_t alloc_ids = 10000;
    char* ids_str = malloc(sizeof(char) * alloc_ids * (UUID_LEN + 1));
    size_t ids_count = 0;
    char* strr = malloc(sizeof(char) * UUID_LEN);
    sprintf(ids_str, "%s", "");

    char uuid[UUID_LEN];
    int also_viewed_offset = 15;
    int uuid_offset = 11;
    const char* separators = ",";
    // char *uuid_location, *strr_location;

    fp = fopen(argv[1], "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        snprintf(uuid, UUID_LEN, "%s", line + uuid_offset);

        printf("%ld ", pos(ids_str, uuid, &ids_count, &alloc_ids));

        char* index_also_viewed = strstr(line, "also_viewed");
        if (index_also_viewed) {
            char* index_endbracket = strstr(index_also_viewed, "]");
            if (!index_endbracket)
                continue;

            char* strToken = strtok(index_also_viewed + also_viewed_offset, separators);
            if (strToken != NULL) {
                while (strToken != NULL && strToken < index_endbracket) {
                    snprintf(strr, UUID_LEN, "%s", strToken + 2);

                    printf("%ld ", pos(ids_str, strr, &ids_count, &alloc_ids));

                    strToken = strtok(NULL, separators);
                };
            }
            else {
                snprintf(strr, UUID_LEN, "%s", index_also_viewed + 1);

                printf("%ld ", pos(ids_str, strr, &ids_count, &alloc_ids));
            }
        }
        printf("\n");
    }

    fclose(fp);
    if (line)
        free(line);
    free(ids_str);
    free(strr);
    exit(EXIT_SUCCESS);
}
