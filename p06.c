/* 
Amogh Lale
3/24/2015
Assignment 6 
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define MAXSIZE 1000
int data[MAXSIZE];
int n,i;
int total;
int lookup_table[10000][10000];


void call_traceback(int data[], int a,int b)
{
	int count=0,i=0,j;	
	char result[10000];
		
 		while(a>0)
		{
			if(lookup_table[a-1][b]!=-1)
			{
				result[i]='L';
				i++;
				count++;	
				a--;
			}
			else
			{
				b=b-data[a];
				result[i]='R';
				i++;
				count++;
				a--;
			}
		}	
		printf("%d",count);
		for(j=i;j>=0;j--)
		{
			printf("%c\n",result[j]);
		}
}

void load_cars(int data[], int n, int total)
{
 	int j,k;
 	int a=0,b=0;
	bool flag=false;
	
	// initialize lookup_table[][] with -1
	for (i = 0; i <= n; i++)
   	{
		for (j = 0; j <= total; j++)
		{
           		lookup_table[i][j]=-1;     	          
       		}
   	}

	
	// Set zeroth row and zeroth column value to 0
	lookup_table[0][0]=0;
			
	// build lookup table
	for(i=1;i<=n;i++)                 // n = rows = total number of cars 
	{
		if(flag==false)
		{		
			flag=true;
			for(j=0;j<=total;j++)   //total = columns = total length of ferry
			{
				if(lookup_table[i-1][j]!=-1)    //if valid
				{
					k=lookup_table[i-1][j]+data[i];	 
					if(k<=total)
					{
						flag=false;
						lookup_table[i][j]=k;     
						if(k>=j)
						{
							k=lookup_table[i-1][j]+data[i];
							if(k<=total) 
							{			
								if(lookup_table[i-1][k]==-1)
								        lookup_table[i][k]=0;
							}	
						}
						a=i;
						b=j;
					} //if closed
       				} //if closed
			}// inner for loop closed
		} //if closed
	}//i for loop closed	
	
	call_traceback(data,a,b);		

}

int main(int argc, char* argv[])
{
	
	// total length of ferry 
	scanf("%d", &total);

	// Total number of cars
  	scanf("%d", &n);

	//accept cars
  	for (i = 1; i <=n; i++)
	{
    		scanf("%d",&data[i]);
	}
	
	//If length of first car is greater than length of ferry then exit
	if(data[1]>total)
	{
		printf("Not Possible\n");
		exit(0);
	}
	
	// Load cars in the ferry
 	load_cars(data, n, total);
}
