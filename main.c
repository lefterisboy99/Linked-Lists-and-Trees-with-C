#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Gaugamela.h"

#define BUFFER_SIZE 1024  /* Maximum length of a line in input file */

/* Uncomment the following line to enable debugging prints 
 * or comment to disable it */
#define DEBUG

#ifdef DEBUG
#define DPRINT(...) fprintf(stderr, __VA_ARGS__);
#else  /* DEBUG */
#define DPRINT(...)
#endif /* DEBUG */

int komboi=0;
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
 * @param type    The soldier's type
 * @param general The general the soldier obeys
 *
 * @return 1 on success
 *         0 on failure
 */
int register_GA_soldier (int sid, int general, int type)
{
	GA_army[0]=makelist(GA_army[0],sid,type,general);
	return 1;
}

/**
 * @brief Register Alexander the Great horse 
 *
 * @param sid     The horse's id
 * @param type    Always the value of 0
 * @param general The general the soldier obeys
 *
 * @return 1 on success
 *         0 on failure
 */
int register_GA_horse (int hid, int type, int general)
{
	GA_army[1]=makelist(GA_army[1],hid,type,general);
	return 1;
}


/**
 * @brief Register Satrapy
 *
 * @param sid The Satrapy's id
 *
 * @return 1 on success
 *         0 on failure
 */
int register_satrapy (int sid)
{
	satrapies_list=makemySatrapy(satrapies_list,sid);
	return 1;
}

/**
 * @brief Register Satrapy soldier
 *
 * @param sid     The id of the Satrapy the soldier belongs to
 * @param aid     The soldier's id
 * @param type    The type of soldier
 * @param general The general the soldier obeys
 *
 * @return 1 on success
 *         0 on failure
 */
int register_S_soldier (int aid, int sid, int type, int general)
{
	satrapies_list=makesatrapiesArmy(satrapies_list,aid,sid,general,type);
	
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
	MakemyEmpire(&GA_battle_list,GA_army[0],GA_army[1]);
	return 1;
}

/**
 * @brief Prepare Satrapies for battle
 *
 * @param sid The satrapy's id
 *
 * @return 1 on success
 *         0 on failure
 */
int prepare_for_battle_S (int sid)
{
	S_battle_list=SATRAPIEESARMIEESS(S_battle_list,sid,satrapies_list,komboi);
	return 1;
}

/**
 * @brief The death of a soldier
 * 
 * @param sid  The soldier's id
 * @param flag If 0, the soldier belongs to a Satrapy
 *             If 1, the soldier belongs to Alexander the Great
 *
 * @return 1 on success
 *         0 on failure
 */
int soldiers_death (int sid, int flag)
{
	int i;
	if(flag==1){
		struct Army* ap=GA_army[0];
		while(ap!=NULL && ap->id!=sid){
				ap=ap->next;
			}
			if(ap==NULL) return 0;
		 GA_army[0] = Delete_this(GA_army[0],ap);
		 struct GA_Battle* Battler=GA_battle_list;
		 while(Battler->soldier_id!=sid){
				  Battler=Battler->next;
				}
 		 GA_battle_list=Delete_thisArmy(GA_battle_list,Battler);
	}
	if(flag==0){
		struct S_Battle* ap=S_battle_list;
    while(ap!=NULL && ap->soldier_id!=sid){
			ap=ap->next;
		}
		if(ap==NULL) return 0;
		if(satrapies_list->next==NULL) return 0;
	i=ap->satrapy_id;
	struct Satrapy *pff=satrapies_list->next;
	while(pff!=satrapies_list && pff->id!=i) pff=pff->next;	
	struct Army *deleted=pff->s_army;
	while(deleted!=NULL && deleted->id!=sid)deleted=deleted->next;
	pff->s_army=Delete_my_soldiers_from_satrapy(pff->s_army,deleted);
    S_battle_list= Delete_this_S(S_battle_list,ap);
	}
	return 1;
}

/**
 * @brief Victory of Alexander the Great's horsemen
 *
 * @return 1 on success
 *         0 on failure
 */
