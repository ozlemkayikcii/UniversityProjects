#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h> 			//for usleep(); if you need to sleep shorter than 1 sec. //usleep((int)(100000)); for 0.1 sec.s
#include <sys/stat.h>		//for the "last modified time" stat
#include <pthread.h>

char *pathRep;
struct stat attr;


void *funcprintTimeAndChanges(void *pathSub) //Klasördeki değişikliğin takibini yapan thread fonksiyonudur.
{

	char pathLogFile[250];
	sprintf(pathLogFile, "%s/191043_uyg3B_repHistory.log", pathRep);  //log dosyası oluşturulup ilgili dizine eklendi.
    char *_pathSub = pathSub;
	struct stat chkdattr = attr;  //güncelemeyle kıyaslamak için kullanılıyor.

	while(1) {

		if(attr.st_mtime != chkdattr.st_mtime) //last modified time değişikliği kontrol edilir.
        {
			printf("Last modified time: %s", ctime(&attr.st_mtime)); //If you need some ctime comparison, use (a.st_mtime == b.st_mtime)
            char myChar[500];
            
            // sprintf(myChar, "ls pathSubmission/. | du -h  pathSubmission/. >> %s", pathLogFile);
            //system(myChar);
            //sprintf(myChar, "ls -Rd /home/ozlem/pathSubmission/* | xargs du -sh >> %s",  pathLogFile);
            sprintf(myChar, "ls -Rd %s/* | xargs du -sh >> %s",_pathSub,  pathLogFile); //belirtilen dizin altındaki klasör ve dosyaları boyut bilgisi ile yazdırır.
            system(myChar);

            sprintf(myChar, "echo __________________________________________________________>> %s",  pathLogFile);// dizin altındaki her değişikliğin saptanması için log dosyasına kaydetmeden çekilen versiyon çizgisi.
            system(myChar);
           // sprintf(myChar, "cp -a pathSubmission/. pathRepository/.");
            sprintf(myChar, "cp -a %s/. %s/.",_pathSub,pathRep);   //tüm alt dizinler pathsubdan alınıp pathrep e kopyalanıyor.
            system(myChar);

            chkdattr = attr;//güncelleme kontrolü için kullanılıyor.
		}

		printf("\r\033[1A%c",  system("date")); // \r: set cursor to the first char of the line; \033[1A: move cursor up 1 line;
		fflush(stdout);	//clear output buffer
		usleep((int)(1000000));
	}

	printf("This line should never be executed. Server program must always be running!\n");
}


void *funcChecker(void *pathSub)//statı belli aralıklarla güncellemek için kullanan fonksiyon.
 {
    while(1) 
    { 
        stat(pathSub, &attr);
        usleep(1000000);
    }
	// printf("This line should never be executed. Server program must always be running!\n");
}

int main(int argc,char *argv[]) {
    
    
        if (argc != 3)     // belirtilen argümana ulaşmadığında hata verip sonlandır.
        {
        printf("Usage: %s pathRepository pathSubmission\n", argv[0]);
        exit(EXIT_FAILURE);
        }
        pathRep = argv[1];
        char *pathSub = argv[2];    //argüman atama işlemleri.
        char myChar[100];

        sprintf(myChar,"mkdir -p %s; mkdir -p %s", pathRep, pathSub); //kullanıcıdan alınan klasörlerin yaratılması.
        system(myChar);

        
        pthread_t threadChecker; 
        pthread_t threadWorker_TimeAndChanges;     //threadler oluşturuldu.

        
        pthread_create(&threadChecker, NULL, funcChecker, argv[2]);
        pthread_create(&threadWorker_TimeAndChanges, NULL, funcprintTimeAndChanges, argv[2]);   //threadleri yaratıldı.

    
        pthread_join(threadChecker, NULL);
        pthread_join(threadWorker_TimeAndChanges, NULL);   //thread fonksiyonlarını joinleme.
    

	    return 0;
}