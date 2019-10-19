#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

double k = 0.224;
//double step = 0.01;
//double Low = 0;
//double High = 48.08;

double func(double V, double x){
    double t = 1 + V * V;
    //printf ("pow = %lg\n", pow(t, 1.5));
    double result = -(pow(t, 1.5)) * k * x;
    return result;
}

int main()
{
    double X_max = 0, X_dY = 0, dY = 0, X_Y = 0, Y = 0, step = 0;
    int num = 0;
    printf("Input maximum x of your function: ");
    scanf("%lg", &X_max);

    printf("\nInput the known argument of y' and the value of y': ");
    scanf("%lg %lg", &X_dY, &dY);

    printf("\nInput the known argument of y and the value of y: ");
    scanf("%lg %lg", &X_Y, &Y);

    printf("\nInput the step of x: ");
    scanf("%lg", &step);

    printf("\nInput the number of points, you want to know (from x = 0): ");
    scanf("%d", &num);

    int V_size = X_max / step;
    printf("%d", V_size);
    assert (num <= V_size);

    double* V = (double*) calloc (V_size + 1, sizeof(double));

    int Vo = X_dY /step;
    V[Vo] = dY;
    printf("%lg\n", V[Vo]);

    for (double x = X_dY; x - step >= 0; x -= step){
        int i_pred = (x - step) / step;
        int i_next = x / step;
        //if (i == 0) break;
        printf("func returned %lg\n", func(V[i_next], x));
        V[i_pred] = V[i_next] - step * func(V[i_next], x);
    }

    for (double x = X_dY; x + step <= X_max; x += step){

        int i_pred = x / step;
        int i_next = (x + step) / step;
        //if (i == 0) break;
        //printf("func returned %lg\n", func(V[i_pred], x));
        V[i_next] = V[i_pred] + step * func(V[i_pred], x);
    }

    double* Y_val = (double*) calloc (V_size, sizeof(double));

    for (double x = X_Y; x - step >= 0; x -= step ){
        //printf("\nI'm in 'for' for Y down");
        int i_pred = (x - step) / step;
        int i_next = x / step;
        Y_val[i_pred] = Y_val[i_next] - step * V[i_pred];
    }

    for (double x = X_Y; x + step <= X_max; x += step){
        //printf("\nI'm in 'for' for Y up");
        int i_pred = x / step;
        int i_next = (x + step) / step;
        Y_val[i_next] = Y_val[i_pred] + step * V[i_pred];
    }

    for(int i = 0; i < num; i++)
        printf("\nOn %d step y = %lg", i, Y_val[i] * 1000);

    free(V);
    free(Y_val);
    return 0;
}
