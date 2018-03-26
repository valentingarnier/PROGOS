/* ====================================================================
 * 
 * Valentin Garnier
 *	                                                                    
 * Exercice snake.c du cours
 * Programmation Orientee Systeme de M. Chappelier (Sections IN et SC).
 *                                                                     
 * Si vous avez ncurses (libcurses-dev), compilez avec
 *  -DUSE_CURSES et -lncurses ; par exemple :
 * gcc -ansi -pedantic -Wall -DUSE_CURSES snake.c -o snake -lncurses
 *                                                                     
 * ====================================================================
 */
#include <stdio.h>
#include <stdlib.h>

#ifdef USE_CURSES
#include <curses.h>
#define printf printw
#else
#define printw printf
#endif

/***************************************************************
 * Here come the data definitions 
 *  (to be done by the students)
 ***************************************************************/

typedef struct direction_t direction_t;
struct direction_t {
	unsigned int dx;
	unsigned int dy;
};

typedef struct segment_t segment_t;
struct segment_t {
	unsigned int x;
	unsigned int y;
	unsigned length;
	direction_t direction;
	segment_t* previous;
};

#define MAX_NUMBER_OF_SEGMENT 10
typedef struct snake_t snake_t;
struct snake_t {
	segment_t* tail;
	segment_t* head;
};

typedef enum map_cell_t map_cell_t;
enum map_cell_t { EMPTY, WALL, FOOD, SNAKE };

typedef struct game_t game_t;
struct game_t {
	snake_t snake;
	unsigned int width;
	unsigned int height;
	map_cell_t* map;
};

//PROTOTYPES DES FONCTIONS

void snake_info(const snake_t*);
void snake_erase_tail(snake_t*);
void snake_destroy(snake_t*);
int snake_add_segment(snake_t*, direction_t);
int snake_move(snake_t*, direction_t);
map_cell_t* cell(game_t*, unsigned int, unsigned int);
int game_update(game_t*, direction_t);
int game_init_snake(game_t*, unsigned int, unsigned int);

//FIN DES PROTOTYPES

/****************************************************************
 * This is the given game map. 
 ****************************************************************/
#define MAP_WIDTH  80
#define MAP_HEIGHT 25

static map_cell_t const header_data[] = {
	WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,
	WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,
	WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,
	WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,
	WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,
	WALL,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
	EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
	EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
	EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
	EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL,
	WALL,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
	EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
	EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
	EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
	EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL,
	WALL,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
	EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
	EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
	EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
	EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL,
	WALL,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
	EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,FOOD,
	FOOD,FOOD,FOOD,FOOD,FOOD,FOOD,FOOD,FOOD,FOOD,FOOD,FOOD,FOOD,EMPTY,EMPTY,EMPTY,EMPTY,
	EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
	EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL,
	WALL,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
	EMPTY,EMPTY,EMPTY,FOOD,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
	EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
	EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,FOOD,FOOD,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
	EMPTY,EMPTY,FOOD,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL,
	WALL,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
	EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
	EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
	EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
	EMPTY,EMPTY,FOOD,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL,
	WALL,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
	EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
	EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
	EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,FOOD,EMPTY,
	EMPTY,EMPTY,FOOD,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL,
	WALL,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
	EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
	EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
	EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,FOOD,EMPTY,
	EMPTY,EMPTY,EMPTY,FOOD,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL,
	WALL,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
	EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL,WALL,WALL,WALL,WALL,
	WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,
	WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
	EMPTY,EMPTY,EMPTY,FOOD,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL,
	WALL,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,FOOD,EMPTY,EMPTY,EMPTY,EMPTY,
	EMPTY,FOOD,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL,WALL,WALL,WALL,WALL,
	WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,
	WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
	EMPTY,EMPTY,EMPTY,FOOD,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL,
	WALL,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
	EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL,WALL,WALL,WALL,WALL,
	WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,
	WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
	EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL,
	WALL,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
	EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL,WALL,WALL,WALL,WALL,
	WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,
	WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
	EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL,
	WALL,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
	EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL,WALL,WALL,WALL,WALL,
	WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,
	WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
	FOOD,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL,
	WALL,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
	EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL,WALL,WALL,WALL,WALL,
	WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,
	WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
	EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,FOOD,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL,
	WALL,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
	EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL,WALL,WALL,WALL,WALL,
	WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,
	WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
	EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL,
	WALL,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
	EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL,WALL,WALL,WALL,WALL,
	WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,
	WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
	EMPTY,EMPTY,EMPTY,FOOD,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL,
	WALL,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
	EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL,WALL,WALL,WALL,WALL,
	WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,
	WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
	EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL,
	WALL,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
	EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL,WALL,WALL,WALL,WALL,
	WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,
	WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
	EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL,
	WALL,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,FOOD,
	EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL,WALL,WALL,WALL,WALL,
	WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,
	WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
	EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL,
	WALL,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
	EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
	EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
	EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
	EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL,
	WALL,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
	EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
	EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
	EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
	EMPTY,EMPTY,EMPTY,FOOD,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL,
	WALL,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
	EMPTY,FOOD,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,FOOD,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
	EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
	EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
	EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL,
	WALL,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
	EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
	EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
	EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
	EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL,
	WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,
	WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,
	WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,
	WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,
	WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL
};

