#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UUID_LEN 10

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

    size_t alloc_size = 10000;
    char** ids = malloc(sizeof(char*) * alloc_size);
    char* strr = malloc(sizeof(char) * UUID_LEN);

    size_t alloc_also_viewed = UUID_LEN;
    char* also_viewed = malloc(sizeof(char) * alloc_also_viewed);
    char uuid[UUID_LEN];
    int also_viewed_offset = 15;
    int uuid_offset = 11;
    const char* separators = ",";

    fp = fopen(argv[1], "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    size_t ids_real_size = 0;

    while ((read = getline(&line, &len, fp)) != -1) {
        snprintf(uuid, UUID_LEN, "%s", line + uuid_offset);
        printf("%s ", uuid);

        char* index_also_viewed = strstr(line, "also_viewed");
        if (index_also_viewed) {
            char* index_endbracket = strstr(index_also_viewed, "]");
            if (!index_endbracket)
                continue;

            char* strToken = strtok(index_also_viewed + also_viewed_offset, separators);
            if (strToken != NULL) {
                while (strToken != NULL && strToken < index_endbracket) {
                    snprintf(strr, UUID_LEN, "%s", strToken + 2);
                    printf("%s ", strr);
                    strToken = strtok(NULL, separators);
                };
            }
            else {
                snprintf(strr, UUID_LEN, "%s", index_also_viewed + 1);
                printf("%s ", strr);
            }
        }
        printf("\n");
    }

    fclose(fp);
    if (line)
        free(line);
    free(also_viewed);
    exit(EXIT_SUCCESS);
}
