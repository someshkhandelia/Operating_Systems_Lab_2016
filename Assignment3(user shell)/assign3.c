
/*ASSIGNMENT NO. 3
  OS LAB
  GROUP NO. 48
  ROLL NO. 14/CS/105 and 13/CS/111
  NAMES: SOMESH KHANDELIA and SUBHRANIL MONDAL*/

/***********************************************************************************************************************/


#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>

int main(void){

char buffer[100];
char*commnd;
char argv[10][10];
char*argv2[10];
pid_t mypid;
int i;
  do {
    write(1,"shell> ",7);
   fflush(stdin);
   i=0;
   do {
    buffer[i]= getchar();
     i++;
   } while(buffer[i-1]!='\n');

///////////////////////// creating the argument array ///////////////////

  i=0;
  int j=0,k=0;
  while(buffer[i]!='\n'){
    if(buffer[i]!=' '){
      argv[j][k]=buffer[i];
      k++;
      i++;
    }
    else{
      argv[j][k]='\0';
      j++;
      k=0;
      i++;
    }
  }
  argv[j][k]='\0';
  j++;

//////// converting the argument array to use in execvp //////////////////

commnd=argv[0];

for(i=0;i<j;i++){
  argv2[i]=argv[i];
}
argv2[i]=NULL;


////////////////////////// Using child process for shell ///////////////////
   mypid=fork();
    if(mypid==0){
      execvp(argv2[0],argv2);
    }

    else{
      sleep(1);
    }

  } while(strcmp(commnd,"exit")!=0);
  return 0;

}

/////////////////////////// END OF PROGRAM /////////////////////////////////
