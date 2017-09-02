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
#include <string.h>
#include <ctype.h>
#include <fcntl.h>

/*Libreria C para trabajar y comparar texto (de la linea de comando)*/
#include <string.h>
/* Librerias para open y write*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


/*int funcion(int af, int bf)
{
	__m128 A1, A2, A, B, C, B1, B2, D;
	int a[4] __attribute__((aligned(16)))   = af;
	int b[4] __attribute__((aligned(16)))   = bf;
	A  = _mm_load_ps(a);
	B  = _mm_load_ps(b);
	A1 = _mm_moveldup_ps(A);
	A2 = _mm_movehdup_ps(A);
	B1 = _mm_mul_ps(A1, B);
	B2 = _mm_mul_ps(A2, B);
	C  = _mm_shuffle_ps(B2, B2, _MM_SHUFFLE(2, 3, 0, 1));
	D  = _mm_addsub_ps(B1, C);
	_mm_store_ps(a, D);

}*/
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
        return 1;
    }
    /*Se crea un loop para revisar los parametros recibidos por consola, como argc[0] es el nombre del ejecutable, se inicia en 1 para revisar del primer parametro*/
    for(int i=1; i<argc;i++)
    {
      if(strcmp(argv[i],"-o")==0 || strcmp(argv[i],"-O")==0 )
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
      if(strcmp(argv[i],"-i")==0 || strcmp(argv[i],"-I")==0 )
      {
        /*Se verifica que el argumento posterior abriendo o creando el archivo*/
        fout=open(argv[i+1], O_CREAT | O_WRONLY, 0600);
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
          perror("\n despues de [%s] se esperaba un numero mayor a cero", argv[i]);
        }
      }
    }/*Fin loop*/

    /*Se comprueba si llegaron todos los parametros obligatorios*/
    if(inputF != -1 && outputF != -1 && nElementos>0)
    {
      /*inicio de la lectura del archivo inputF*/
      c = (float *) malloc( 16 * sizeof(f));
      while((ret_in = read (input_fd, &c, 16)) > 0){
      {
        /*ERROR: Trabajar con la funcion de arriba comentada - Mientras se lee el archivo los compara y clasifica para SIMD*/
        /*inicio SIMD*/
        if(i>1 && i%2==0)
        {
          //printf("numero decimal integer %u:  %d\n", i, g);
          //printf("numero decimal integer %u:  %d\n", i, c);
          /*Comparamos el primero con el segundo o primer grupo con el segundo respectivamente*/
          if(g>c)
          {
            /*De ser mayor el primero el segundo es menor*/
            //printf("el mayor es %u\n", g);
          }
          else
          {
            /*De ser menos el primero el segundo es mayor o igual*/
            //printf("el mayor es %u\n", c);
          }

        }
        g=c;
      }


    }/*fin if*/

/*Basura para borrar despues*/

    fin = open("16inum.raw", O_RDONLY);
    if(fin == -1)
    {
      printf("\nFailed to create an open and read the file.");
      exit(1);
    }
    nElementos = 16;
    float *a;
    float floatType;
    char buffer[BUF_SIZE];      /* Character buffer */
    ssize_t ret_in, ret_out;    /* Number of bytes returned by read() and write() */

    a = (float *) malloc (nElementos * sizeof(floatType));
    b = read(fin, a, nElementos * sizeof(floatType));
    printf("buf: %9.6f \n", b);
    //}

    int input_fd, output_fd;    /* Input and output file descriptors */
    ssize_t ret_in, ret_out;    /* Number of bytes returned by read() and write() */
    char buffer[BUF_SIZE];      /* Character buffer */

    /* Are src and dest file name arguments missing */
    if(argc != 3){
        printf ("Usage: cp file1 file2");
        return 1;
    }

    /* Create input file descriptor */
    input_fd = open (argv [1], O_RDONLY);
    if (input_fd == -1) {
            perror ("open");
            return 2;
    }

    /* Create output file descriptor */
    output_fd = open(argv[2], O_WRONLY | O_CREAT, 0644);
    if(output_fd == -1){
        perror("open");
        return 3;
    }

    /* Copy process */
    while((ret_in = read (input_fd, &buffer, BUF_SIZE)) > 0){
            printf("_ %s...\n\n", output_fd);
            ret_out = write (output_fd, &buffer, (ssize_t) ret_in);
            if(ret_out != ret_in){
                /* Write error */
                perror("write");
                return 4;
            }
    }

    /* Close file descriptors */
    close (input_fd);
    close (output_fd);

    printf("Fin del programa %s...\n\n", argv[0]);

    return 0;
 }
