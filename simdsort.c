/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   main.cpp
 * Author: juare
 *
 * Created on 24 de agosto de 2017, 23:49
 */

#include <pmmintrin.h>

/*C library to perform Input/Output operations*/
#include <stdio.h>
/*C  library Añade funciones para convertir texto a otro formato*/
#include <stdlib.h>
#include <ctype.h>
#include <fcntl.h>

/*Libreria C para trabajar y comparar texto (de la linea de comando)*/
#include <string.h>
/* Librerias para open y write*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void BitonicSortingNetwork(const __m128 a, const __m128 b, __m128 aOut, __m128 bOut)
{
    __m128 a1 = _mm_shuffle_ps(a, b, _MM_SHUFFLE(2, 0, 2, 0)); // 1357
    __m128 b1 = _mm_shuffle_ps(a, b, _MM_SHUFFLE(3, 1, 3, 1)); // 2468
    __m128 a1Min = _mm_min_ps(a1, b1);
    __m128 b1Max = _mm_max_ps(a1, b1);
    __m128 a2 = _mm_shuffle_ps(a1Min, b1Max, _MM_SHUFFLE(2, 0, 2, 0)); // 1526
    __m128 b2 = _mm_shuffle_ps(b1Max, a1Min, _MM_SHUFFLE(3, 1, 3, 1)); // 4837
    __m128 a2Min = _mm_min_ps(a2, b2);
    __m128 b2Max = _mm_max_ps(a2, b2);
    __m128 a3 = _mm_shuffle_ps(a2Min, b2Max, _MM_SHUFFLE(3, 2, 1, 0)); // 1537
    __m128 b3 = _mm_shuffle_ps(a2Min, b2Max, _MM_SHUFFLE(1, 0, 3, 2)); // 2648
    __m128 a3Min = _mm_min_ps(a3, b3);
    __m128 b3Max = _mm_max_ps(a3, b3);
    __m128 a4 = _mm_shuffle_ps(a3Min, b3Max, _MM_SHUFFLE(2, 0, 2, 0)); // 1324
    __m128 b4 = _mm_shuffle_ps(b3Max, a3Min, _MM_SHUFFLE(1, 3, 1, 3)); // 8675
    __m128 a4Min = _mm_min_ps(a4, b4);
    __m128 b4Max = _mm_max_ps(a4, b4);
    __m128 a5 = _mm_shuffle_ps(a4Min, b4Max, _MM_SHUFFLE(1, 3, 2, 0)); // 1256
    __m128 b5 = _mm_shuffle_ps(a4Min, b4Max, _MM_SHUFFLE(0, 2, 3, 1)); // 3478
    __m128 a5Min = _mm_min_ps(a5, b5);
    __m128 b5Max = _mm_max_ps(a5, b5);
    __m128 a6 = _mm_shuffle_ps(a5Min, b5Max, _MM_SHUFFLE(2, 0, 2, 0)); // 1537
    __m128 b6 = _mm_shuffle_ps(a5Min, b5Max, _MM_SHUFFLE(3, 1, 3, 1)); // 2648
    __m128 a6Min = _mm_min_ps(a6, b6);
    __m128 b6Max = _mm_max_ps(a6, b6);
    __m128 a7 = _mm_shuffle_ps(a6Min, b6Max, _MM_SHUFFLE(2, 0, 2, 0)); // 1324
    __m128 b7 = _mm_shuffle_ps(a6Min, b6Max, _MM_SHUFFLE(3, 1, 3, 1)); // 5768
    aOut = _mm_shuffle_ps(a7, a7, _MM_SHUFFLE(3, 1, 2, 0)); // 1234
    bOut = _mm_shuffle_ps(b7, b7, _MM_SHUFFLE(3, 1, 2, 0)); // 5678
}

void BitonicSortingNetworkLane(const __m128 a, const __m128 b, __m128 aOut)
{
    __m128 a1 = _mm_shuffle_ps(a, a, _MM_SHUFFLE(2, 3, 2, 3)); // 1313
    __m128 b1 = _mm_shuffle_ps(a, a, _MM_SHUFFLE(0, 1, 0, 1)); // 2828
    __m128 a1Min = _mm_min_ps(a1, b1); //1313
    __m128 b1Max = _mm_max_ps(a1, b1); //2828
    __m128 a2 = _mm_shuffle_ps(a1Min, b1Max, _MM_SHUFFLE( 1, 3, 1, 3)); // 1328
    __m128 b2 = _mm_shuffle_ps(b1Max, a1Min, _MM_SHUFFLE(0, 2, 0, 2)); // 2813
    __m128 a2Min = _mm_min_ps(a2, b2); // 1313
    __m128 b2Max = _mm_max_ps(a2, b2); // 2828
    aOut = _mm_shuffle_ps(a2Min, b2Max, _MM_SHUFFLE(0, 1, 2, 3)); // 1238
}

typedef enum bool{FALSE,TRUE}bool;

typedef struct lista
{
    int num;
    struct lista * sgte;

}lista;

void agregarNumero(lista** arreglo, int num)
{
    if((*arreglo) == NULL)
    {
        lista* nuevo = (lista*) malloc(sizeof(lista));
        nuevo->sgte = NULL;
        nuevo->num = num;
        *arreglo = nuevo;
    }

    else
    {
        lista* actual = *arreglo;

        while(actual->sgte != NULL)
        {
            actual = actual->sgte;
        }

        lista* nuevo = (lista*) malloc(sizeof(lista));
        nuevo->sgte = NULL;
        nuevo->num = num;
        actual->sgte = nuevo;
    }
}

/*Retorna el numero en esa posicion de la lista.*/
int obtenerPosicion(lista** arreglo, int num)
{
    if((*arreglo) == NULL)
    {
      return 0;
    }

    else
    {
        lista* actual = *arreglo;
        for(int i=0;i<=num; i++)
        {
          if(i==num)
          {
            return (actual->num);
          }
          if(actual->sgte == NULL)
          {
            return -1;
          }
        }

    }
    return -1;
}
/*Obtiene un arreglo con los datos del numero inicial hasta completar 16 elementos, si falta los completaran con cero */
int * obtenerSecuencia(lista** arreglo, int inicial, int largo)
{

    if((*arreglo) == NULL)
    {
      return NULL;
    }
    else
    {
      //crea el arreglo de longitud [largo]
      int os[largo];
      int j=0;
      lista* actual = *arreglo;
      for(int i=inicial;i<=(inicial+largo); i++)
      {
        if(i>=inicial)
        {
          os[j] = arreglo->num;
          arreglo = arreglo->sgte;
        }
        if(actual->sgte == NULL)
        {
          /*termina el loop y mantiene el resto de numeros con su valor defecto*/
          break;
        }
        arreglo = arreglo->sgte;
      }

    }
    return -1;
}

