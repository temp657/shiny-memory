#include<stdio.h>
#include<string.h>

int main()
{
    char data[50],stuff[50],dstuff[50];
    int i,j,s,fsize,noofframes,tframe,dsize;
    
    printf("Enter data: \n");
    scanf("%s", data);
    
    dsize = strlen(data);
    
    printf("Enter fsize: \n");
    scanf("%d", &fsize);
    s=fsize;

    tframe = fsize-1;
    noofframes = (dsize/tframe) + 1;
    
    for(i =0; i<(noofframes+dsize);i++)
    {
        if(i%fsize ==0)
        {
            if((dsize-j)<fsize)
            {
                fsize = dsize-j+1;
            }
        stuff[i]=(char)(48 + fsize);
        fsize = s;
        }
        else
        {
            stuff[i]=data[j];
            j++;
        }
    }
    stuff[noofframes+dsize] = '\0';
    
    printf("Stuffed data is: %s\n", stuff);
    
    
    j=0;
    for(i=0;i<(noofframes+dsize);i++)
    {
        if(i%fsize!=0)
        {
            dstuff[j]=stuff[i];
            j++;
        }
    }
    printf("De-stuffed data is: %s\n", dstuff);
    return 0;
}
