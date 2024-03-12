#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

#define N strlen(gen_poly)

char data[30];
char gen_poly[10]="1001";
int data_length, i, j;
char check_value[28];




void append(){
	for(i=data_length; i<data_length+N-1; i++){
		data[i] = '0';
	}
	data[i]='\0';
}



void XOR(){
	for(j=1; j<N; j++)
		check_value[j]=((check_value[j] == gen_poly[j])?'0':'1');
	
}

void crc(){
	for(i=0;i<N;i++){
		check_value[i]=data[i];
	}
	//check_value[i]='\0';
	do{
		if(check_value[0]=='1'){
			XOR();
		}
		
		for(j=0; j<N-1; j++){
			check_value[j]=check_value[j+1];
		}
		check_value[j]=data[i++];
		
	
	}
	while(i<=data_length+N-1);

}

void crc_append(){
	for(j=0;j<N-1;j++){
	data[j+data_length]=check_value[j];
	}
	data[N-1+data_length]='\0';
}


void error(char * msg){
	perror(msg);
	exit(1);
}


int main(int argc, char * argv[]){
	
	if(argc<2){
		fprintf(stderr,"Please enter portno");
		exit(1);
	}
	
	int sockfd,newsockfd,portno, check;
	struct sockaddr_in sockaddr, cliaddr;
	socklen_t clilen;
	char buffer[255];
	
	sockfd = socket(AF_INET, SOCK_STREAM,0);
	if(sockfd < 0){
		error("Error opening socket");
	}
	
	
	memset(&sockaddr, 0, sizeof(sockaddr));
	
	portno = atoi(argv[1]);
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_addr.s_addr = INADDR_ANY;
	sockaddr.sin_port = htons(portno);
	
	if(bind(sockfd, (struct sockaddr *) &sockaddr, sizeof(sockaddr))<0){
		error("Error binding");
	}
	
	listen(sockfd, 4);
	
	clilen = sizeof(cliaddr);
	
	newsockfd = accept(sockfd, (struct sockaddr *) &cliaddr, &clilen);
	
	if(newsockfd<0){
		error("Error connecting");
	}
	//code
	
	printf("Enter the data to be sent to the receiver : ");
	scanf(" %s", data);
	data_length = strlen(data);
	printf("\n-----------------\n");
	printf("\nData received : %s",data);
	append();
	printf("\nData after appending is : %s",data);
	crc();
	check_value[N]='\0';	
	printf("\n------------------\n");
	printf("\nThe check value or CRC is : %s ",check_value);
	crc_append();
	printf("\n------------------\n");
	printf("\nThe final data to be sent is : %s\n", data);

	check = write(newsockfd, data, strlen(data)+1);
	if(check<0){
		error("Error sending data");
	}	
	
	
	
	
	
	
	
	
	close(newsockfd);
	close(sockfd);
	return 0;
	
		
}

