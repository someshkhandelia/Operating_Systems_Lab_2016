/*ASSIGNMENT NO. 4
  OS LAB
  GROUP NO. 48
  ROLL NO. 14/CS/105 and 13/CS/111
  NAMES: SOMESH KHANDELIA and SUBHRANIL MONDAL*/

/***********************************************************************************************************************/

#include<stdio.h>
#include<unistd.h>
int main(void)
{
int pfds[2];
pipe(pfds);
if (!fork()) {
  close(1);
  dup(pfds[1]);
  close(pfds[0]);
  execlp("ls","ls","-l",NULL);
}

else{
  close(0);
  dup(pfds[0]);
  close(pfds[1]);
  execlp("wc","wc",NULL);
}
return 0;
}
