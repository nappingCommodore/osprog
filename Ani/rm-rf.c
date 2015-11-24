#include<stdio.h>
#include<dirent.h>
#include<sys/stat.h>
#include<unistd.h>
#include<string.h>
struct stat mystat;
char path[10000];
void recurse_rem(DIR * dp,char * dpath)
{
	printf("called\n");
	int len;
	struct dirent * myfile;
	DIR * temp;
	while((myfile=readdir(dp))!=NULL)
	{
		printf("%s\n",myfile->d_name);
		if(myfile->d_name[0]=='.')
			continue;
		strcpy(path,dpath);
		strcat(path,"/");
		strcat(path,myfile->d_name);
		if(stat(path,&mystat)==0)
		{
			if(S_ISDIR(mystat.st_mode)==1)
			{
			 	len=strlen(dpath);
				strcat(dpath,"/");
				strcat(dpath,myfile->d_name);
				if((temp=opendir(dpath))==NULL)
					printf("error while opening %s",dpath);
				else
				{
					recurse_rem(temp,dpath);
					dpath[len]='\0';
				}
			}
			else
			{
				len=strlen(dpath);
				strcat(dpath,"/");
				strcat(dpath,myfile->d_name);
				if(remove(dpath)==-1)
					printf("error\n");
				dpath[len]='\0';
			}

		}
		else
			continue;
	}
	closedir(dp);
	remove(dpath);
}
int main(int argn,char * argc[])
{
	char cwd[1000];
	DIR * dp;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		strcat(cwd,"/");
		strcat(cwd,argc[1]);
	}
	else
	{
		printf("error while getting cwd\n");
	}
	if(argn==1)
	{
		printf("No commands to run\n");
		return 0;
	}
	else
	{
		dp=opendir(cwd);
		if(dp!=NULL)
		{
			recurse_rem(dp,cwd);
		}
		else
		{
			printf("Error while deleting %s\n",argc[1]);
			return 0;
		}
	}
}