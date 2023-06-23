#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <getopt.h>
int temp;


/// @brief kullanıcı taraffından seçilen ve girilen opsiyonlara göre kişi bilgisi ve derinlik bilgisi alınarak işlenir,
///logs klasörü ve logAll.log dosyası açılarak işlemler opsiyonlara göre dosyalara yazdırılır.Derinlik bilgisi kullanıcının girdisinden 
//bağımsız olarak en az 2 olarak kabul edilir.Ebeveyn oluşturulup 1 saniye bekletilir,child proses üretme fonksiyonu çağırılır.
/// @param argc int değerinde kullanıcıdan opsiyon almak için kullanılır.
/// @param argv char değerinde kullanıcıdan opsiyon almak için kullanılır.
/// @return sistemi sonlandıran değeri içerir.
int main(int argc, char* argv[]) 
{
    int opt, depth = -1, show_info = -1;
    while ((opt = getopt(argc, argv, "i:o:")) != -1) {
        switch (opt) {
        case 'i':
            show_info = atoi(optarg);
            break;
        case 'o':
            depth = atoi(optarg);
            break;
        default:
            fprintf(stderr, "Usage: %s [-i show_info] [-o depth]\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    if (depth < 2) {
        depth = 2;
    }
    temp=depth+1;
    // Create logs directory if it does not exist
    mkdir("logs", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

    // Open log file
    char log_file_name[50];
    time_t now = time(NULL);
     strftime(log_file_name, 50, "logs/logAll-%Y-%m-%d_%H-%M-%S.log", localtime(&now));
     FILE* log_file = fopen(log_file_name, "w");
     if (log_file == NULL) {
        printf("Error: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    write_log("Log file created.\n");
    

    // Write info to log file
    if (show_info==0) {
        char info[100];
        sprintf(info, "152120191043 @%s wrote this.\n",  getenv("USER"));
        write_log(info);
    }

    // Create process tree
  int parent_pid = getpid();
   
    printf("Parent process with PID: %d\n", parent_pid);
    waitpid(parent_pid, NULL, 1);
     wait(1);
    create_process_tree(depth+1,parent_pid);

    fclose(log_file);

    return 0;
}



/// @brief recursive olarak child (alt işlemler olusturur) ilk derinlikte 2 çcocuk, sonraki derinliklerde 1 çocuk olusturulur.
/// @param depth kullanıcının belirlediği derinlik fonksiyona argüman olarak atanır.
/// @param parent_pid ata belirleme işleminin yapıldığı kısım argüman olarak atanır.
void create_process_tree(int depth,int parent_pid) {
    pid_t pid = getpid();

    if (depth > 1) {
        if (depth == temp) { 
            pid_t child1_pid = fork();
            if (child1_pid == 0) {
                 printf("Child process created with PID: %d from parent process with PID: %d\n", getpid(), parent_pid);
                 char info[300];
                 sprintf(info, "Child process created with PID: %d from parent process with PID: %d\n", getpid(), parent_pid);
                 write_log(info);
                 wait(2);
                create_process_tree(depth - 1,getpid());
                _exit(0);
            } else {
                pid_t child2_pid = fork();
                if (child2_pid == 0) {
                    printf("Child2 process created with PID: %d from parent process with PID: %d\n", getpid(), parent_pid);
                    char info[300];
                    sprintf(info, "Child2 process created with PID: %d from parent process with PID: %d\n", getpid(), parent_pid);
                    write_log(info);
                     wait(2);
                    _exit(0);
                } else {
                    waitpid(child1_pid, NULL, 0);
                    waitpid(child2_pid, NULL, 0);
                }
            }
        } else { 
            pid_t child_pid = fork();
            if (child_pid == 0) {
                printf("Child process created with PID: %d from parent process with PID: %d\n", getpid(), parent_pid);
                char info[300];
                sprintf(info, "Child process created with PID: %d from parent process with PID: %d\n", getpid(), parent_pid);
                write_log(info);
                 wait(2);
                create_process_tree(depth - 1,getpid());
                _exit(0);
            } else {
                waitpid(child_pid, NULL, 0);
            }
        }
    } else {
        _exit(0);
    }
}


/// @brief olusturulan log dosyasına yazım için gerekli bilgileri içerir.
/// @param message yazılmak istenen mesajdır.
void write_log(char* message) {
    FILE* log_file = fopen("logs/logAll.log", "a");
    if (log_file == NULL) {
        printf("Error: Failed to open log file.\n");
        exit(1);
    }
    time_t t = time(NULL);
    struct tm* tm = localtime(&t);
    char timestamp[30];
    strftime(timestamp, sizeof(timestamp), "%c", tm);
    char log_message[200];
    sprintf(log_message, "[%s]: %s\n", timestamp, message);
    fprintf(log_file, "%s", log_message);
    fclose(log_file);
}





