/*
 ============================================================================
 Name        : sp_linux_copy.c
 Author      : Marko Martinović
 Description : Copy input file into output file

 compile: gcc test.c -o test
 Execute: ./test 16inum.raw test
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX(a,b) ((a) > (b) ? a : b)
#define MIN(a,b) ((a) < (b) ? a : b)
//#define BUF_SIZE 8192

int main(int argc, char* argv[]) {

    int input_fd, output_fd;    /* Input and output file descriptors */
    ssize_t ret_in, ret_out;    /* Number of bytes returned by read() and write() */

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

    /* Copy process */
    /*while((ret_in = read (input_fd, &buffer, BUF_SIZE)) > 0){
    while((ret_in = read (input_fd, &f, sizeof(f))) > 0){
    */
    float f;
    float *c, *g;
    c = (float *) malloc( 16 * sizeof(f));
    int i=0;
    //while((ret_in = read (input_fd, &c, sizeof(f))) > 0){
      //while((ret_in = read (input_fd, &c, 4)) > 0){
        while((ret_in = read (input_fd, &c, 16)) > 0){
        i++;
            //printf("numero %u:  %p\n", i, c);
            /*printf("numero float %u:  %f\n", i, c);
            printf("numero Float %u:  %F\n", i, c);
            printf("numero Char %u:  %c\n", i, c);*/
            //printf("numero decimal integer %u:  %d\n", i, c);


            //printf("%f\n", f);
            /*printf("called read(%d, c, 10), which read %f bytes.\n", input_fd, ret_in);*/
            if(i>1 && i%2==0)
            {
              //printf("numero decimal integer %u:  %d\n", (i-1), g);
              printf("numero decimal integer %u:  %d\n", i, g);
              printf("numero decimal integer %u:  %d\n", i, c);
              if(g>c)
              {
                printf("el mayor es %u\n", g);
              }
              else
              {
                printf("el mayor es %u\n", c);
              }

            }
            g=c;
            //g==c;

    }

    /* Close file descriptors */
    close (input_fd);

    return (EXIT_SUCCESS);
}
