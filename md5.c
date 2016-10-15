#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/md5.h>
 
const char *string = "Alexandre";
 
int main()
{

   int i;
   FILE *p;
   p = fopen("md5.txt", "w");

   /*MD5_DIGEST_LENGTH é 16, no caso 16 bytes em decimal. No entanto, como geralmente 
   a hash md5 é salva em 32 bits hexa, no arquivo são salvos os 32 bytes*/
   unsigned char result[MD5_DIGEST_LENGTH];

   //A funçao cria o MD5 a partir da string e salva em result
   MD5(string, strlen(string), result);
    

   for(i = 0; i < MD5_DIGEST_LENGTH; i++)
   {

     fprintf(p, "%02x", result[i]);
   }
}