void mostrarNumeros(lista* arreglo)
{
    if(arreglo == NULL)
    {
        return;
    }

    while(arreglo->sgte != NULL)
    {
        printf("%d ",(arreglo->num));
        arreglo = arreglo->sgte;
    }
    printf("%d\n",(arreglo->num));
}

/*
* Funcion que imprime solo si debug es 1
*/
void print(char* str, int debug)
{
    /*Solo si debug es 1 imprime la secuencia por stdout*/
    if(debug==1)
    {
        /*fprintf( stdout, "hello world\n" );*/
        //printf( stdout, str );
    }
}
/*
 * Function principal encargada de recibir y gestionar los datos recibidos
 */
 int main(int argc, char *argv[])
 {

    /*Variables int guardan el archivo de entrada y salida respectivamente*/
    //FILE *fin, *fout;
    int inputF, outputF;
    /*Variables int guardan el numero de elementos entregados por linea de comando (argv[])*/
    int nElementos=0;

    /*Variables para la lectura y utilizacion de numeros del archivo*/
    float f;
    float *c, *g;

    /*De tener menos de 6 elementos por parametros se cancela ya que es insuficiente para iniciar*/
    if (argc<6)
    {
        perror("se esperaban mas parametros...\n");
        return 0;
    }
    /*Se crea un loop para revisar los parametros recibidos por consola, como argc[0] es el nombre del ejecutable, se inicia en 1 para revisar del primer parametro*/
    for(int i=1; i<argc;i++)
    {
      if(strcmp(argv[i],"-i")==0 || strcmp(argv[i],"-I")==0 )
      {
        /*Se verifica que el argumento posterior abriendo el archivo*/
        inputF=open(argv[i+1], O_RDONLY);
        if(inputF == -1)
        {
          perror("\nFailed to create an open the file.");
          exit(1);
        }
        //close(inputF);
      }
      if(strcmp(argv[i],"-o")==0 || strcmp(argv[i],"-O")==0 )
      {
        /*Se verifica que el argumento posterior abriendo o creando el archivo*/
        outputF=open(argv[i+1], O_CREAT | O_WRONLY, 0600);
        if(outputF == -1)
        {
          perror("\nFailed to create an open the file.");
          exit(1);
        }
        write(outputF, "hello World!\n", 13);
        //close(outputF);
      }
      if(strcmp(argv[i],"-n")==0 || strcmp(argv[i],"-N")==0 )
      {
        /*Se verifica que el argumento posterior a -n o -N sea un numero*/
        nElementos=atoi(argv[i+1]);
        if(nElementos<1)
        {
          perror("\n despues de [-n] se esperaba un numero mayor a cero");
        }
      }
    }/*Fin loop*/

    /*Se comprueba si llegaron todos los parametros obligatorios*/
    if(inputF != -1 && outputF != -1 && nElementos>0)
    {
      /*avanza en cada par, determina la posicion actual del arreglo */
      int i=(nElementos/4);
      int *j;

          //  float list[i][4] __attribute__((aligned(16)));
      int *list = (int *) malloc (sizeof(int));

      /*inicio de la lectura del archivo inputF*/
      char buffer[16];
      i=0;
      printf("\nnElementos [%u]", nElementos);

      ssize_t ret_in, ret_out;    /* Number of bytes returned by read() and write() */
      while((ret_in = read (inputF, &j, sizeof(int))) > 0)
      {
        i++;
        agregarNumero(list, j);
        if(i==10)
        {
            printf("\nLeyendo  %u:  %d  \n", i, j);
            printf("\nLeyendo  %u:  %d  \n", i, &j);
        }

      }/*Fin loop de lectura del archivo*/
      int tempe = obtenerPosicion(list, 10);
      printf("accediendo al 10mo %d  \n", tempe);
      printf("accediendo al 10mo %d  \n", &tempe);
      tempe = obtenerPosicion(list, 11);
      printf("accediendo al 11mo %d  \n", tempe);
      printf("accediendo al 11mo %d  \n", &tempe);

      /*Cerramos el archivo anteriormente abierto por que ya se encuentra almacenado y no lo usaremos mas*/
      close(inputF);

      //Guardando en procesador


      for(int i=0;i<nElementos;i=i+16)
      {
        //obtengo un arreglo de la lista, de 16 elementos
        int grupo[16]=obtenerSecuencia(list, i, 16);
        //guardo este arreglo en el procesador
        __m128i mGroup = _mm_load_ps(grupo);
        //lleno los pequeños arreglos con el grupo

        //<Ordenamiento vertical>
        //Primero creo un grupo
        __m128i a = _mm_shuffle_ps(mGroup, mGroup, _MM_SHUFFLE(0, 4, 8, 12));
        //Luego lo mando a ordenar
        BitonicSortingNetworkLane(a, a, a);

        __m128i b = _mm_shuffle_ps(mGroup, mGroup, _MM_SHUFFLE(1, 5, 9, 13));
        BitonicSortingNetworkLane(b, b, b);

        __m128i c = _mm_shuffle_ps(mGroup, mGroup, _MM_SHUFFLE(2, 6, 10, 14));
        BitonicSortingNetworkLane(c, c, c);

        __m128i d = _mm_shuffle_ps(mGroup, mGroup, _MM_SHUFFLE(3, 7, 11, 15));
        BitonicSortingNetworkLane(d, d, d);

        //<Ordenamiento horizontal>
        /*Realizo una copia de a para modificar los actuales, temp5 es para realizar las modificaciones*/
        __m128i temp1, temp2, temp3, temp4, temp5;

                                                                        //a0 a1 a2 a3
        //Rearmar a en temp1
        temp1 = a;
        temp5 = _mm_shuffle_ps(a, b, _MM_SHUFFLE(0, 0, 0, 0));          //a0 a0 b0 b0
        temp1 = _mm_shuffle_ps(temp5, temp5, _MM_SHUFFLE(0, 1, 0, 1));  //a0 b0 a0 b0
        temp5 = _mm_shuffle_ps(c, d, _MM_SHUFFLE(0, 0, 0, 0));          //c0 c0 d0 d0
        temp1 = _mm_shuffle_ps(temp1, temp5, _MM_SHUFFLE(0, 1, 0, 2));  //a0 b0 c0 d0
        //rearmar b en temp2
        temp2 = b;
        temp5 = _mm_shuffle_ps(a, b, _MM_SHUFFLE(1, 1, 1, 1));          //a1 a1 b1 b1
        temp2 = _mm_shuffle_ps(temp5, temp5, _MM_SHUFFLE(0, 1, 0, 1));  //a1 b1 a1 b1
        temp5 = _mm_shuffle_ps(c, d, _MM_SHUFFLE(1, 1, 1, 1));          //c1 c1 d1 d1
        temp1 = _mm_shuffle_ps(temp2, temp5, _MM_SHUFFLE(0, 1, 0, 2));  //a1 b1 c1 d1
        //rearmar c en temp3
        temp3 = c;
        temp5 = _mm_shuffle_ps(a, b, _MM_SHUFFLE(2, 2, 2, 2));          //a2 a2 b2 b2
        temp3 = _mm_shuffle_ps(temp5, temp5, _MM_SHUFFLE(0, 1, 0, 1));  //a2 b2 a2 b2
        temp5 = _mm_shuffle_ps(c, d, _MM_SHUFFLE(2, 2, 2, 2));          //c2 c2 d2 d2
        temp3 = _mm_shuffle_ps(temp3, temp5, _MM_SHUFFLE(0, 1, 0, 2));  //a2 b2 c2 d2
        //rearmar b en temp4
        temp4 = b;
        temp5 = _mm_shuffle_ps(a, b, _MM_SHUFFLE(3, 3, 3, 3));          //a3 a3 b3 b3
        temp4 = _mm_shuffle_ps(temp5, temp5, _MM_SHUFFLE(0, 1, 0, 1));  //a3 b3 a3 b3
        temp5 = _mm_shuffle_ps(c, d, _MM_SHUFFLE(3, 3, 3, 3));          //c3 c3 d3 d3
        temp4 = _mm_shuffle_ps(temp4, temp5, _MM_SHUFFLE(0, 1, 0, 2));  //a3 b3 c3 d3


        //devuelvo los temp a las letras
        a = temp1;
        b = temp2;
        c = temp3;
        d = temp4;

        //los Ordeno
        BitonicSortingNetworkLane(a, a, a);
        BitonicSortingNetworkLane(b, b, b);
        BitonicSortingNetworkLane(c, c, c);
        BitonicSortingNetworkLane(d, d, d);


      }
      //mList = _mm_load_ps(list);

      /*ordenamiento en vertical
      float array[4] __attribute__((aligned(16))) = { obtenerPosicion, obtenerPosicion, obtenerPosicion, obtenerPosicion};
      //guardo en registro el arreglo
      array[0] = mList[0];
      array[1] = mList[4];
      array[2] = mList[8];
      array[3] = mList[12];
      a = _mm_load_ps(array);
      BitonicSortingNetworkLane(a, a, a);
      mList[0] = a[0];
      mList[4] = a[1];
      mList[8] = a[2];
      mList[12] = a[3];

      array[0] = mList[1];
      array[1] = mList[5];
      array[2] = mList[9];
      array[3] = mList[13];
      a = _mm_load_ps(array);
      BitonicSortingNetworkLane(a, a, a);
      mList[0] = a[0];
      mList[4] = a[1];
      mList[8] = a[2];
      mList[12] = a[3];

      array[0] = mList[2];
      array[1] = mList[6];
      array[2] = mList[10];
      array[3] = mList[14];
      a = _mm_load_ps(array);
      BitonicSortingNetworkLane(a, a, a);
      mList[2] = a[0];
      mList[6] = a[1];
      mList[10] = a[2];
      mList[14] = a[3];

      array[0] = mList[3];
      array[1] = mList[7];
      array[2] = mList[11];
      array[3] = mList[15];
      a = _mm_load_ps(array);
      BitonicSortingNetworkLane(a, a, a);
      mList[3] = a[0];
      mList[7] = a[1];
      mList[11] = a[2];
      mList[15] = a[3];

      /*ordenamiento en Horizontal
      array[0] = mList[0];
      array[1] = mList[1];
      array[2] = mList[2];
      array[3] = mList[3];
      a = _mm_load_ps(array);
      BitonicSortingNetworkLane(a, a, a);
      mList[0] = a[0];
      mList[1] = a[1];
      mList[2] = a[2];
      mList[3] = a[3];

      array[0] = mList[4];
      array[1] = mList[5];
      array[2] = mList[6];
      array[3] = mList[7];
      a = _mm_load_ps(array);
      BitonicSortingNetworkLane(a, a, a);
      mList[4] = a[0];
      mList[5] = a[1];
      mList[6] = a[2];
      mList[7] = a[3];

      array[0] = mList[8];
      array[1] = mList[9];
      array[2] = mList[10];
      array[3] = mList[11];
      a = _mm_load_ps(array);
      BitonicSortingNetworkLane(a, a, a);
      mList[8] = a[0];
      mList[9] = a[1];
      mList[10] = a[2];
      mList[11] = a[3];

      array[0] = mList[12];
      array[1] = mList[13];
      array[2] = mList[14];
      array[3] = mList[15];
      b = _mm_load_ps(array);
      BitonicSortingNetworkLane(b, b, b);
      mList[12] = b[0];
      mList[13] = b[1];
      mList[14] = b[2];
      mList[15] = b[3];


    /*Ordeno las listas
    BitonicSortingNetwork(a, b, aOut, bOut);

      /*Creo las dos listas de 8 elementos
      float arrayA[8] __attribute__((aligned(16)));
      float arrayB[8] __attribute__((aligned(16)));

      arrayA[0] = mList[0];
      arrayA[1] = mList[1];
      arrayA[2] = mList[2];
      arrayA[3] = mList[3];
      arrayA[4] = mList[4];
      arrayA[5] = mList[5];
      arrayA[6] = mList[6];
      arrayA[7] = mList[7];

      a = _mm_load_ps(arrayA);

      arrayB[0] = mList[8];
      arrayB[1] = mList[9];
      arrayB[2] = mList[10];
      arrayB[3] = mList[11];
      arrayB[4] = mList[12];
      arrayB[5] = mList[13];
      arrayB[6] = mList[14];
      arrayB[7] = mList[15];

      b = _mm_load_ps(arrayB);*/




    }/*fin if*/

    close (outputF);

    return 0;
}
