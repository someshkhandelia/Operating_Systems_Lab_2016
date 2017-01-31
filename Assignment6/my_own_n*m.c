#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<unistd.h>
#include<sys/sem.h>

#define P(s) semop(s,&pop,1);
#define V(s) semop(s,&vop,1);

int isempty(int*arr){
  int i;
  for(i=0;i<20;i++){
    if(arr[i]!=-1){
      return -1;
    }
  }

    return 1;

}


int main(void){

  int m,n;
  int i,j,k;
  printf("Enter value of m:");
  scanf("%d",&m);
  printf("Enter value of n:");
  scanf("%d",&n);
//////////////////////////////////////////////////////////
  struct sembuf pop,vop;
  pop.sem_num=vop.sem_num=0;
  pop.sem_flg=vop.sem_flg=0;
  pop.sem_op=-1;
  vop.sem_op=1;
/////////////////////////////////////////////////////////////

int semid1,semid2;
semid1=semget(IPC_PRIVATE,1,IPC_PRIVATE|0777);
semid2=semget(IPC_PRIVATE,1,IPC_PRIVATE|0777);

semctl(semid1,0,SETVAL,1);//producer
semctl(semid2,0,SETVAL,0);//consumer
//////////////////////////////////////////////////////////////

int shared_array_id,sum_id;
shared_array_id=shmget(IPC_PRIVATE,20*sizeof(int),IPC_CREAT|0777);
sum_id=shmget(IPC_PRIVATE,sizeof(int),IPC_CREAT|0777);

int*sum1=(int*)shmat(sum_id,0,0);
*sum1=0;

/////////////////////////PRODUCER////////////////////////////////////

for(i=0;i<m;i++){
  if(!fork()){
    //producer process(producer since m iterations)

    int*pro_arr=(int*)shmat(shared_array_id,0,0);

    for(j=1;j<=50;){
      P(semid1);
      for(k=0;k<20&&j<=50;k++){
        pro_arr[k]=j;

        printf("Producer writes %d\n",pro_arr[k]);
        j++;
      }
      V(semid2);

    }

      shmdt(pro_arr);
      printf("Producer %d exits\n\n",i+1);
      exit(0);

  }
}

////////////////////////CONSUMER///////////////////////////////////////

for(i=0;i<n;i++){
  if(!fork()){
    //consumer process(consumer since n iterations)

    int*con_arr=(int*)shmat(shared_array_id,0,0);
    int*sum=(int*)shmat(sum_id,0,0);
    while(1){

     P(semid2);
      if(isempty(con_arr)==-1){
      //  printf("ABHI NON_EMPTY HAI\n\n");
        for(j=1;j<=50;){

          if(isempty(con_arr)==-1){
            for(k=0;k<20&&j<=50;k++){
              if(con_arr[k]!=-1){
                *sum=*sum+con_arr[k];
                printf("Consumer number %d reads %d\n",i+1,con_arr[k]);
                printf("Current value of sum=%d\n",*sum);
                con_arr[k]=-1;
                j++;
              }
                //j++;
                else{
                  break;
                }
              }
          }
          else{

            V(semid1);//if all producers have not exited execute this
            break;
          }

        }
      }
      else{

        break;
      }

    }


      shmdt(con_arr);
      shmdt(sum);
    //  printf("Consumer exits\n\n");
      exit(0);

  }//one consumer ends here
}
////////////////////////////////////////////////////////////////////

for(i=0;i<m;i++){
  wait(NULL);
}
sleep(2);

printf("\n\nVALUE OF SUM IN PARENT=%d\n\n",*sum1);
shmdt(sum1);

shmctl(shared_array_id,IPC_RMID,0);
shmctl(sum_id,IPC_RMID,0);

semctl(semid1,0,IPC_RMID,0);
semctl(semid2,0,IPC_RMID,0);

return 0;

}
