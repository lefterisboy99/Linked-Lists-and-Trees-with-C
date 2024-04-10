#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "Persida.h"

#define BUFFER_SIZE 1024  /* Maximum length of a line in input file */

/* Uncomment the following line to enable debugging prints 
 * or comment to disable it */
#define DEBUG

#ifdef DEBUG
#define DPRINT(...) fprintf(stderr, __VA_ARGS__);
#else  /* DEBUG */
#define DPRINT(...)
#endif /* DEBUG */


/**
 * @brief Optional function to initialize data structures that 
 *        need initialization
 *
 * @return 1 on success
 *         0 on failure
 */



int initialize (void)
{
	return 1;
}

/**
 * @brief Register Alexander the Great soldier 
 *
 * @param sid     The soldier's id
 *
 * @return 1 on success
 *         0 on failure
 */
int register_GA_soldier (int sid)
{
	HayateKirino= insert(HayateKirino,sid);
	return 1;
}

void alex_death(struct Army *p){
    if(p==NULL)return;
    if(p->id<500){
        ptolemeos=insert(ptolemeos,p->id);
    }else if(p->id<1000){
        mitsos=insert(mitsos,p->id);
    }else if(p->id<1500){
        kassandros=insert(kassandros,p->id);
    }else if(p->id<2000){
        lysas=insert(lysas,p->id);
    }else if(p->id>=2000){
        seleykos=insert(seleykos,p->id);
    }
    alex_death(p->lc);
    alex_death(p->rc);
}

/**
 * @brief Register Alexander the Great horse 
 *
 * @param sid     The horse's id
 * @param age     The horse's age
 *
 * @return 1 on success
 *         0 on failure
 */
int register_GA_horse (int hid, int age)
{
	struct Horse h;
	h.age=age;
	h.id=hid;
	A=HeapInsert(A,h);
	return 1;
}

/**
 * @brief Register enemy soldier
 *
 * @param aid     The soldier's id
 *
 * @return 1 on success
 *         0 on failure
 */
int register_AR_soldier (int aid)
{
	int thesi=hash(aid);
	insert_S(thesi,aid);
	return 1;
}

/**
 * @brief Prepare Alexander's soldiers for battle
 * 
 * @return 1 on success
 *         0 on failure
 */
int prepare_for_battle_GA (void)
{
	PreOrder(HayateKirino);
	return 1;
}

/**
 * @brief The ambush against Alexander the Great
 * @param X  Kill 1-every-X soldiers
 * @return 1 on success
 *         0 on failure
 */
int ambush_GA (int X)
{
	ARXIGOS.Ga_tree=Delete_the_fucking_hitler(ARXIGOS.Ga_tree,X);
	return 1;
}

/**
 * @brief Victory of Alexander the Great's army
 *
 * @return 1 on success
 *         0 on failure
 */
int GA_victory (void)
{
	Start_Delete(ARXIGOS.Ga_tree);
	return 1;
}

/**
 * @brief The death of Alexander the Great
 *
 * @return 1 on success
 *         0 on failure
 */
int Alexanders_death (void)
{
	alex_death(HayateKirino);
	return 1;
}

/**
 * @brief Print all soldiers of Alexander the Great
 *
 * @return 1 on success
 *         0 on failure
 */
int print_GA_soldiers (void)
{
	printf("GA_SOLDIERS=");
	PeOrder(HayateKirino);
	return 1;
}

/**
 * @brief Print all of Alexander the Great horses
 *
 * @return 1 on success
 *         0 on failure
 */
int print_GA_horses (void)
{
	printf("GA_HORSES=");
	PrintHorses(A);
	return 1;
}

/**
 * @brief Print Alexander the Great army
 *
 * @return 1 on success
 *         0 on failure
 */
int print_GA_army (void)
{
	printf("GA_ARMY=");
	PeOrder1(ARXIGOS.Ga_tree);
	return 1;
}

/**
 * @brief Print enemy's army
 *
 * @return 1 on success
 *         0 on failure
 */
int print_AR_army (void)
{
	int i;
	for(i=0;i<max_soldiers_g/2;i++){
		printf("Index %d:",i);
		print_this_S(hash_table[i]);
		printf("\n");
	}
	return 1;
}




/**
 * @brief Free resources
 *
 * @return 1 on success
 *         0 on failure
 */
int free_all(void)
{
	return 1;
}


/**
 * @brief The main function
 *
 * @param argc Number of arguments
 * @param argv Argument vector
 *
 * @return 0 on success
 *         1 on failure
 */
