#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

#include <cstdio>
#include <cstdlib>
#include <fstream>	
#include <string.h>
#include <unistd.h>

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

    char buffer[shmSize];
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

    ofstream file;
    file.open("output.txt");    

    if(semop(semId, c, 2) != -1){
        strcpy(buffer, sharedMem);
        output << buffer;
        output.close();
        if(semop(semId, r, 1) != -1){
          //release semaphor
          sleep(1);
        }
        else{
          perror("semop(release)");
        }
    }
    else{
        perror("semop(control)");
    }
}