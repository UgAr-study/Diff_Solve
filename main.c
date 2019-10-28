#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

// for P = 23.3H, a = 1.88 cm, b = 1.08 cm, E = 10 * 10^9
double k = 0.583;
double kostil = 0.000001;

double func(double V, double x){
    double t = 1 + V * V;
    double result = -(pow(t, 1.5)) * k * x;
    return result;
}

void Input(double* X_max, double* X_dY, double* dY, double* X_Y, double* Y, double* step, int* num){

    printf("Input maximum x of your function: ");
    scanf("%lg", X_max);

    printf("\nInput the known argument of y' and the value of y': ");
    scanf("%lg %lg", X_dY, dY);

    printf("\nInput the known argument of y and the value of y: ");
    scanf("%lg %lg", X_Y, Y);

    printf("\nInput the step of x: ");
    scanf("%lg", step);

    printf("\nInput the number of points, you want to know (from x = 0): ");
    scanf("%d", num);
}

void fill_V(double* V, int V_size, double X_dY, double step, double dY){

    int Vo = (int)(X_dY /step + kostil);
    V[Vo] = dY;
    printf("%lg\n", V[Vo]);

    for (double x = X_dY; x / step + 1 < V_size; x += step){


        int i_pred = (int)(x / step + kostil);
        int i_next = (int)(x / step + 1 + kostil);

        printf("\ni_pred = %d\n", i_pred);
        printf("\ni_next = %d\n", i_next);

        V[i_next] = V[i_pred] + step * func(V[i_pred], x);
    }
}

void fill_Y (double* Y_val, double* V, double step, double X_Y, double X_dY, double X_max, double Y){

    Y_val[(int)((X_Y / step) + kostil)] = Y;
    //double t = (*Y_val)[(int)((X_Y / step) + kostil)];
    printf("/////%lg\\\\\\", Y_val[(int)((X_Y / step) + kostil)]);

    for (double x = X_Y; x >= X_dY; x -= step){

        int i_pred = (int) (x / step - 1 + kostil);
        int i_next = (int) (x / step + kostil);
        Y_val[i_pred] = Y_val[i_next] - step * V[i_pred];
    }

    for (double x = X_Y; x >= X_dY; x -= step){

        int j = (int) (x / step + kostil);
        int i = (int) ((X_max - x) / step + kostil);
        Y_val[i] = Y_val[j];
    }
}

void Write(double* Y_val, int num){

    FILE * Laba_1_3_1 = fopen ("Laba_1_3_1.txt", "w");

    for(int i = 0; i <= num; i++)
        fprintf(Laba_1_3_1, "%.3lg ", Y_val[i] * 1000);

    fclose(Laba_1_3_1);
}

void ReWrite(double* Y_val){

    printf("Before opening");
    FILE * Laba_1_3_1 = fopen ("Laba_1_3_1.txt", "r+b");
    printf("I'v open file");

    int size_of_file = 0;

    if (Laba_1_3_1 == NULL) printf("Error of file\n");

    else{
        fseek (Laba_1_3_1, 0, SEEK_END);
        size_of_file = ftell (Laba_1_3_1);
        fseek (Laba_1_3_1, 0, SEEK_SET);
    }

    char* text = (char*) calloc ((++size_of_file), sizeof(char));
    assert (text != NULL);

    size_t length = fread (text, sizeof(char), size_of_file, Laba_1_3_1);
    assert (size_of_file == length + 1);

    fseek (Laba_1_3_1, 0, SEEK_SET);

    for (int i = 0; i < size_of_file; i++)
        if(text[i] == '.') text[i] = ',';

    for (int i = 0; i < size_of_file; i++)
        fprintf(Laba_1_3_1, "%c", text[i]);

    free(text);
    fclose(Laba_1_3_1);
}

int main()
{
    double X_max = 0.48, X_dY = 0.24, dY = 0, X_Y = 0.48, Y = 0, step = 0.01;
    int num = 48;

    //Input(&X_max, &X_dY, &dY, &X_Y, &Y, &step, &num);

    int V_size = (int)(X_max / step) + 1;
    printf("%d\n", V_size);
    assert (num <= V_size);

    double* V = (double*) calloc (V_size + 1, sizeof(double));

    fill_V(V, V_size, X_dY, step, dY);

    double* Y_val = (double*) calloc (V_size, sizeof(double));

//    for(int i = 0; i < V_size; i++)
//        printf("V[%d] = %lg\n", i, V[i]);

    fill_Y(Y_val, V, step, X_Y, X_dY, X_max, Y);

    Write(Y_val, num);
    ReWrite(Y_val);
//    for(int i = 0; i <= num; i++)
//        printf("\nOn %d step y = %.3lg", i, Y_val[i] * 1000);

    free(V);
    free(Y_val);
    return 0;
}
