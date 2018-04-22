#include <stdio.h>

void file_Msg(const char *filename, const char *description){
    FILE *fp_in, *fp_out;
    unsigned char s[20];

    if((fp_in = fopen("C:\\Users\\kyu\\Desktop\\NSR_professional-manpower\\M01_AES\\AES_01\\AES\\example.txt", "r")) == NULL) {
        printf("Could not open this file for read \n");

        return 1;
    }

    while(fgets(s, 20, fp_in) != NULL) {
        printf(s);
    }

    if((fp_out = fopen(filename, "w")) == NULL) {
        printf("Could not open this file for read \n");

        return 1;
    }

    fprintf(fp_out, "# %s\n", description);

    fclose(fp_in);
    fclose(fp_out);
}

int main(){
    file_Msg("C:\\Users\\kyu\\Desktop\\NSR_professional-manpower\\M01_AES\\AES_01\\AES\\ttt.txt", "description");

    return 0;
}