int main(int argc, char** argv)
{
	 srand((unsigned int)time(NULL));
	int i;
	FILE *fin = NULL;
	char buff[BUFFER_SIZE], event;

	/* Check command buff arguments */
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <input_file> \n", argv[0]);
		return EXIT_FAILURE;
	}

	/* Open input file */
	if (( fin = fopen(argv[1], "r") ) == NULL ) {
		fprintf(stderr, "\n Could not open file: %s\n", argv[1]);
		perror("Opening test file\n");
		return EXIT_FAILURE;
	}

	/* Initializations */
	initialize();

	// Read max horses
	fgets(buff, BUFFER_SIZE, fin);
	sscanf(buff, "%d", &max_horses);
	DPRINT("Max horses: %d\n", max_horses)
	A.size=0;
     A.horsePQ=  malloc(max_horses * sizeof(struct Horse));

	// Read max enemy soldiers' number
	fgets(buff, BUFFER_SIZE, fin);
	sscanf(buff, "%d", &max_soldiers_g);
	DPRINT("Max enemy soldiers: %d\n", max_soldiers_g)

	// Read max enemy soldiers' ID
	fgets(buff, BUFFER_SIZE, fin);
	sscanf(buff, "%d", &max_soldiers_id_g);
	DPRINT("Max enemy soldiers' ID: %d\n", max_soldiers_id_g)
	hash_table = (struct AR_Battle **) malloc(max_soldiers_g/2 * sizeof(struct AR_Battle **));
	 for(i=0;i<max_soldiers_g/2;i++) hash_table[i]=NULL;
	 i=0;
	  while(primes_g[i]<=max_soldiers_id_g) i++;
            max_number = primes_g[i];
	/* Read input file buff-by-buff and handle the events */
	while (fgets(buff, BUFFER_SIZE, fin)) {

		DPRINT("\n>>> Event: %s", buff);

		switch(buff[0]) {

			/* Comment */
			case '#':
				break;

				/* Register GA soldier
				 * R <sid> */
			case 'R':
				{
					int sid;

					sscanf(buff, "%c %d", &event, &sid);
					DPRINT("%c %d\n", event, sid);

					if (register_GA_soldier(sid)) {
						DPRINT("R %d succeeded\n", sid);
						print_GA_soldiers();
					} else {
						fprintf(stderr, "R %d failed\n", sid);
					}

					break;
				}

				/* Register GA horse
				 * H <hid> <age> */
			case 'H':
				{
					int hid, age;

					sscanf(buff, "%c %d %d", &event, &hid, &age);
					DPRINT("%c %d %d\n", event, hid, age);

					if (register_GA_horse(hid, age)) {
						DPRINT("H %d %d succeeded\n", hid, age);
						print_GA_horses();
					} else {
						fprintf(stderr, "H %d %d failed\n", hid, age);
					}

					break;
				}
				/* Register enemy soldier
				 * A <aid> */
			case 'A':
				{
					int aid;

					sscanf(buff, "%c %d", &event, &aid);
					DPRINT("%c %d\n", event, aid);

					if (register_AR_soldier(aid)) {
						DPRINT("A %d succeeded\n", aid);
						print_AR_army();
					} else {
						fprintf(stderr, "A %d failed\n", aid);
					}

					break;
				}

				/* Prepare Alexander's soldiers for battle
				 * P */
			case 'P':
				{
					sscanf(buff, "%c", &event);
					DPRINT("%c\n", event);

					if (prepare_for_battle_GA()) {
						DPRINT("P %c succeeded\n", event);
						print_GA_army();
					} else {
						fprintf(stderr, "P %c failed\n", event);
					}

					break;
				}
				/* Ambush against Alexander the Great
				 * T <X> */
			case 'T':
				{
					int X;

					sscanf(buff, "%c %d", &event, &X);
					DPRINT("%c %d\n", event, X);

					if (ambush_GA(X)) {
						DPRINT("T %d succeeded\n", X);
						print_GA_army();
					} else {
						fprintf(stderr, "T %d failed\n", X);
					}

					break;
				}

				/* Victory of Alexander the Great's army
				 * K */
			case 'K':
				{
					sscanf(buff, "%c", &event);
					DPRINT("%c\n", event);

					if (GA_victory()) {
						DPRINT("%c succeeded\n", event);
						print_AR_army();
					} else {
						fprintf(stderr, "%c failed\n", event);
					}

					break;
				}

				/* The death of Alexander the Great
				 * D */
			case 'D':
				{
					sscanf(buff, "%c", &event);
					DPRINT("%c\n", event);

					if (Alexanders_death()) {
						DPRINT("%c succeeded\n", event);
						printf("General 0=");
						PeOrder(ptolemeos);
						printf("\n");
						printf("General 1=");
						PeOrder(mitsos);
						printf("\n");
						printf("General 2=");
						PeOrder(kassandros);
						printf("\n");
						printf("General 3=");
						PeOrder(lysas);
						printf("\n");
						printf("General 4=");
						PeOrder(seleykos);
						printf("\n");
					} else {
						fprintf(stderr, "%c failed\n", event);
					}

					break;
				}

				/* Print all soldiers of Alexander the Great
				 * X */
			case 'X':
				{
					sscanf(buff, "%c", &event);
					DPRINT("%c\n", event);

					if (print_GA_soldiers()) {
						DPRINT("%c succeeded\n", event);
					} else {
						fprintf(stderr, "%c failed\n", event);
					}

					break;
				}
				/* Print all Alexander the Great horses
				 * Y */
			case 'Y':
				{
					sscanf(buff, "%c", &event);
					DPRINT("%c\n", event);

					if (print_GA_horses()) {
						DPRINT("%c succeeded\n", event);
					} else {
						fprintf(stderr, "%c failed\n", event);
					}

					break;
				}
			/* Print of Alexander the Great army
				 * X */
			case 'Z':
				{
					sscanf(buff, "%c", &event);
					DPRINT("%c\n", event);

					if (print_GA_army()) {
						DPRINT("%c succeeded\n", event);
					} else {
						fprintf(stderr, "%c failed\n", event);
					}

					break;
				}
				/* Print all enemy soldiers
				 * Y */
			case 'W':
				{
					sscanf(buff, "%c", &event);
					DPRINT("%c\n", event);

					if (print_AR_army()) {
						DPRINT("%c succeeded\n", event);
					} else {
						fprintf(stderr, "%c failed\n", event);
					}

					break;
				}

				/* Empty line */
			case '\n':
				break;

				/* Ignore everything else */
			default:
				DPRINT("Ignoring buff: %s \n", buff);

				break;
		}
	}

	free_all();
	return (EXIT_SUCCESS);
}
