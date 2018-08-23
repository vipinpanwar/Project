#include <sys/socket.h>
#include<iostream>
#include<string>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <pthread.h>
#include<thread>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include<sys/stat.h>
#include<map>
#include<iterator>
#include <fstream>
using  namespace std;
/*for sendfile()*/
#include<sys/sendfile.h>
/*for O_RDONLY*/
#include<fcntl.h> 

ofstream ofile;
ifstream ifile;
	
char buffer[1000],command[100],filename[100],*f;;
char rbuffer[1000]; 	
int connfd[100];int ii=0,filehandle=0,size=0;
struct stat obj;

int k=0;
void * receive(void * socket) 
   {
    int sockfd, n;
	 
    sockfd =(intptr_t)socket;
    memset(rbuffer, 0, 1000);  
	while(1)     {
	 memset(&rbuffer, 0, 1000);
       	 memset(&command, 0, 100);
         memset(&filename,0,100);
 	 n = read(sockfd, rbuffer, 1000);  
          sscanf(rbuffer,"%s",command);

   if (n < 0)   
       printf("Error1!\n");    
/* **********************************************************QUIT*********************************************************************** */


	if(strcmp(command,"quit")==0)
	{puts("inside quit\n");

	int ret=1;
	int a[10];
	for(int i=0;i<10;i++)if(sockfd!=connfd[i])a[i]=connfd[i];
	for(int i=0;i<10;i++)connfd[i]=a[i];
	pthread_exit(&ret);

}
/* **********************************************************QUIT_END********************************************************************** */

/* **********************************************************MESSAGE*********************************************************************** */

	if(strcmp(command,"msg")==0)
	{
	puts("inside msg");
	
	while(1){
       	memset(&command, 0, 100);	
	memset(&rbuffer, 0, 1000);
	n = read(sockfd, rbuffer, 1000);  
	 sscanf(rbuffer,"%s",command);
	if(strcmp(command,"outt")==0){puts("out success");break;};
        printf("from : ");
        fputs(rbuffer, stdout);
	
	for(int i=0;i<k;i++)
{
	int p = write(connfd[i], rbuffer, 100);  
     /* if (p < 0)
       {  
        printf("Error in sending data ...\n");  
	}
*/
}
}
}
/* **********************************************************MESSAGE_END*********GET_START************************************************** */



	if(strcmp(command,"get")==0)
	{

	printf("In child of fork\n");
	puts("get operation\n");
	read(sockfd, rbuffer, 1000);
	printf("%s\n",rbuffer);
	sscanf(rbuffer, "%s", filename);
	stat(filename, &obj);

	filehandle = open(filename, O_RDONLY);

	size=0;
if(filehandle>0){

	size = obj.st_size;
}
	send(sockfd,&size,sizeof(int),0);

	 if(filehandle == -1)
	{

	      size = 0;
		puts("no such file directory");
 		printf("size = %d\n",size);

	}
if(size)
{

	printf("size = %d\n",size);
	sendfile(sockfd, filehandle, NULL, size);
	 puts("ok\n");

}
	else
	puts("bad\n");
}
/* **********************************************************GET_END*******PUT_START***************************************************** */
 if(!strcmp(command, "put"))
        {
		
	 memset(&rbuffer, 0, 1000);
       	 memset(&command, 0, 100);
	  int c = 0, len;
	puts("in puts");
	read(sockfd, rbuffer, 1000);
	  sscanf(rbuffer, "%s", filename);
	 sscanf(filename,"%s",command);
/**********************************************************************write to file********************************************************/
	

ofstream file;
   

    file.open("nfile.txt",ios::app);
    if(!file)
    {
      puts("file not found/n");           //file does not exist and cannot be created.
    }
file<<filename;
file<<"\n";
file.close();


/**********************************************************************write to file********************************************************/
		  
if(strcmp(command,"not")){
puts("working puts\n");
	

	recv(sockfd, &size, sizeof(int), 0);
	puts(command);
	int  i = 1;
   filehandle = open(filename, O_CREAT | O_EXCL | O_WRONLY, 0666);

	  f = (char *)malloc(sizeof(char)*(size));
	  recv(sockfd, f, size, 0);
	puts("btw");	
	  c = write(filehandle, f, size);
	  close(filehandle);
	  send(sockfd, &c, sizeof(int), 0);

}
}
/* **********************************************************PUT_END*****FILE_SEARCH**************************************************** */

if(strcmp(command,"search")==0){



	puts("inside the search\n");
	read(sockfd, rbuffer, 1000);
	printf("%s\n",rbuffer);
///////////////////////////starts
ifile.open("nfile.txt");
if(!ifile.is_open())
{
exit(EXIT_FAILURE);
}
char buffer[100];
string str;
string line;
int offset,i;
string word1,word2;
char x,y;

str=rbuffer;
cout<<str;
offset=str.length();
int length,success=0;
cout<<"searching out\n";
while(getline(ifile,line))
{
for(i=0;i<line.length();i++)
{
y=line[i];
if(y!='|')
{
word2=word2+y;
}
else
{break;}

}
word1=line.substr(0,offset);
if(word1==str)
{
for(i=0;i<word2.length();i++){
buffer[i]=word2[i];

}
if(word1==str){
success=1;
break;
}
//for(i=0;i<word2.length();i++){
//cout<<buffer[i];
//}
}
else
{
word2="";
}

}

//printf("word2=%s",word2);

for(i=0;i<str.length();i++){
printf("%c",buffer[i]);
}
if(success)
write(sockfd, rbuffer,100);
else
write(sockfd,"file not found\n",100);

puts("search complete\n");
ifile.close();
////////////////////////////ends
}

/* **********************************************************PUT_END*****FILE_SEARCH**************************************************** */

 memset(&rbuffer, 0, 1000);
 memset(&command, 0, 100);
	
}
	
}
int main(int argc, char *argv[])
{	
	int n=5;	
	pthread_t *threads;
	threads=(pthread_t*)malloc(n*sizeof(*threads));

	
    int listenfd = 0;
    struct sockaddr_in serv_addr; 
	char s[100];
    	char sendBuff[1025];
	char sends[100];
	char recvBuff[1024];
 
	
	pthread_attr_t pthread_receive,pthread_send;	   	

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff)); 
	
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5000); 
	
    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 
    listen(listenfd, 10); 
	memset(&sends, '0', sizeof(sends));
  	
	pthread_attr_init(&pthread_receive);	
	
	while(connfd[ii] = accept(listenfd, (struct sockaddr*)NULL, NULL))

	{

	//write(connfd[ii], "connection established start chat\n", 40);
	pthread_create(&threads[ii], &pthread_receive, receive, (void *)(connfd[ii]));
	ii++;
	k++;

	}
 for (int j = 0; j <10 ; j++)
     {
        pthread_join (threads [j], NULL);
     }

	
	while(1);
        sleep(1);
}
