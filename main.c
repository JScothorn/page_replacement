/*
 * main.c
 *
 *  Created on: Jul 2, 2015
 *  Author: justin scothorn
 *
 *  Algorithms were started from code found at:
 *
 *  http://codearea.in/wp-content/uploads/2012/07/pagereplacement1.c
 *
 *  https://github.com/dileep98490/Operating-Systems/blob/master/Page%20replacement%20algorithms/LFU.c
 *
 *  The code found at these sites was altered to fit the requirements of this project
 *
 */
#include<stdio.h>
#include<stdlib.h>
void fifo(int *fr,int frameSize,int *pg,int n);
void optimal(int *fr,int frameSize,int *pg,int n);
void lru(int *fr,int frameSize,int *pg,int n);
void lfu(int *fr,int frameSize,int *pg,int n);
void mfu(int fr[],int frameSize,int pg[],int n);
int minVal(int frameSize,int *count);
int maxVal(int frameSize,int *count);

int main(int argc, char **argv)
{
	int i,ch,j,frameSize;
	int n = argc-2;
	int pg[n];
	frameSize = atoi(argv[1]);
	int fr[frameSize];

	printf("\n\tPage Replacement Algorithms!\n");

	printf("\nNumber of pages is %d\n", n);
	printf("Number of frames is %d\n", frameSize);

	printf("\nAccepting sequence:\n");
	for(i=0,j=2;i<argc && j < argc;i++,j++){//accepting sequence
		pg[i] = atoi(argv[j]);
		printf("%d ",pg[i]);
	}
	printf("\nSequence accepted!");

	do
	{
		printf("\n\n\tMENU\n");
		printf("\n1)FIFO");
		printf("\n2)OPTIMAL");
		printf("\n3)LRU");
		printf("\n4)LFU");
		printf("\n5)MFU");
		printf("\n6)EXIT");
		printf("\nEnter your choice:");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1: fifo(fr,frameSize,pg,n);
				break;

			case 2: optimal(fr,frameSize,pg,n);
				break;

			case 3: lru(fr,frameSize,pg,n);
				break;

			case 4: lfu(fr,frameSize,pg,n);
				break;

			case 5: mfu(fr,frameSize,pg,n);
				break;

		}
	}while(ch!=6);
	getchar();
	return 0;
}
///////////////////////////////////////////////
//
//	First in first out page replacement
//	all parameters passed are already initialized from main
//	from the command line arguments
//
///////////////////////////////////////////////
void fifo(int fr[],int frameSize,int pg[],int n)
{
	int i,f=0,r=0,s=0,counter=0,flag=0,num;

	for(i=0;i<frameSize;i++)
	{
		fr[i]=-1;
	}
	printf("\n\tFIFO\n");
	while(s<n)
	{
		flag=0;
		num=pg[s];
		for(i=0;i<frameSize;i++)
		{
			if(num==fr[i])//check if current page is in frame already
			{
				s++;
				flag=1;
				break;
			}
		}
		if(flag==0)
		{
			if(r<frameSize)
			{
				fr[r]=pg[s];
				r++;
				s++;
				counter++;
			}
			else
			{
				if(f<frameSize)
				{
					fr[f]=pg[s];
					s++;
					f++;
					counter++;
				}
				else
					f=0;
			}
		}
		printf("\n");
		for(i=0;i<frameSize;i++)
		{
			printf("%d\t",fr[i]);
		}
	}
printf("\n\nPage Faults = %d",counter);
getchar();
}

///////////////////////////////////////////////
//
//	Optimal page replacement
//	all parameters passed are already initialized from main
//	from the command line arguments
//
///////////////////////////////////////////////
void optimal(int fr[],int frameSize,int pg[],int n)
{
	int count[frameSize],i,j,k=0,fault=0,flag,temp,current,c,max,m,cnt,p,x;

	//Initializing distance and frame array
	for(i=0;i<frameSize;i++){
		count[i]=0;
		fr[i]=-1;
	}
	printf("\n\tOPTIMAL\n");
	for(i=0;i<n;i++){
		flag=0;
		temp=pg[i];
		for(j=0;j<frameSize;j++){//check if current page is in frame already
			if(temp==fr[j]){
				flag=1;
				break;
			}
		}
		if((flag==0)&&(k<frameSize)){//first three pages added to the frame
			fault++;
			fr[k]=temp;
			k++;
		}else if((flag==0)&&(k==frameSize)){//once frame is full
			fault++;
			for(cnt=0;cnt<frameSize;cnt++){
				current=fr[cnt];
				for(c=i;c<n;c++){
					if(current!=pg[c]){
						count[cnt]++;
					}else{
						break;
					}
				}
			}
			max=0;
			for(m=0;m<frameSize;m++){
				if(count[m]>max){
					max=count[m];
					p=m;
				}
			}
			fr[p]=temp;
		}
		printf("\n");
		for(x=0;x<frameSize;x++){
			printf("%d\t",fr[x]);
		}
	}
	printf("\n\nPage Faults = %d",fault);
	getchar();
}