/****************************************************************
 * Here come the function definitions 
 * (to be done by the students)
 ****************************************************************/
void snake_info(const snake_t* snake) {
	segment_t* current = NULL;
	current = malloc(sizeof(segment_t));
	if(snake->tail != NULL) { current = snake->tail; }

		while (current != snake->head) {
		printf("c-x: %d | ", current->x);
		printf("c-y: %d | ", current->y);
		printf("length: %d | ", current->length);
		printf("direction :(%d, %d) | ", current->direction.dx, current->direction.dy);
		printf("previous : ");
		current = current->previous;
	}
	free(current);
	current = NULL;
}

void snake_erase_tail(snake_t* snake) {
	if(snake->tail != NULL) { free(snake->tail); }
	snake->tail = (snake->tail)->previous;	
}

void snake_destroy(snake_t* snake) {
		segment_t* current = NULL;
		current = malloc(sizeof(segment_t));
		
		if(snake->tail != NULL) { current = snake->tail; }

		while(current != snake->head) {
			snake_erase_tail(snake);
			current = current->previous;
		}
	free(current);
	current = NULL;
}

int snake_add_segment(snake_t* snake, direction_t direction) {
	int result = 1;

	segment_t* newSegment = NULL;
	newSegment = malloc(sizeof(segment_t));
	
	newSegment->direction = direction;
	
	if(snake->tail == NULL) {
		newSegment->length = 1;
		snake->tail = newSegment;
		result = 0;
	} else {
		newSegment->length = 0;
		newSegment->x = direction.dx + snake->head->x;
		newSegment->y = direction.dy + snake->head->y;
		result = 0;
	}
	snake->head = newSegment;
	
	free(newSegment);
	newSegment = NULL;

	return result;
}

int snake_move(snake_t* snake, direction_t direction) {
	int result = 1;

	if((direction.dx == snake->head->x) && (direction.dy == snake->head->y)) {
		snake->head->x += direction.dx;
		snake->head->y += direction.dy;
		result = 0;
	}
	 else {
		snake_add_segment(snake, direction);
		result = 0;
	}

	if(snake->head != snake->tail) {
		++(snake->head->length);
		--(snake->tail->length);
		result = 0;
	}

	if(snake->tail->length == 0) {
		snake_erase_tail(snake);
		result = 0;
	}
	return result;
}

map_cell_t* cell(game_t* game, unsigned int x, unsigned int y) {
	return &(game->map[x + (y * (game->width))]);
}

int game_update(game_t* game, direction_t direction) {
	int result = 0;

	unsigned int xq = (game->snake.tail->x) - (direction.dx * (game->snake.tail->length  - 1));
	unsigned int yq = (game->snake.tail->y) - (direction.dy * (game->snake.tail->length  - 1));

	int movement = snake_move(&game->snake, direction);

	map_cell_t currentHeadCase = *(cell(game, game->snake.head->x, game->snake.head->y));

	if(movement == 0) { //Success du mouvement
		if(currentHeadCase == WALL || currentHeadCase == SNAKE) {
			result = 1;
		}
		else if(currentHeadCase == FOOD) {
			++(game->snake.tail->length);
			result = 0;
		}
		else {
			*(cell(game, xq, yq)) = EMPTY;
			result = 0;
		}
	}
	currentHeadCase = SNAKE;
	return result;
}

int game_init_snake(game_t* game, unsigned int orig_x, unsigned int orig_y) {
	segment_t* initialSegment = NULL;
	initialSegment = malloc(sizeof(segment_t));

	initialSegment->length = 1;
	initialSegment->x = orig_x;
	initialSegment->y = orig_y;
	*cell(game, orig_x, orig_y) = SNAKE;

	snake_t* mySnake = NULL;
	mySnake = malloc(sizeof(snake_t));

	mySnake->tail = initialSegment;
	mySnake->head = initialSegment;
	game->snake = *mySnake;

	free(initialSegment);
	free(mySnake);
	return 0;
}


