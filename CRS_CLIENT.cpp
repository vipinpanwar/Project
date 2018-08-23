#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include<sys/stat.h>
#include<iostream>
#include<map>
#include<iterator>
#include <fstream>
#include <vector>

#include <string>
#include <cstdlib>
using namespace std;
 ofstream ofile;
ifstream ifile;
/*for sendfile()*/
#include<sys/sendfile.h>

/*for O_RDONLY*/
#include<fcntl.h>
char sends[1000];
int mg=0;

void * receive(void * socket)
{
    int sockfd,status, n,i,filehandle,size=0,c=0;
    char rbuffer[1000],command[10],filename[100],*f;
    sockfd = (intptr_t) socket;
	struct stat obj;
    memset(rbuffer, 0, 1000);
	
   while(1)
{	
	int ch=0;
cout<<"\nPress 1 to get a file ";
cout<<"\n\t\tor";
cout<<"\nPress 2 to search for a file and get the ip";
cout<<"\nPress 3 to share a file";
cout<<"\nPress 4 to Broadcast message";
cout<<"\nPress 5 to exit";
cout<<"\nEnter your choice\n";
	scanf("%d",&ch);

	memset(&command,0,100);
	memset(&rbuffer,0,100);
     	memset(&sends,0,sizeof(sends));
	memset(&filename,0,sizeof(sends));
	if(ch==4){
	
	mg=1;
	strcpy(sends,"msg\n");
	write(sockfd, sends,100);
	memset(sends,0,sizeof(sends));


	puts("*********please write 'outt' to come out to main menu");
	while(fgets(sends,100,stdin)!=NULL)
{
		
	write(sockfd, sends,100);
	sscanf(sends,"%s",command);
	if(strcmp(command,"outt")==0){mg=0;break;}
	memset(sends,0,sizeof(sends));

}
	mg=0;

}

	if(ch==2){
	size=0;
	strcpy(sends,"search\n");
	write(sockfd, sends,100);
	puts("\nEnter file name that you want to search\n");
	cin>>filename;
	puts("searching\n");
	
	
	write(sockfd,filename,100);
	for(int i=0;i<3;i++){
	sleep(1);
	puts(".");
	}
	cout<<endl;
	read(sockfd, rbuffer, 1000);
	cout<<">>"<<rbuffer;


}
if(ch==3){
	size=0;
	strcpy(sends,"put\n");
	write(sockfd, sends,100);
	puts("in put\n");
	 printf("Enter filename to put to server: ");
          scanf("%s", filename);
	//puts(filename);
	  filehandle = open(filename, O_RDONLY);
          if(filehandle == -1)
            {
              printf("No such file on the local directory\n\n");
		write(sockfd,"not\n",100);
    
            }
	else

{	
	puts(filename);
	  write(sockfd,filename, 100);
	  stat(filename, &obj);
	  size = obj.st_size;
	cout<<size;
	  send(sockfd, &size, sizeof(int), 0);
	puts(" size send\n");	 
        sendfile(sockfd, filehandle, NULL, size);
	  recv(sockfd, &status, sizeof(int), 0);
	  if(status)
	    printf("File stored successfully\n");
	  else
	    printf("File failed to be stored to remote machine\n");

	memset(&sends,0,100);
}

}
if(ch==5){
puts("inside quit\n");
	 	memset(&sends,0,sizeof(sends));

	strcpy(sends,"quit\n");
	
write(sockfd, sends,100);
exit(1);

}

	if(ch==1){
	     	memset(&sends,0,sizeof(sends));


	size=0;
	strcpy(sends,"get\n");
	write(sockfd, sends,100);
	 puts("Enter filename to get: \n");
	  scanf("%s", filename);
	  write(sockfd,filename,100);
	printf("size = %d\n",size);
	recv(sockfd,&size,sizeof(int), 0);
	printf("size received =%d\n",size);
if(size){  	
	f = (char*)malloc(sizeof(char)*size);
	  recv(sockfd, f, size, 0);

}
cout<<size;

if(size){
while(1)
	    {
	      filehandle = open(filename, O_CREAT | O_EXCL | O_WRONLY, 0666);
	      if(filehandle == -1)
		{
		  sprintf(filename + strlen(filename), "%d", i);//needed only if same directory is used for both server and client
		}
	      else break;
	    }
	  }	
if(size)
{
	c=write(filehandle, f, size);
	printf("c=%d\n",c);
	  close(filehandle);
	puts("successful***");
}
else
puts("file not found");
}

   memset(&sends,0,100);
}
}
int main(int argc, char *argv[])
{
memset(&sends,0,100);

	int sockfd = 0, n = 0;
    char recvBuff[1024];
	int temp;
    struct sockaddr_in serv_addr;
	int listenfd = 0;
	char s[100];
	pthread_t threads1, threads2;
	pthread_attr_t pthread_receive;

	int *p;
    if(argc != 2)
    {
        printf("\n Usage: %s <ip of server> \n",argv[0]);
        return 1;
    }

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    }

    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000);
	printf("Server address used is: %s\n", argv[1]);
    if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr)<=0)
    {
        printf("\n inet_pton error occured\n");
        return 1;
    }

    if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
		printf("\n Error : Connect Failed \n");
		return 1;
    }

	pthread_attr_init(&pthread_receive);
	n=pthread_create(&threads1,&pthread_receive,receive,(void *) (intptr_t)(sockfd));

	if(n<0)
{
		printf("error in creating thread");
}


	while(1)

{

char cbuffer[1000]; 
		if(mg){
	
	


    memset(cbuffer, 0, 1000);  
   while(1)
     {
      n = read(sockfd, cbuffer, 1000);  
	if(mg==0)break;
      if (n < 0)   
      printf("Error receiving data!\n");    
      else
       {
        printf(" Broadcast message \n : ");
        fputs(cbuffer, stdout);
	printf("\n\n");
       }  
     
	
}
	
   memset(&sends,0,100);

}

}


   	return 0;
}
