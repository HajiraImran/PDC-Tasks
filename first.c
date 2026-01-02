#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>


#define NUM_CUSTOMERS 5

sem_t hairstylist; 
sem_t makeupArtist; 

void* customer(void* arg) {
    int id = *(int*)arg;

    int service = rand() % 3; //1=hair , 2=makeup, 3=both



if(service==1){
    sem_wait(&HAIR_STYLIST);
    printf("Customer %d getting hairstyling.\n", id);
    sleep(1);
    sem_post(&hairstylist);
} 
else if(service==2){
    sem_wait(&makeupArtist);
    printf("MakupArtist %d is busy.\n", id);
    sleep(1);
    sem_post(&makeupArtist);
}
 else{
    sem_wait(&makeupArtist); //both makeup ho ga and then hair
    printf("Customer %d getting makeup(1).\n", id);
    sleep(1);
    sem_post(&makeupArtist);

    
    sem_wait(&hairstylist); //both makeup ho ga and then hair
    printf("Customer %d getting hairstyling(2).\n", id);
    sleep(1);
    sem_post(&hairstylist);

 }

 pthread_exit(NULL); 
}

int main() {
    pthread_t customer[NUM_CUSTOMERS];
    int ids[NUM_CUSTOMERS];
    sem_init(&hairstylist, 1 , 3);
    sem_init(&makeupArtist, 1 , 2);

    for (int i = 0; i < NUM_CUSTOMERS; i++) {
        ids[i] = i + 1;
        pthread_create(&customer[i], NULL, customer, &ids[i]);
        sleep(1); 
    }

    for (int i =0; i<NUM_CUSTOMERS; i++){
        pthread_join([i], NULL);
    }
 
sem_destroy(&hairstylist);
sem_destroy(&makeupArtist);

return 0;
}



