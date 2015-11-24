#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>


struct dirent 	*dp;
struct stat	 statbuf;
struct passwd	*pwd;
struct group	*grp;
struct tm	*tm;
char		 datestring[256];
DIR* dir;

int main(){
	dir = opendir(".");
	while((dp = readdir(dir)) != NULL){
		if(stat(dp->d_name, &statbuf) == -1)
			continue;
			
		
	}

}