int GA_horsemen_victory (void)
{
	Delete_my_hsoldiers(&S_battle_list);
	GA_army[0]=Delete_my_hsoldiersGA(GA_army[0]);
	MakemyEmpire(&GA_battle_list,GA_army[0],GA_army[1]);
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
	int i;
	for(i=0;i<5;i++){
      GA_Generals[i]=AlexanderDeath(GA_Generals[i],GA_battle_list,i+1);
}
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
	struct Army *S=GA_army[0];
	struct Army *P=GA_army[1];
	printf("GA_SOLDIERS=");
	while(S!=NULL){
		printf("<%d,%d,%d> ",S->id,S->type,S->general);
		S=S->next;
	}
	printf("GA_HORSES=");
	while(P!=NULL){
		printf("<%d,%d,%d> ",P->id,P->type,P->general);
		P=P->next;
	}

	return 1;
}
void print_GA_soldiers_only (void)
{
	struct Army *S=GA_army[0];
	printf("GA_SOLDIERS=");
	while(S!=NULL){
		printf("<%d,%d,%d> ",S->id,S->type,S->general);
		S=S->next;
	}
	}
void print_GA_soldiers_battle (void)
{
	struct GA_Battle *S=GA_battle_list;
	printf("GA_BATTLE=");
	while(S!=NULL){
		printf("<%d,%d,%d> ",S->soldier_id,S->horse_id,S->general);
		S=S->next;
	}
	}

	void print_S_soldiers_battle (void)
{
	struct S_Battle *S = S_battle_list;
	printf("S_BATTLE=");
	while(S!=NULL){
		printf("<%d,%d,%d> ",S->satrapy_id,S->soldier_id,S->type);
		S=S->next;
	}

	}


	void print_GA_horses (void)
{
	
	struct Army *P=GA_army[1];
	
	printf("GA_HORSES=");
	while(P!=NULL){
		printf("<%d,%d,%d> ",P->id,P->type,P->general);
		P=P->next;
	}


}
/**
 * @brief Print all Satrapy soldiers
 *
 * @return 1 on success
 *         0 on failure
 */
int print_S_soldiers (void)
{
	struct Army *s;
	int i;
	struct Satrapy *Bronzetron=satrapies_list->next;
while(Bronzetron!=satrapies_list){
    s=Bronzetron->s_army;
    i=Bronzetron->id;
    printf("satrapy %d",i);
    while(s!=Bronzetron->sentinel){
    printf("<%d,%d,%d> ",s->id,s->type,s->general);
    s=s->next;
    }
    printf("\n");
    Bronzetron=Bronzetron->next;
}
	return 1;
}

