
/*ASSIGNMENT NO. 1
  OS LAB
  GROUP NO. 48
  ROLL NO. 14/CS/105 and 13/CS/111
  NAMES: SOMESH KHANDELIA and SUBHRANIL MONDAL*/

/***********************************************************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<time.h>


int max1,max2;

/***********************************************************************************************/
// This module will find maximum in an array whose size is less than 10

int max_finding_module(int*arr,int l,int r,pid_t mypid,pid_t parpid){
	int i;
	int maxi=arr[l];
	for(i=l;i<=r;i++){
		if(arr[i]>maxi){
			maxi=arr[i];
		}
	}


	printf("The maximum found=%d Process-id=%u Parent-Process-id=%u\n",maxi,mypid,parpid);
	return maxi;

}
/************************************************************************************************/

// This module will create two children Pl and Pr
int child_creating_module(int*arr,int l,int r,int length,pid_t myypid,pid_t parrpid){
	pid_t childpid,mypid,parpid;
	int status;
	int m=(l+r)/2;
	int maxi;
	childpid=fork(); //created a child

	if(childpid==0){
	//Inside the first child

		length=m-l+1;
		mypid=getpid();
		parpid=getppid();
		
		if(length>=10){
			max1=child_creating_module(arr,l,m,length,mypid,parpid);
		}
		
		else{
			max1=max_finding_module(arr,l,m,mypid,parpid);
		}
		exit(max1); //exiting with status equal to max-value 

	}

	

	else if(childpid==-1){
		printf("Child creation unsuccessful\n");
	}



	else{
	//This is the continuing thread of the parent
		
		waitpid(childpid,&status,0);
		max1=WEXITSTATUS(status);

		childpid=fork();    //creating second child
		
		if(childpid==0){
			//Inside the second child
			length=r-m;
			mypid=getpid();
			parpid=getppid();

			if(length>=10){
				max2=child_creating_module(arr,m+1,r,length,mypid,parpid);
			}
			else{
				max2=max_finding_module(arr,m+1,r,mypid,parpid);
			}
			exit(max2);
		}

		else if(childpid==-1){
			printf("Child creation unsuccessful\n");
		}

		else{
			//This is the continuing thread of the parent
			
			waitpid(childpid,&status,0);
			max2=WEXITSTATUS(status);

			maxi= max1>=max2?max1:max2;

			 printf("The maximum found=%d Process-id=%u Parent-Process-id=%u\n",maxi,myypid,parrpid);

			 return maxi;



		}

	}

} // child_creating_module ends here

/****************************************************************************************************/


int main(void){

int n;
printf("Enter the size of the array: ");
scanf("%d",&n);
srand(time(NULL));

int*arr;
arr=(int*)malloc(n*sizeof(int));


int i,j,k,z;
//printf("Enter the elements: ");

for(i=0;i<n;i++){
	//scanf("%d",&arr[i]);
	arr[i]=rand()%200;  // Random values less than 200 will be generated(small values)
}

printf("The unsorted randomly generated input array with small values:\n");

for(i=0;i<n;i++){
	printf("%d ",arr[i]);
}
printf("\n");

pid_t mypid,parpid;


mypid=getpid();
parpid=getppid();

printf("The root process's pid:%u\n",mypid);
printf("The root process's ppid:%u\n",parpid);


int l=0,r=n-1;
int length=n;
int maxi;

if(length>=10){
	child_creating_module(arr,l,r,length,mypid,parpid);
}
else{
	max_finding_module(arr,l,r,mypid,parpid);
}


free(arr);
return 0;

}