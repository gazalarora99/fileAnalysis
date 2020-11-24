#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <fcntl.h>
void directory_handler(void* arg);
void directory_handler(void* arg){
struct dirent *dir;
 DIR *D = opendir((char*)arg);
  int direcs=0, files=0;
  if (D == NULL){
    printf("can't open the current directory\n" );
    return;
  }
  while ((dir = readdir(D)) != NULL) {
    if(strcmp((char*)dir->d_name,".")==0 || strcmp((char*)dir->d_name,"..")==0){
      continue;
     }
    if(dir->d_type==DT_REG){
      files++;
      printf("File %d's name: %s\n", files, dir->d_name);
    }
    else if(dir->d_type==DT_DIR){
      direcs++;
      printf("Directory %d's name: %s\n", direcs, dir->d_name);
      //char* args = (char*)arg;
      char* oldarg;
      strcpy(oldarg, (char*)arg);
	//[strlen((char*)arg)];
      //for(int i = 0; i < strlen(oldarg); i++){
      //oldarg[i] = args[i];
      //}
      //char* args = (char*)arg;
      //oldarg = &args;
      strcat((char*)arg,"/");
      strcat((char*)arg,dir->d_name);
      printf("going to subdir %s\n", (char*)arg);
      directory_handler((void*)arg);
      //arg = (void*)(*oldarg);
      //for(int i = 0; i < strlen(oldarg); i++){
      //args[i] = oldarg[i];
      //}
      strcpy((char*)arg, oldarg);
      printf("back to original arg %s\n", (char*)arg);
    }
    else{
      continue;
    }
  }
  closedir(D);
}

int main(int argc, char** argv){
  directory_handler((void*)argv[1]);  
}
