#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/types.h>
#define bufsize 1024
#define shcall "echo \"Enter the first number\"\n\
read a\n\
echo \"Enter second Number\"\n\
read b\n\
echo \"Enter the operation you want to perform\"\n\
read op\n\
case $op in\n\
add) echo `expr $a + $b`\n\
;;\n\
sub) echo `expr $a - $b`\n\
;;\n\
mul) echo `expr $a \* $b`\n\
;;\n\
esac"

void  parse(char *cmd, char **argval)
{
     while (*cmd != '\0') 
     {      
          while (*cmd == ' ' || *cmd == '\t' || *cmd == '\n')
			  *cmd++ = '\0'; 
          *argval++ = cmd;          
           while (*cmd != '\0' && *cmd != ' ' && *cmd != '\t' && *cmd != '\n') 
               cmd++;          
     }
     *argval = '\0';                 
}
void execute(char **argval)
{
     pid_t  pid;
     int    status;

     if ((pid = fork()) < 0) {     
          printf("*** ERROR: forking child process failed\n");
          exit(1);

     }
     else if (pid == 0) {         
          if (execvp(*argval, argval) < 0) {    
               printf("*** ERROR: exec failed\n");
               exit(1);         
	  }
     }
     else {                                  
          while (wait(&status) != pid)      
               ;

     }
     return 0;
}
int main()
{
	char cmd[100],str[bufsize],fname[25],s[100],*argval[64];;
	int l;
	printf("List of Commands\n");
	printf("1. print\n2. read\n3. remove\n4. exit\n5. chdir\n6. Calculator \n7. UNIX System Commands\n");
	while(1)
	{	
		printf("\nEnter your Command>>\t");
		gets(cmd);
		fflush(stdin);
		parse(cmd, argval);
		if(strcmp(cmd,"read") == 0)
		{
			l=read(1,str,sizeof(str));
		}
		else if(strcmp(argval[0],"print") == 0)
		{
				if(argval[1]=='\0')
			    {	l=read(1,str,sizeof(str));
					write(1,str,l);
				}
				else
				{
					printf("%s",argval[1]);
				}			
		}
		else if(strcmp(cmd,"remove") == 0)
				{
					printf("Current Working Directory is %s\nEnter the file name you want to remove\n",getcwd(s,100));
					scanf("%s",fname);
					if(unlink(fname) == -1)
						perror(" ");
					else	
						printf("File removed Successfully\n");
				}

		else if(strcmp(cmd,"chdir") == 0)
						{
							printf("Current Working Directory is %s\n",getcwd(s,100));
							scanf("%s",str);
							fflush(stdin);
							chdir(str);
							printf("%s\n",getcwd(s,100));
						}
		else if(strcmp(cmd,"exit") == 0)
						break;
		else if(strcmp(cmd,"calc") == 0)
				system(shcall);
		else
		{
			
			execute(argval);
			
				
		}				
	}
}