///////////////////////////////////////////////
//
//	Least recently used(LRU) page replacement
//	all parameters passed are already initialized from main
//	from the command line arguments
//
///////////////////////////////////////////////
void lru(int fr[],int frameSize,int pg[],int n)
{
	int count[frameSize],i,j,k=0,fault=0,flag,currentPage,current,c,max,m,cnt,p,x;

	//Initializing count and frame array
	for(i=0;i<frameSize;i++){
		count[i]=0;
		fr[i]=-1;
	}
	printf("\n\tLRU\n");
	for(i=0;i<n;i++){
		flag=0;
		currentPage=pg[i];
		for(j=0;j<frameSize;j++){//check if current page is in frame already
			if(currentPage==fr[j]){
				flag=1;
				break;
			}
		}
		if((flag==0)&&(k<frameSize)){//first three pages added to the frame
			fault++;
			fr[k]=currentPage;
			k++;
		}else if((flag==0)&&(k==frameSize)){//once frame is full
			fault++;
			for(cnt=0;cnt<frameSize;cnt++){
				current=fr[cnt];
				for(c=i;c>0;c--){
					if(current!=pg[c])
						count[cnt]++;
					else
						break;
				}
			}
			max=0;
			for(m=0;m<frameSize;m++){
				if(count[m]>max){
					max=count[m];
					p=m;
				}
			}
			fr[p]=currentPage;
		}
		printf("\n");
		for(x=0;x<frameSize;x++){
			printf("%d\t",fr[x]);
		}
	}
	printf("\n\nPage Faults = %d",fault);
	getchar();
}

///////////////////////////////////////////////
//
//	Least frequently used(LFU) page replacement
//	all parameters passed are already initialized from main
//	from the command line arguments
//
///////////////////////////////////////////////
void lfu(int fr[],int frameSize,int pg[],int n){
	int count[frameSize];
	int i,j,z,currentPage,min, fault=0,flag=0,k=0;

	//initialize frame to -1, and count to 0
	for(i=0;i<frameSize;i++){
		fr[i] = -1;
		count[i] = 0;
	}
	printf("\n\tLFU\n");
		for(i=0;i<n;i++){
			flag=0;
			currentPage=pg[i];
			for(j=0;j<frameSize;j++){//check if current page is in frame already
				if(currentPage==fr[j]){
					flag=1;
					count[j]=count[j]+1;
					break;
				}
			}
		if((flag==0)&&(k<frameSize)){//first three pages added to the frame
			fault++;
			fr[k]=currentPage;
			count[k]=count[k]+1;
			k++;
		}else if((flag==0)&&(k==frameSize)){//once frame is full
			fault++;
			min = minVal(frameSize,count);
			fr[min]=pg[i];
			count[min]=0;
		}
		printf("\n");
		for(z=0;z<frameSize;z++){
			printf("%d\t",fr[z]);
		}
	}
	printf("\n\nPage Faults = %d",fault);
	getchar();
}

///////////////////////////////////////////////
//
//	Most frequently used(MFU) page replacement
//	all parameters passed are already initialized from main
//	from the command line arguments
//
///////////////////////////////////////////////
void mfu(int fr[],int frameSize,int pg[],int n){
	int count[frameSize];
	int i,j,z,currentPage,max, fault=0,flag=0,k=0;

	//initialize frame to -1, and count to 0
	for(i=0;i<frameSize;i++){
		fr[i] = -1;
		count[i] = 0;
	}
	printf("\n\tMFU\n");
		for(i=0;i<n;i++){
			flag=0;
			currentPage=pg[i];
			for(j=0;j<frameSize;j++){//check if current page is in frame already
				if(currentPage==fr[j]){
					flag=1;
					count[j]=count[j]+1;
					break;
				}
			}
		if((flag==0)&&(k<frameSize)){//first three pages added to the frame
			fault++;
			fr[k]=currentPage;
			count[k]=count[k]+1;
			k++;
		}else if((flag==0)&&(k==frameSize)){//once frame is full
			fault++;
			max = maxVal(frameSize,count);
			fr[max]=pg[i];
			count[max]=0;
		}
		printf("\n");
		for(z=0;z<frameSize;z++){
			printf("%d\t",fr[z]);
		}
	}
	printf("\n\nPage Faults = %d",fault);
	getchar();
}

///////////////////////////////////////////////
//
//	Minimum value search method
//	values passed are assumed to be initialized prior
//	returns minimum value index in count array
//
///////////////////////////////////////////////
int minVal(int frameSize,int *count){
	int i,min;

	    min=count[0];
	    for(i=1;i<frameSize;i++){
	    	if(min > count[i] ){
	    		min=i;
	    	}
	    }
	return min;
}

///////////////////////////////////////////////
//
//	Maximum value search method
//	values passed are assumed to be initialized prior
//	returns maximum value index in count array
//
///////////////////////////////////////////////
int maxVal(int frameSize,int *count){
	int i,max;

	    max=count[0];
	    for(i=1;i<frameSize;i++){
	    	if(max<count[i]){
	    		max=i;
	    	}
	    }
	return max;
}
