#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc) {
    if (argc > 1) return 22; 

    char *rm_call = "rm ";
    char *ln_call = "ln -s ";
    char src[PATH_MAX]; 
    if (getcwd(src, sizeof(src)) == NULL) return 1;
    char *dest = strcat(getenv("HOME"), "/quick-access");
    char *delete_command = (char *)malloc((strlen(rm_call) + strlen(dest)));
    char *create_command = (char *)malloc((strlen(ln_call) + strlen(src) + 
                strlen(dest) + 7) * sizeof(char));

    *delete_command = *strcpy(delete_command, rm_call);
    *delete_command = *strcat(delete_command, " ");
    *delete_command = *strcat(delete_command, dest);

    *create_command = *strcpy(create_command, ln_call);
    *create_command = *strcat(create_command, " ");
    *create_command = *strcat(create_command, src);
    *create_command = *strcat(create_command, " ");
    *create_command = *strcat(create_command, dest);
        
    // Check if link already exists; then delete
    if (!access(dest, F_OK)) {
        int rm_status = system(delete_command);
    }

    // Check if link really does not exist; then create new link
    if (access(dest, F_OK)) {
        int ln_status = system(create_command);

        if (!ln_status) {
            printf("Link created \033[0;36m%s", dest);
            printf(" \033[0m->");
            printf(" \033[0;34m%s\033[0m\n", src);
        }

        return ln_status;
    }

    return 1;
}
