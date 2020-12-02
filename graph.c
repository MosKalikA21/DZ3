#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

int** create_array(int n) {
    int ** arr = malloc(sizeof(int*) * n);
    for(int i = 0; i < n; i++){
       arr[i] = malloc(sizeof(int)*n);
      for(int j = 0; j < n; j++) {
         arr[i][j] = 0;
      }
    }
    return arr;    
}

void free_array(int n, int** b) {
   for(int i = 0; i < n; i++){
         free(b[i]);
   }
   free(b);

}

void print_graph(int n, int** arr) {
    int i = 0; int j = 0; 
    printf("Матрица смежности:\n");
    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++){
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

void print_dot(int n, int** arr) {        
    FILE* f = fopen("graph.dot", "w");    // открытие файла graph.dot,   "w"=write
    fprintf(f, "graph{\n");
    printf("graph{\n");                   // реализовываем вид, который будет понятен, для Graphviz,          
    int i = 0; int j = 0;  int m = 0;               // который содержит такой синтаксис: graph{
    for (i = 0; m < n; m++){                       //                                      0--1;
       printf("%d ", m);                          //                                     и т.д.
       fprintf(f, "%d ", m);                     //                                          }                        
            }
            printf("\n");
    for (i = 0; i < n; i++){              
        for (j = i; j < n; j++){          
                for (int m = 0; m < arr[i][j]; m++){         
            printf("%d -- %d;\n", i, j);
            fprintf(f, "%d -- %d;\n", i, j);
        }
    }
    } 
    printf("}\n");
    fprintf(f, "}\n");
    fclose(f);
}
void connected(int n, int r, int** arr){
    int k = 0;
    for (int i = 0; i < n; i++){              
        for (int j = 0; j < n; j++){ 
            if (arr[i][j] > 1){   
                k = k + 1;
            }
            if (i==j && arr[i][j] == 1){
                k = k + 1;
            }
        }
    }
    printf ("%d\n", k);
        if(k > 0){
            printf("Граф имеет кратные ребра и петли. Теорему применить нельзя!\n");
        }
        else {
            printf("Граф не имеет кратные ребра и петли. Можно применить теорему!\n");
        }
    if(k == 0){
        if (r < ((n - 1) * (n - 2)) / 2) {
            printf("Граф несвязный, теорема не работает\n");  
        } 
        else {
            printf("Граф связный, теорема работает\n");   
        }
    }
}

int main()
{   setlocale(LC_ALL, "RUS");
    int n; int j; int r; int a1; int a2; 
    printf("Введите количество вершин:");
    scanf("%d", &n);                      
    printf("Введите количество ребер:");   
    scanf("%d", &r);
    int** arr = create_array(n);
    printf("Введите вершины, которые нужно соединить в качестве ребер:\n");
            for (int i = 0; i < r; i++){
        scanf(" %d" "%d", &a1, &a2);
               arr[a1][a2] += 1;
               arr[a2][a1] += 1;    
        if(a1 == a2){
            arr[a1][a2] -=1;
        }       
}
    
    print_graph(n, arr);
    print_dot(n, arr);
    connected(n,r, arr);
    
    printf("Добавляем новую вершину!\n");
    int** arr2 = create_array(n + 1);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            arr2[i][j] = arr[i][j];
         }
    }
    
    free_array(n, arr);
    arr = arr2;
    print_graph(n + 1, arr);
    printf("Сколько раз вы будете соединять новую вершину?\n");
    scanf("%d", &r);
    printf("Введите вершины, с которыми хотите соединить в качестве ребер:\n");
    for (int i = 0; i < r; i++){
       scanf(" %d", &a2);
       arr[n][a2] += 1;
       arr[a2][n] += 1;  
       if(n == a2){
            arr[n][a2] -=1;
        } 
    }
    
    print_graph(n + 1, arr);
    print_dot(n + 1, arr);
    free_array(n + 1, arr);
    return 0;
    }
