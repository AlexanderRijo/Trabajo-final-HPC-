#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include <time.h>
#include <unistd.h> 
#include <omp.h> 

main()
{

    
    double time_spent = 0.0;
 
    clock_t begin = clock();
    
       int i,j;
       int a[6][6];
       srand (time (0)); // Toma el tiempo como semilla, genera un número diferente cada vez
      
    
        #pragma omp parallel for 
        {
           for(i=0;i<6;i++)
           {   
             for(j=0;j<6;j++)
             // 0/1 generado aleatoriamente
             a [i] [j] = 0 + rand ()% 2; 
            }
        }

        #pragma omp parallel for 
        {
           for(i=0;i<6;i++)
            for(j=0;j<6;j++)
           {
               if(a[i][j]==1)
             a[i][j]=i*6+j+1;
            }
        }
            printf ("Generar puntos de objeto aleatoriamente: \n");

        
         #pragma omp parallel for 
        {
            for(i=0;i<6;i++)
            for(j=0;j<6;j++)
            {
              if(j!=5)
              printf(" %02d  ",a[i][j]);
              else
             printf(" %02d  \n",a[i][j]);
            }
        }
            printf("\n");printf("\n");
        

    
       
    int x [2] = {1,1}; // Seleccione dos puntos iniciales de antemano
    int y[2]={4,4};
    int x1,x2,y1,y2;    
    
    int d1 [36] = {0}; // La distancia entre los puntos de paso se divide en dos matrices agregadas
    int d2[36]={0};
    int k=0;
    int l=0;

    #pragma omp parallel for 
        {
          for(i=0;i<6;i++)
             for(j=0;j<6;j++)
             {
                 if(a[i][j]!=0)
                 {
                     if(sqrt((i-x[0])*(i-x[0])+(j-x[1])*(j-x[1]))<sqrt((i-y[0])*(i-y[0])+(j-y[1])*(j-y[1]))){
                     d1[k]=a[i][j];
                     k++;
                 }
                     else
                    {
                     d2[l]=a[i][j];
                     l++;
                    }
                 }
             }
        }
    printf ("Clasifica en dos matrices agregadas a traves de dos puntos iniciales: \n");
    printf ("Matriz uno:");

    #pragma omp parallel for 
        {
           for(i=0;i<k;i++)
            printf("%d  ",d1[i]);
            printf("\n");
            printf ("Matriz dos:");
            for(i=0;i<l;i++)
            printf("%d  ",d2[i]);
        }
     
 

     printf("\n");
    int o=0;int p=0;
    int q; // Número de línea de cada punto
 #pragma omp parallel for 
        {
          for(i=0;i<k;i++)
          {
            q=(d1[i]-1)/6;
            o=q+o;
           p=d1[i]-q*6-1+p;
          } 
             x[0]=o/k;x[1]=p/k;
             o=0;p=0; 
           for(i=0;i<l;i++){
           q=(d2[i]-1)/6;
           o=q+o;
           p=d2[i]-q*6-1+p;
           } 
        }
    y[0]=o/l;y[1]=p/l;
    printf("\n");printf("\n");
    printf ("Dos puntos de coordenadas recien generados basados en los valores centrales de las dos matrices ordenadas: \n");
    printf("%d, %d   ",x[0],x[1]);
    printf("%d, %d \n\n",y[0],y[1]);
    
    
    while(1){
    x1=x[0];x2=x[1];y1=y[0];y2=y[1];
        for(i=0;i<36;i++){
        d1[i]=0;d2[i]=0;}
        k=0;
        l=0;
        for(i=0;i<6;i++)
             for(j=0;j<6;j++){
                 if(a[i][j]!=0){
                     if(sqrt((i-x[0])*(i-x[0])+(j-x[1])*(j-x[1]))<sqrt((i-y[0])*(i-y[0])+(j-y[1])*(j-y[1]))){
                     d1[k]=a[i][j];
                     k++;
                 }
                     else{
                     d2[l]=a[i][j];
                     l++;
                 }
                 }
             }
           o=0;p=0;q=0;
           for(i=0;i<k;i++){
        q=(d1[i]-1)/6;
        o=q+o;
        p=d1[i]-q*6-1+p;
    } 
    x[0]=o/k;x[1]=p/k;
    o=0;p=0;q=0; 
     for(i=0;i<l;i++){
        q=(d2[i]-1)/6;
        o=q+o;
        p=d2[i]-q*6-1+p;
    } 

    y[0]=o/l;y[1]=p/l;
    printf ("Dos puntos de coordenadas recien generados basados en los valores centrales de las dos matrices ordenadas: \n");
    printf("%d, %d   ",x[0],x[1]);
    printf("%d, %d \n\n",y[0],y[1]);    

    if(x1==x[0] && x2==x[1] && y1==y[0] && y2==y[1])
    {
    printf ("Se han encontrado los dos ultimos puntos de coordenadas! \n");
    printf (" \n");
        break;
    }
    }

         sleep(3);
    clock_t end = clock();
 
    // calcula el tiempo transcurrido encontrando la diferencia (end - begin) y
    // dividiendo la diferencia por CLOCKS_PER_SEC para convertir a segundos
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
 
    printf("El tiempo de ejecucion es  %f segundos", time_spent);
    printf (" \n \n");
 
    system("pause");

}