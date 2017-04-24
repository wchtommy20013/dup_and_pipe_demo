#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char** argv){
        int fd[2];
	int fd_file1 = open("myfile1.txt", O_RDONLY);
	int fd_file2 = open("myfile2", O_CREAT|O_WRONLY|O_TRUNC);

	pipe(fd);
   
        if(fork() == 0){
		close(STDIN_FILENO);
		dup(fd_file1);

            	close(STDOUT_FILENO);  	
            	dup(fd[1]);          
		execl("/bin/cat", "cat", (char*) NULL);
       	}

        if(fork() == 0){
           	close(STDIN_FILENO);
            	dup(fd[0]);        	
		close(fd[1]);			
		close(STDOUT_FILENO);
		dup(fd_file2);

            	execl("/usr/bin/wc", "wc", "-l", (char*) NULL);
       	}
}
