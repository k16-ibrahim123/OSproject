#include<stdio.h> 

#include<stdlib.h> 

#include<unistd.h> 

#include<sys/types.h> 

#include<string.h> 

#include<sys/wait.h>

int main()

{

    int fd1[2];  // Used to store two ends of first pipe 

    int fd2[2];  // Used to store two ends of second pipe 

  int m, n,q,r,i,j, k, sum = 0;

   pid_t p;  

    if (pipe(fd1)==-1) 

    { 

        fprintf(stderr, "Pipe Failed"); 

        return 1; 

    } 

    if (pipe(fd2)==-1) 

    { 

        fprintf(stderr, "Pipe Failed" ); 

        return 1; 

    } 

  printf("Enter number of rows and columns of first matrix\n");

  scanf("%d%d", &m, &n);

  printf("Enter number of rows and columns of second matrix\n");

  scanf("%d%d", &q, &r);

  if(m!=q || n!=r){

    printf("The matrices can't be added with each other.\n");

    exit(0);}  

  int first[m][n], add[m][n];

  printf("Enter elements of first matrix\n");

  for (i = 0; i < m; i++)

    for (j = 0; j < n; j++)

    scanf("%d", &first[i][j]);

    p = fork(); 

    if (p < 0) 

    { 

        fprintf(stderr, "fork Failed" ); 

        return 1; 

    } 

    else if (p > 0)  //parent process 

    {  

        close(fd1[0]);  // Close reading end of first pipe 

  

        // Write input matrix values and close writing end of first 

        // pipe. 

        write(fd1[1], first, 100); 

        close(fd1[1]); 

  

        // Wait for child to send an array 

        wait(NULL); 

  

        close(fd2[1]); // Close writing end of second pipe 

  

        // Read an array from child, print it and close 

        // reading end. 

        read(fd2[0],add,100); 

         printf("Addition of the matrices:\n");

    for (i = 0; i < m; i++) {

    for (j = 0; j < n; j++)

      printf("%d\t", add[i][j]);

     printf("\n");

  } 

        close(fd2[0]);

        close(fd1[0]); 

    }

  else{

  	int second[q][r];

    printf("Enter elements of second matrix\n");

    for (i = 0; i < q; i++)

    for (j = 0; j < r; j++)

    scanf("%d", &second[i][j]); 

    close(fd1[1]);  // Close writing end of first pipe 

        // Read an array using first pipe 

        read(fd1[0],first,100); 

        // addition two matrices 

        for (i = 0; i < q; i++) {

      for (j = 0; j < r; j++) {

          sum = first[i][j]+second[i][j];

        add[i][j] = sum;

        sum = 0;}      

    }

    // Close both reading ends 

    close(fd1[0]); 

    close(fd2[0]); 

    // Write addition matrix and close writing end 

    write(fd2[1],add,100); 

    close(fd2[1]); 

   exit(0); 

}

   return 0;

}

