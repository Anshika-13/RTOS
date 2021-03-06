#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>

int player = 0;
int position[4] = {0,0,0,0};
int winner = 0;
pthread_t tid[4];
pthread_mutex_t lock[4], mlock;

int snake[5] = {12, 38, 55, 74, 99};
int snake_final[5] = {2, 13, 20, 54, 67};
int ladder[5] = {6, 36, 52, 83, 89};
int ladder_final[5] = {23, 51, 73, 97, 95};

struct timeval end, start;

void close_handle(){ exit(0); }
void close_final(){

	// printf("In close_final\n\n");

	for (int i=0;i<4;i++) {
		pthread_mutex_destroy(&lock[i]); //destroying the lock
		// printf("destroying lock: %d\n", i);
	}
	pthread_mutex_unlock(&mlock);
	pthread_mutex_destroy(&mlock);

	// exit(0);

}

void* trythis(void *arg) {
	// printf("Hello\n");
	while (1) {

		pthread_mutex_lock(&lock[player]); //entering critical section
		// printf("Hello\n");

		// printf("Player: %d\n", player);
		srand(time(NULL));
		int dice = (rand()%6) + 1;
		position[player] = position[player] + dice; //rolling the dice
		// printf("dice: %d, Position: %d\n", dice, position[player]);

		for (int i =0; i<5; i++) { //checking for snakes/ladders, updating position accordingly
			if(position[player] == snake[i])
				position[player] = snake_final[i];
			else if (position[player] == ladder[i])
				position[player] = ladder_final[i];
		}
		// printf("dice: %d, Position, after snake/ladder: %d\n", dice, 
		// 	position[player]);

		if (position[player] > 99) { //checking for a win
			winner = player;
			printf("Player %d won\n", winner);
			printf("Final positions: Player0: %d, Player1: %d, Player2: %d, Player3: %d\n", position[0], position[1], position[2], position[3]);

			gettimeofday(&end, NULL); 
			long seconds = (end.tv_sec - start.tv_sec); //time when output recieved
		    long micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
		    printf("Time elpased is %lu seconds and %lu micros\n", end.tv_sec - start.tv_sec, micros);//final time
			
			close_handle();
		}

		if (player != 3) //updating player number
			player = player + 1;
		else if (player == 3)
			player = 0;
		// printf("Player (updated): %d\n", player);

		pthread_mutex_unlock(&lock[player]); //exiting critical section
	}
	return NULL;
}

void print_name() {
	for(int i=0;i<4;i++) {
		// printf("In main, creating thread: %d\n", i);
		if (pthread_create(&(tid[i]), NULL, &trythis, &(tid[i])) != 0)
			printf("Thread creation error\n"); 
	}
	// printf("Hello\n\n");
	pthread_mutex_lock(&mlock);
	// printf("Hello\n\n");

}

int main() {
	gettimeofday(&start, NULL); // Store time as soon as message sent
	if (pthread_mutex_init(&mlock, NULL) != 0)
		printf("Mutex init error\n");
	for(int i=0;i<4;i++) {
		if (pthread_mutex_init(&lock[i], NULL) != 0)
			printf("Mutex init error\n");
		// pthread_mutex_lock(&lock[i]); //entering critical section
	}

	print_name(); //call the coroutine

	pthread_mutex_lock(&mlock);

	// for (int i=0;i<4;i++) {
	// 	pthread_join(tid[i], NULL);
	// }

	close_final();

    return 0;
}
