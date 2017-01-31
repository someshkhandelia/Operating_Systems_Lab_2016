/*ASSIGNMENT NO. 2
  OS LAB
  GROUP NO. 48
  ROLL NO. 14/CS/105 and 13/CS/111
  NAMES: SOMESH KHANDELIA and SUBHRANIL MONDAL*/
/***********************************************************************/
/*PLEASE EXECUTE THE FOLLOWING COMMANDS ON THE TERMINAL BEFORE RUNNING
gcc twice.c -o twice
gcc half.c -o half
gcc square.c -o square

NOW EXECUTE:
FOR EXAMPLE

./twice half square half 200

*/
/************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<string.h>

int main(int argc,char**argv){
  pid_t mypid;
  mypid=getpid();
  char*s1=argv[argc-1];
  int len=strlen(s1);
  int i=0;
  int d=0;
  int temp;
  while(i<len){
      temp=(int)s1[i]-48;
      d=d*10+temp;
      i++;
    }

// number is in d

  int result=d*d;
  int z=result;

  int c=0;
  while(z!=0){
    c=c+1;
    z=z/10;
  }

  z=result;
//converting result to string

  char*newa=(char*)malloc((c+1)*sizeof(char));
  newa[c]='\0';

  for(i=c-1;i>=0;i--){
    newa[i]=z%10+'0';
    z=z/10;
  }

//so now newa[] contains the result in string form
  strcpy(argv[argc-1],newa);// final argument is the result

  char**newarg=(char**)malloc((argc)*sizeof(char*));

  for(i=1;i<argc;i++){
    newarg[i-1]=(char*)malloc(sizeof(argv[i]));
    strcpy(newarg[i-1],argv[i]);
  }

  char nextarg[50];
  strcpy(nextarg,"./");
  strcat(nextarg,argv[1]);
  if(argc>2){
    printf("The square calculating program process-id=%u and result=%d\n",mypid,result);
    execvp(nextarg,newarg);
  }

  printf("Final result in square program with process-id=%u and result=%d\n",mypid,result);


  return 0;


}