/****************************************************************/
int game_init_map(game_t* game, const map_cell_t* map, unsigned int width, unsigned int height)
{
    unsigned int x, y;
    game->width = width;
    game->height = height;
    game->map = malloc(game->width * game->height * sizeof(map_cell_t));

    if (game->map == NULL) {
        game->width = game->height = 0;
        return -1;
    }

    for (y = 0; y < height; ++y) {
        for (x = 0; x < width; ++x) {
          *cell(game, x, y) = map[y*width + x];
        }
    }

    return 0;
}

/****************************************************************/
game_t* game_init(unsigned int orig_x, unsigned int orig_y)
{
    game_t* game = malloc(sizeof(game_t));
    if (game != NULL) {
      if (game_init_map(game, header_data, MAP_WIDTH, MAP_HEIGHT) != 0) {
        free(game); game = NULL;
      } else if (game_init_snake(game, orig_x, orig_y) != 0) {
        free(game->map);
        free(game); game = NULL;
      }
    }
    return game;
}

/****************************************************************/
void game_destroy(game_t *game)
{
    snake_destroy(&game->snake);
    free(game->map);
    free(game); game = NULL;
}

/***************************************************************
 * The following handles I/O and is not part of the game engine 
 ****************************************************************/

void game_print(game_t* game)
{
    unsigned int x, y;
#ifdef USE_CURSES
    const int color = has_colors();
    clear();
	if (color) {
      start_color();
      init_pair(WALL , COLOR_BLACK, COLOR_YELLOW);
      init_pair(SNAKE, COLOR_BLACK, COLOR_GREEN );
      init_pair(FOOD , COLOR_BLACK, COLOR_RED   );
    }
#endif
    printw("\n");
    for (y = 0; y < game->height; ++y) {
        for (x = 0; x < game->width; ++x) {
            switch(*cell(game, x, y)) {
              
                case EMPTY:
                    printw(" ");
                    break;
                    
                case WALL:
#ifdef USE_CURSES
                    if (color) {
                        attron(COLOR_PAIR(WALL));
                        printw(" ");
                        attroff(COLOR_PAIR(WALL));
                    } else
#endif
                    printw("O");
                    break;
                    
                case FOOD:
#ifdef USE_CURSES
                    if (color) {
                        attron(COLOR_PAIR(FOOD));
                        printw(" ");
                        attroff(COLOR_PAIR(FOOD));
                    } else
#endif
                    printw("F");
                    break;
                    
                case SNAKE:
#ifdef USE_CURSES
                    if (color) {
                        attron(COLOR_PAIR(SNAKE));
                        printw(" ");
                        attroff(COLOR_PAIR(SNAKE));
                    } else
#endif
                    printw("S");
                    break;
                default:
                    printw("?");
                    break;
            }
        }
        printw("\n");
    }
    /* For debugging */
    snake_info(&game->snake);
#ifdef USE_CURSES
    refresh();
#else
    getchar();
#endif
}

/* Transforms a keypress to dx and dy coordinates */
void handle_key_press(int key, direction_t* dir)
{
#ifndef USE_CURSES
#define KEY_DOWN  's'
#define KEY_UP    'w'
#define KEY_LEFT  'a'
#define KEY_RIGHT 'd'    
#endif

    switch (key) {
    case KEY_DOWN:
        dir->dx =  0;    dir->dy =  1;
        break;

    case KEY_UP:
        dir->dx =  0;    dir->dy = -1;
        break;

    case KEY_RIGHT:
        dir->dx =  1;    dir->dy =  0;
        break;

    case KEY_LEFT:
        dir->dx = -1;    dir->dy =  0;
        break;

    default:
        dir->dx =  0;    dir->dy =  0;
        break;
    }
}

void game_loop(game_t* game)
{
    direction_t dir;
#ifdef USE_CURSES
    /* The user must move the snake manually, it does not move by itself */
#define getkey getch()
#else
    /* Change this array to simulates moves. 
     * An x is a step where no keys are pressed */
    char const keys[] = "xsxdxxxxxxxxxxxxxxxxwxxdxxwxxdxsxsxsx";
    const char* key = keys;
#define getkey (*key)
#endif
    do {
        game_print(game);
        handle_key_press(getkey, &dir);
        if (dir.dx == 0 && dir.dy == 0) {
            dir = game->snake.head->direction;
        }
    } while ((game_update(game, dir) == 0)
#ifndef USE_CURSES
             && (*++key)
#endif
            );
    printw("Game over\n");
}

int main(void)
{
    game_t* game;

#ifdef USE_CURSES
    initscr();
    raw();
    noecho();
    keypad(stdscr, TRUE);
#endif

    game = game_init(3,3);
    if (game) {
        game_loop(game);
        game_destroy(game);
    }

#ifdef USE_CURSES
    endwin();
#endif
    return 0;
}