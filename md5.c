#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/md5.h>
 
int main()
{
   const char senha[100] = "huffman";
   //supondo que a senha seja huffman
   const char tentativa[100];


   scanf("%s", tentativa);
   int i;


   FILE *p, *q, *aux;
   p = fopen("md5.txt", "w");


   /*MD5_DIGEST_LENGTH é 16, no caso 16 bytes em decimal. No entanto, como geralmente 
   a hash md5 é salva em 32 bits hexa, no arquivo são salvos os 32 bytes*/
   unsigned char result[MD5_DIGEST_LENGTH];
   unsigned char result2[MD5_DIGEST_LENGTH];

   //A funçao cria o MD5 a partir da string e salva em result
   MD5(senha, strlen(senha), result);
   MD5(tentativa, strlen(tentativa), result2);

   //Isso nao funciona
   if(strcmp(result, result2) == 0)
   {
      printf("Senha correta!\n");
   }  
   else
   {  
      printf("Senha incorreta.\n");
   }    




   for(i = 0; i < MD5_DIGEST_LENGTH; i++)
   {
      printf("%2x", result[i]);
      //Isso que quero salvar em uma string
      fprintf(p, "%02x", result[i]);
   }
   printf("\n");
   fprintf(p, "\n");

   for(i = 0; i < MD5_DIGEST_LENGTH; i++)
   {
      printf("%2x", result2[i]);
            //Isso que quero salvar em uma string

      fprintf(p, "%02x", result[i]);
      
   }
   printf("\n");
   fclose(p);

}