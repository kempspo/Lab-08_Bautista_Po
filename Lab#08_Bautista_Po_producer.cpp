#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <string.h>

using namespace std;

int main( int argc, char* argv[] )
{
    if(argc != 3 ){
    	perror("invalid number of args");
    	exit(1);
    }


    int semId, shmId;
    key_t semKey = 1234, shmKey = 5678;
    char* sharedMem;
    string sfile = argv[1];
    int shmSize = atoi(argv[2]);
    int nSems = 1;
    int semFlag = IPC_CREAT | 0666; //just use semflag for both shmflag

    //create semaphore
    semId = semget( semKey, nSems, semFlag );
    if( semId == -1 )
    {
        perror( "semget" );
        exit( 1 );
    }

    //create shared memory
    shmId = shmget( shmKey, shmSize, semFlag ); 
    if( shmId == -1 )
    {
    	perror("shmget");
    	exit( 1 );
    }

    sharedMem = (char*)shmat( shmId, NULL, 0 );

    if( ((int*)sharedMem) == (int*) -1 )
    {
    	perror( "shm attach failed" );
    } 

    struct sembuf c[2];
    struct sembuf r[1];

    c[0].sem_num = 0;
    c[0].sem_op = 0; // wait 
    c[0].sem_flg = SEM_UNDO;

    c[0].sem_num = 0;
    c[0].sem_op = 1; // increment
    c[0].sem_flg = SEM_UNDO | IPC_NOWAIT;

    r[0].sem_num = 0;
    r[0].sem_op = -1; // decrement 
    r[0].sem_flg = SEM_UNDO | IPC_NOWAIT;

    ifstream file;
    file.open(sfile);

    if( !file.is_open()){
    	perror("file can't be opened");
    }

    const char* buffer;
    const char* line;
    char* temp;
    string in;
    string tempL = "";

    while(getline(file,in))
    {
    	tempL += in + "\n";
    }

     line = tempL.c_str();
  		if(semop(semId, c, 2) != -1){
			buffer = line;
	  		strcpy(sharedMem, buffer);
  			if(semop(semId, r, 1) != -1){
  				sleep(1);
  			}
  			else{
  				perror("semop(release)");
  			}
  		}
  		else{
  			perror("semop(control)");
  		}
    file.close();
   
}

