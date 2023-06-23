#include <stdio.h>
#include <stdlib.h>

// Bu değişkenler programın dışında tanımlanmıştır ve
// linker tarafından sağlanır.

extern char etext;     // Programın sonunu temsil eder.
extern char end;      // Programın yüklendiği bellek bölgesinin sonunu temsil eder.
extern int edata;    // Programın veri bölgesinin sonunu temsil eder.

/**
 * @brief etext, end, ve edata sembolleri, programın derlenmiş haliyle birlikte gelen sembollerdir ve bellek bölgesinin farklı segmentlerini temsil eder:

 * etext: Programın kod (yürütülebilir) segmentinin sonunu temsil eder.
 * end: Programın yüklendiği bellek bölgesinin sonunu temsil eder.
 * edata: Programın veri (initialize edilmiş değişkenler) segmentinin sonunu temsil eder.
 * Program başladığında, etext, end, ve edata sembollerinin adreslerini ekrana yazdırır.

 * Kullanıcıdan bir bellek konumu girmesini ister ve bu konumu s değişkenine atar. Bellek konumu, %p formatında girilmelidir (örneğin, 0x12345678).

 * Eğer kullanıcının girdiği bellek konumu, etext sembolünün adresinden daha küçükse, o zaman "Read-only segment" bölgesinde yer aldığını söyler. Bu segmentte, belleği sadece okumak mümkündür. Program, kullanıcının girdiği bellek konumunu okur ve başarılı bir şekilde okunduğunu ekrana yazar.

 * Eğer kullanıcının girdiği bellek konumu, etext sembolünün adresinden büyük veya eşit olup edata sembolünün adresinden daha küçükse, o zaman "Read-write segment" bölgesinde yer aldığını söyler. Bu segmentte, belleği hem okuyup hem de yazmak mümkündür. Program, kullanıcının girdiği bellek konumunu okur ve başarılı bir şekilde okunduğunu ekrana yazar. Ardından, okunan değeri ekrana ve belleğe geri yazmaya çalışır. Bu, belleğin yazılabilir olup olmadığını kontrol etmek için yapılır. Yazma işlemi başarılıysa, yazma işleminin başarılı olduğunu ekrana yazar.

 * Eğer kullanıcının girdiği bellek konumu, edata sembolünün adresinden daha büyükse, geçersiz bir bellek konumu olduğunu söyler.

 * Bu program, kullanıcının girdiği bellek konumunu programın bellek segmentlerine göre sınıflandırır ve belleği okuma ve yazma işlemlerini test eder.
 * 
 * @return int programın sonlandırma dönüş tipini temsil etmektedir.
 */

int main() 
{
    char c, *s;

    printf("&etext  =  %p\n", &etext);
    printf("&end    =  %p\n", &end);
    printf("&edata  =  %p\n", &edata);


    printf("Enter memory location in hex (start with 0x): ");
    fflush(stdout);
    
    // Kullanıcıdan bellek konumunu alır ve s değişkenine atar.

    if (scanf("%p", &s) != 1) 
    {
        printf("Invalid memory location.\n");
        return 1;
    }

    printf("\n\n");

    // Kullanıcının girdiği bellek konumu, etext adresinden daha küçükse
    // "Read-only segment" bölgesinde yer alır.

    if (s < &etext) {
        printf("------Read-only segment!!!------\n\n");
        printf("Reading %p: ", s);
        fflush(stdout);
        c = *s;
        printf("Reading is OK\n");
    }

    // Kullanıcının girdiği bellek konumu, etext adresinden büyük veya eşit
    // olup edata adresinden daha küçükse "Read-write segment" bölgesinde yer alır.

     else if (s < (char*)&edata) 
     {
        printf("------Read-write segment!!!------\n\n");
        printf("Reading %p: ", s);
        fflush(stdout);
        c = *s;
        printf("Reading is OK\n");

        printf("%d\n", c);
        printf("Writing %d back to %p: ", c, s);
        fflush(stdout);
        *s = c;
        printf("Writing is OK\n");
    } 

    // Kullanıcının girdiği bellek konumu, edata adresinden daha büyükse geçersizdir.
   
    else 
    {
        printf("Invalid memory location.\n");
    }

    return 0;
}
