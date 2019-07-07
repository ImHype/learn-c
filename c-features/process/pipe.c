#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 
  
int main() 
{ 
    // We use two pipes 
    // First pipe to send input string from parent 
    // Second pipe to send concatenated string from child 
  
    int fd1[2];  // Used to store two ends of first pipe 
    int fd2[2];  // Used to store two ends of second pipe 
  
    char fixed_str[] = "forgeeks.org"; 
    char input_str[100] = "source_code:\nhello world"; 
    pid_t p; 
  
    if (pipe(fd1)==-1) 
    { 
        fprintf(stderr, "Pipe Failed" ); 
        return 1; 
    } 
    if (pipe(fd2)==-1) 
    { 
        fprintf(stderr, "Pipe Failed" ); 
        return 1; 
    } 
  
    p = fork(); 
  
    if (p < 0) 
    { 
        fprintf(stderr, "fork Failed" ); 
        return 1; 
    } 
  
    // Parent process 
    else if (p > 0) 
    { 
        char concat_str[100]; 
        char concated_str[100] = "child->parent:\n"; 
  
        close(fd1[0]);  // Close reading end of first pipe 
  
        // Write input string and close writing end of first 
        // pipe. 

        printf("size: %lu", strlen(input_str)+1);
        write(fd1[1], input_str, strlen(input_str)+1); 
        // close(fd1[1]); 
  
        // Wait for child to send a string 
        wait(NULL); 
  
        // close(fd2[1]); // Close writing end of second pipe 
  
        // Read string from child, print it and close 
        // reading end. 
        // printf("start reading");
        // read(fd2[0], concat_str, 100); 
        // printf("%s", strcat(concated_str, concat_str)); 
        // close(fd2[0]); 
    } 
  
    // child process 
    else
    { 
        printf("child process");
        close(fd1[1]);  // Close writing end of first pipe 
  
        // Read a string using first pipe 
        char concat_str[100]; 
        char concated_str[100] = "parent->child:\n"; 
        read(fd1[0], concat_str, 100); 

        printf("%s", strcat(concated_str, concat_str));

        // strcat(concated_str, concat_str);
        // strcat(concated_str, "\0");
        // // Close both reading ends 
        // close(fd1[0]); 
        // close(fd2[0]); 
        // sleep(1);
  
        // // Write concatenated string and close writing end 
        // write(fd2[1], concated_str, strlen(concated_str)+1); 
        // close(fd2[1]); 
        // exit(0); 
    } 
} 