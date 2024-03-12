#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netdb.h>
#include<netinet/in.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>

#define N strlen(gen_poly)

char data[30];
char gen_poly[10]="1001";
int data_length, i, j;
char check_value[28];


void error(char * msg){
	perror(msg);
	exit(1);
}

void XOR(){
	for(j=1; j<N; j++)
		check_value[j]=((check_value[j] == gen_poly[j])?'0':'1');
	
}

void append(){
	for(i=data_length; i<data_length+N-1; i++){
		data[i] = '0';
	}
	data[i]='\0';
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



int main(int argc, char *argv[]){
	
	if(argc<3){
	fprintf(stderr,"Please provide hostname and portno");
	exit(1);
	}

	int sockfd, portno, check, K;
	struct sockaddr_in serv_addr;
	struct hostent * server;
	
	sockfd = socket(AF_INET, SOCK_STREAM,0);
	if(sockfd<0){
	error("Error opening socket");
	}
	
	server = gethostbyname(argv[1]);
	if(server == NULL){
		error("Please provide the correct hostname");
	}
	
	memset(&serv_addr, 0, sizeof(serv_addr));
	portno = atoi(argv[2]);
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(portno);
	
	if(connect(sockfd,(struct sockaddr *) &serv_addr, sizeof(serv_addr))<0){
		error("Error connecting");
	}
	
	//code
	memset(data,'\0',sizeof(data));
	memset(check_value,'\0',sizeof(check_value));
	check = read(sockfd, data, sizeof(data));
	if(check<0){
		error("Error reading from server");
	}
	
	printf("Data received from server is : %s\n", data);
	data_length = strlen(data);
	printf("%d\n",data_length);
	append();
	printf("%s\n",data);
	crc();
	check_value[N]='\0';
	printf("Check Value or CRC is:%s\n",check_value);
	

	for(i = 0;i<N && check_value[i]=='0';i++);
	if(i<N-1){
		printf("\nError detected\n");
	}
	else{
		printf("No error\n");
		for(j=data_length-N+1;j<data_length;j++){
			data[j]='\0';
		}
		printf("Data after truncating the zeros is : %s\n",data);
	}
	
	
	
	
	
	
	close(sockfd);
	return 1;
	}