void print_S_soldiersonly (void)
{
	struct Army *s;
	int i;
	struct Satrapy *Bronzetron=satrapies_list->next;
while(Bronzetron!=satrapies_list){
    s=Bronzetron->s_army;
    i=Bronzetron->id;
    printf("satrapy %d",i);
    while(s!=Bronzetron->sentinel){
    printf("<%d,%d,%d> ",s->id,s->type,s->general);
    s=s->next;
    }
    printf("\n");
    Bronzetron=Bronzetron->next;
}
	
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
	satrapies_list=(struct Satrapy*)malloc(sizeof(struct Satrapy));
	satrapies_list->next=NULL;
	satrapies_list->prev=NULL;	
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

	/* Read input file buff-by-buff and handle the events */
	while (fgets(buff, BUFFER_SIZE, fin)) {

		DPRINT("\n>>> Event: %s", buff);

		switch(buff[0]) {

			/* Comment */
			case '#':
				break;

				/* Register GA soldier
				 * R <sid> <type> <general> */
			case 'R':
				{
					int sid, type, general;

					sscanf(buff, "%c %d %d %d", &event, &sid, &type, &general);
					DPRINT("%c %d %d %d\n", event, sid, type, general);

					if (register_GA_soldier(sid, type, general)) {
						DPRINT("R %d %d %d succeeded\n", sid, type, general);
						print_GA_soldiers_only();
						printf("DONE\n");
					} else {
						fprintf(stderr, "R %d %d %d failed\n", sid, type, general);
					}

					break;
				}

				/* Register GA horse
				 * H <hid> <type> <general> */
			case 'H':
				{
					int hid, type, general;

					sscanf(buff, "%c %d %d %d", &event, &hid, &type, &general);
					DPRINT("%c %d %d %d\n", event, hid, type, general);

					if (register_GA_horse(hid, type, general)) {
						DPRINT("H %d %d %d succeeded\n", hid, type, general);
						print_GA_horses();
						printf("DONE\n");
					} else {
						fprintf(stderr, "H %d %d %d failed\n", hid, type, general);
					}

					break;
				}

				/* Register Satrapy
				 * S <sid> */
			case 'S':
				{
					int sid;
					komboi++;
					sscanf(buff, "%c %d", &event, &sid);
					DPRINT("%c %d\n", event, sid);

					if (register_satrapy(sid)) {
						DPRINT("S %d succeeded\n", sid);
						struct Satrapy *Bronzetron=satrapies_list->next;
						printf("Satrapies=");
							while(Bronzetron!=satrapies_list){
							
								printf("<%d> ",Bronzetron->id);
								
								Bronzetron=Bronzetron->next;
							}
							printf("\n");
							printf("DONE\n");
					} else {
						fprintf(stderr, "S %d failed\n", sid);
					}

					break;
				}

				/* Register Satrapy soldier
				 * A <sid> <aid> <type> <general> */
			case 'A':
				{
					int sid, aid, type, general;

					sscanf(buff, "%c %d %d %d %d", &event, &sid, &aid, &type, &general);
					DPRINT("%c %d %d %d %d\n", event, sid, aid, type, general);

					if (register_S_soldier(sid, aid, type, general)) {
						DPRINT("A %c %d %d %d %d succeeded\n", event, sid, aid, type, general);
						print_S_soldiersonly();
						printf("DONE\n");
					} else {
						fprintf(stderr, "A %c %d %d %d %d failed\n", event, sid, aid, type, general);
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
						print_GA_soldiers();
						printf("DONE\n");
					} else {
						fprintf(stderr, "P %c failed\n", event);
					}

					break;
				}

				/* Prepare Satrapies for battle
				 * B <sid> */
			case 'B':
				{
					int sid;

					sscanf(buff, "%c %d", &event, &sid);
					DPRINT("%c %d\n", event, sid);

					if (prepare_for_battle_S(sid)) {
						DPRINT("B %c %d succeeded\n", event, sid);
						print_S_soldiers_battle();
						printf("DONE\n");
					} else {
						fprintf(stderr, "B %c %d failed\n", event, sid);
					}

					break;
				}

				/* The death of a soldier
				 * K <sid> <flag> */
			case 'K':
				{
					int sid, flag;

					sscanf(buff, "%c %d %d", &event, &sid, &flag);
					DPRINT("%c %d %d\n", event, sid, flag);

					if (soldiers_death(sid, flag)) {
						DPRINT("K %c %d %d succeeded\n", event, sid, flag);
						print_GA_soldiers_battle();
						print_S_soldiers_battle();
						printf("DONE\n");
					} else {
						fprintf(stderr, "K %c %d %d failed\n", event, sid, flag);
					}

					break;
				}

				/* Victory of Alexander the Great's horsemen
				 * V */
			case 'V':
				{
					sscanf(buff, "%c", &event);
					DPRINT("%c\n", event);

					if (GA_horsemen_victory()) {
						DPRINT("%c succeeded\n", event);
						print_GA_soldiers_battle();
						print_S_soldiers_battle();
						printf("DONE\n");
					} else {
						fprintf(stderr, "%c failed\n", event);
					}

					break;
				}

				/* The death of Alexander the Great
				 * D */
			case 'D':
				{
					int i;
					sscanf(buff, "%c", &event);
					DPRINT("%c\n", event);

					if (Alexanders_death()) {
						DPRINT("%c succeeded\n", event);
						struct GA_Battle* SG;
						for(i=0;i<5;i++){
							SG=GA_Generals[i];
							printf("GENERAL%d\n",i+1);
							while(SG!=NULL){
							printf("%d %d",SG->soldier_id,SG->general);
							SG=SG->next;
							printf("\n");
							}


						}
						printf("DONE\n");
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
						printf("DONE\n");
					} else {
						fprintf(stderr, "%c failed\n", event);
					}

					break;
				}

				/* Print all Satrapy soldiers
				 * Y */
			case 'Y':
				{
					sscanf(buff, "%c", &event);
					DPRINT("%c\n", event);

					if (print_S_soldiers()) {
						DPRINT("%c succeeded\n", event);
						printf("DONE\n");
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

