#include <stdio.h>

int main() {
    unsigned char ex_array2[0x04][0x04] = {0,1,2,3,
                                            4,5,6,7,
                                            8,9,10,11,
                                            12,13,14,15};

    unsigned char ex_array1[0x16] = {0,};
    int row = 4;


    for(int i=0; i<4; i++){ //2차원 배열 -> 1차원
        for(int j=0; j<4; j++){
            ex_array1[row * i + j] = ex_array2[i][j];
        }
    }


    for(int i=0; i<4; i++){ //1차원 배열 -> 2차원
        for(int j=0; j<4; j++){
             ex_array2[i][j] = ex_array1[row * i + j];
             printf("%d ", ex_array2[i][j]);
        }
    }



    return 0;
}
