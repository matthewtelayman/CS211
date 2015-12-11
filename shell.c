//Matt Layman CS211 shell.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

//global constants
#define COMMAND_SIZE 100
#define ARGUMENT_SIZE 50
#define HISTORY_CAPACITY 10
#define FALSE 0
#define TRUE 1

//function protoypes
void GetCommand(char *command);
void ParseCommand(char *command, char **args);
int ExecuteCommand(char **args);
void MonitorChildProcess();
int CheckForContinue(char *command);
void AddToHistory(char **history, char *command, int *list_size);
void PrintHistory(char **history, int *list_size);

int main()
{
 
  int history_size = 0;       //size of history list
  char command[COMMAND_SIZE];  //string for most recent command
  char *arguments[ARGUMENT_SIZE]; //array of arguments to send to exec
  char *history[HISTORY_CAPACITY]; //array of strings for history

 
  //set all array values to null
  memset(command,'\0',COMMAND_SIZE - 1);
  memset(arguments,'\0',ARGUMENT_SIZE - 1);
  memset(history, '\0',HISTORY_CAPACITY - 1);
 
 
 
  GetCommand(command);   //get command from user
  AddToHistory(history,command, &history_size);//add most recent command to history
 
  //while command is not "exit" or "logout" or command is newline get and process commands
  while(CheckForContinue(command) == TRUE || command[0] == '\n')
    {
      
      if(command[0] != '\n' && strcmp("history",command) != 0)
    {
      
      ParseCommand(command,arguments); //populate arguments array
      int child_pid = fork();   //fork child process to make call to exec
       switch(child_pid)
         {
         case 0: /*child process*/
           ExecuteCommand(arguments);
           break;
         case -1:
           perror("Error: command cannot be executed");
           exit(1);
         default:/*parent process*/
           MonitorChildProcess(child_pid);//check to see that child process executes
           break;                
           }
     }
      else
    {
      //print history
      PrintHistory(history, &history_size);
      
    }

      //get new command
       
       GetCommand(command);
       AddToHistory(history,command,&history_size);
       memset(arguments,'\0',ARGUMENT_SIZE - 1); //the next command may have fewer characters than the last
      
    }

   
      
  exit(0);

}

void GetCommand(char *command)
{

    memset(command,'\0',COMMAND_SIZE - 1);
    char *endline;    //pointer to a character in command
    int strLength;
    

   
    printf("myshell->");

    if((fgets(command,COMMAND_SIZE,stdin)) == NULL)
    {
      printf("command failed!\n");
    }

    // if user entered command, replace newline with '\0'
    else if(command[0] != '\n' && (endline = strchr(command, '\n')) != NULL)
       {
       *endline = '\0';
      
       }
 
}

void ParseCommand(char *command, char **args)
{
  char *tokenPtr;
  int i = 0;
    
  tokenPtr = strtok(command," ");
  while(tokenPtr != NULL)
    {
       args[i++] = tokenPtr;
       tokenPtr = strtok(NULL," ");
       }
 
}

int ExecuteCommand(char **args)
{    
  execvp(args[0],args);
  perror("Error: Invalid command. Make sure your command, options, or file arguments are correct.\n");
  exit(1);
}

void MonitorChildProcess(int child_pid)
{
  int received_pid, status;
    
    while(received_pid = wait(&status))
      {
    if(received_pid == child_pid)
      {
        break;
      }
    if(received_pid == -1)
      {
        perror("error while waiting for child process to execute command");
        return;
      }
      }

    if(WIFEXITED(status) == 0)
      {
    printf("child process exited with value %d\n", WEXITSTATUS(status));
      }
}

int CheckForContinue(char *command)
{
 
  if((strcmp("exit",command) == 0) || (strcmp("logout",command) == 0))
    {
      return FALSE;
    }
   
  else
    {
      return TRUE;
    }
}

void AddToHistory(char **history, char *command, int *list_size)
{
  //keep track of where to add the next string in the array
  int index_to_access = *(list_size);
 

  if(command[0] != '\n')
    {
      //if statement stub
      if(index_to_access ==  HISTORY_CAPACITY - 1)
    {
      printf("Start taking away oldest entries from the list now\n");
    }
      else
    {  //copy command into history array
      history[index_to_access] = (char *)malloc(sizeof(char)*COMMAND_SIZE);
      strdup(history[index_to_access], command);
      free(history[index_to_access])
      index_to_access++;
         }
    }

 
  *(list_size) = index_to_access;
 
}

void PrintHistory(char **history, int *list_size)
{
  int size = *(list_size);
  int i = 0;
  for(i = 0; i <= size; i++)
    {
      printf("%d. %s\n", i+1, history[i]);
    }
}
