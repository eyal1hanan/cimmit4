#include <stdio.h>
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#include <sys\stat.h>
#define chunk (5*1024) 



void copy_folder(char *src, char *dest)
{
	WIN32_FIND_DATAA info ;
	HANDLE hwnd ;
	char temp[1000] = "" ;
	char temp_1[1000] = "" ;

	char temp_src[1000] ;
	char temp_dest[1000] ;

	int in, out, i, x ;
	void *buffer ;

	strcpy(temp_1, src) ;
	strcat(temp_1, "\\*.*") ;

	//SECURITY_ATTRIBUTES s ;

	CreateDirectoryA(dest,NULL) ;

	hwnd = FindFirstFileA(temp_1, &info) ;
	do{
		if (!strcmp(info.cFileName , ".")) continue ;
		if (!strcmp(info.cFileName , "..")) continue ;

		strcpy(temp_src, src) ;
		strcat(temp_src, "\\") ;
		strcat(temp_src, info.cFileName) ;

		if (info.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY){

			strcpy(temp_dest, dest) ;
			strcat(temp_dest, "\\") ;
			strcat(temp_dest, info.cFileName) ;
			//CreateDirectory(temp_dest, NULL) ;
			copy_folder(temp_src, temp_dest) ;

		}else{
			strcpy(temp, dest) ;
			strcat(temp, "\\") ;
			strcat(temp, info.cFileName) ;
			printf("%s\n", temp) ;
			//copy_file(temp_src, temp)

			buffer = malloc(chunk) ;
			in = (int)open(temp_src, O_RDONLY|O_BINARY) ;
			out = (int)open(temp, O_CREAT|O_WRONLY|O_BINARY|O_TRUNC) ;
			printf("%s %s\n", temp_src, temp) ;
			while (i = read(in, buffer, chunk)){
				//printf("%s\n", buffer) ;
				x = write(out, buffer, i) ;
				//printf("%d %d\n", x, i) ;
			}
			close(in) ;
			close(out) ;
			free(buffer) ;

		}



	}while (FindNextFileA(hwnd, &info)) ;
	FindClose(hwnd) ;
}

int main()
{
	char src[1000] = "\\\\172.24.1.243\\public\\Eyalh\\old\\old1\\Tools\\x64" ;
	char dest[1000] = "C:\\temp\\x86" ;


	copy_folder(src, dest) ;

	return 0 ;

}