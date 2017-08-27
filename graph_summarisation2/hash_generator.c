#include <stdio.h>
#include <stdlib.h>
int main()
{
	int i,nh=20;
	srand(time(NULL));
	for(i=0;i<nh;i++)
	{
		printf("%d,",(rand()%nh)*2+1);
		printf("%d\n",(rand()%100)-(rand()%100) +1);
	}

}

	 
