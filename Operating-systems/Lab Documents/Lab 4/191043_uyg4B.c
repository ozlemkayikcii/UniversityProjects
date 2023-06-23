#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <pthread.h>
#include <time.h>
#include <sys/stat.h>

#define READ_END 0
#define WRITE_END 1

bool alarmFlag = false;
struct stat attr;
void alarmHandler(int signal) {
    printf("Alarm Handler -> Alarm clock signal received.\n");
    alarmFlag = true;
}
void *funcChecker(void *pathChk) {

	while (1) {
		stat(pathChk, &attr);
		usleep((int)(100000));
	}
	printf("This line should never be executed. Server program must always be running!\n");
}
void signalHandler(int signal) {
    printf("Signal Handler -> Signal received: %d\n", signal);
    printf("Signal Handler -> I'll always suffer (Protection from Ctrl+C | Ctrl+Z)!!!\n");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s pathInputFile\n", argv[0]);
        return 1;
    }

    char *pathInp = argv[1];
    FILE *inputFile = fopen(pathInp, "r");

    if (inputFile == NULL) {
        fprintf(stderr, "Error opening the input file.\n");
        return 1;
    }

    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    } else if (pid == 0) {
        // Child process

        printf("Child process: PID=%d, PPID=%d\n", getpid(), getppid());
        pthread_t threadChecker;
		pthread_create(&threadChecker, NULL, funcChecker, argv[1]);
		struct stat chkdattr;
		stat(argv[1], &chkdattr);
		printf(" __________Last modified time: %s________________", ctime(&chkdattr.st_mtime));
		
		while (1) {
			if(attr.st_mtime != chkdattr.st_mtime) {
				printf(" __________Last  updated time: %s ________________", ctime(&attr.st_mtime));
        // Read the student number from the input file
        long int studentNumber;
        fscanf(inputFile, "%li", &studentNumber);

        // Close the read end of the pipe
        close(pipefd[READ_END]);

        // Write the student number to the parent process through the pipe
        write(pipefd[WRITE_END], &studentNumber, sizeof(studentNumber));

        // Close the write end of the pipe
        close(pipefd[WRITE_END]);

        // Wait for 4 seconds
        sleep(4);
        chkdattr = attr;
            }
            
            usleep((int)(100000));
            }
        printf("Child process exiting.\n");
    } else {
        // Parent process

        printf("Parent process: PID=%d\n", getpid());

        // Close the write end of the pipe
        close(pipefd[WRITE_END]);

        // Read the student number from the child process through the pipe
        long int studentNumber;
        read(pipefd[READ_END], &studentNumber, sizeof(studentNumber));

        printf("Received message from child process: %li\n", studentNumber);

        // Close the read end of the pipe
        close(pipefd[READ_END]);

        int faculty = studentNumber / 10000000000;
        int dept = (studentNumber / 100000000) % 100;
        int entYear = (studentNumber / 10000) % 10000;

        // Process the student number and print details
        printf("Parsing and printing Student ID:\n");
        printf("Faculty: ");
        if (faculty == 15) {
            printf("Engineering Faculty\n");
        } else if (faculty == 30) {
            printf("Other University\n");
        } else {
            printf("Other\n");
        }

        printf("Department: ");
        if (dept == 21) {
            printf("Computer Engineering\n");
        } else if (dept == 12) {
            printf("Electrical Engineering\n");
        }
        else{printf("Other\n");}


    printf("Entrance Year: %d\n", entYear);

    if (entYear >= 2017) {
        // Wait for 4 seconds
        printf("Parent process waiting for 4 seconds...\n");
        sleep(4);
        printf("Parent process waited for 4 seconds.\n");

        // Terminate the child process
        printf("Terminating the child process...\n");
        kill(pid, SIGTERM);
        wait(NULL);
        printf("Child process terminated.\n");
    } 
     if (faculty != 15) {
        // Set up signal handlers for Ctrl+C and Ctrl+Z
        signal(SIGINT, signalHandler);
        signal(SIGTSTP, signalHandler);

        // Set up an alarm for 6 seconds
        signal(SIGALRM, alarmHandler);
        alarm(6);

        printf("Parent process waiting for 6 seconds...\n");
        printf("Parent process will ignore Ctrl+C and Ctrl+Z signals during the wait.\n");
        //printf("Send Ctrl+C or Ctrl+Z to test.\n");

        // Wait until the alarm goes off
        while (!alarmFlag) {
            pause();
        }

        printf("Parent process waited for 6 seconds.\n");

        // Restore the default signal handlers for Ctrl+C and Ctrl+Z
        //signal(SIGINT, SIG_DFL);
        //signal(SIGTSTP, SIG_DFL);
    }

    printf("Parent process exiting.\n");
    fclose(inputFile);

    }
    return 0;
    }

