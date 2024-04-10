/*************************************************************
 * @file   Gaugamela.h                                       *
 * @author Nikolaos Batsaras <batsaras@csd.uoc.gr>  	     *
 *                                                    	     *
 * @brief  Header file for the needs of cs-240a project 2018 *
 ************************************************************/

#ifndef __GAUGAMELA_H__
#define __GAUGAMELA_H__


struct Army {
	int id;
	int type;
	int general;
	struct Army *next;
};

struct GA_Battle {
	int soldier_id;
	int horse_id;
	int general;
	struct GA_Battle *next;
};

struct Satrapy {
	int id;
	struct Army *s_army;
	struct Satrapy *next;
	struct Satrapy *prev;
	struct Army *sentinel;
};

struct S_Battle {
	int soldier_id;
	int satrapy_id;
	int type;
	struct S_Battle *next;
};

/*
 * Global variable
 *
 * A 2-Cell array containing the following pointers:
 *
 * 	* 1rst cell is a pointer to the head of Alexander's list of soldiers
 * 	* 2nd  cell is a pointer to the head of Alexander's list of horses
 */
struct Army *GA_army[2];

/* global variable, pointer to the head of Alexander's battle list */
struct GA_Battle *GA_battle_list;

/* global variable, pointer to the head of the list of Satrapies */
struct Satrapy *satrapies_list;

/* global variable, pointer to the head of the Satrapies' battle list */
struct S_Battle *S_battle_list;

/* global variable, array of pointers to struct GA_Battle sublists */
struct GA_Battle *GA_Generals[5];


struct GA_Battle*AlexanderDeath(struct GA_Battle *General,struct GA_Battle *battlelist,int i){
    struct GA_Battle *S=General,*P=battlelist,*tmp;
    while(P!=NULL){
    if(General==NULL){
      if(P->general==i){
        General=(struct GA_Battle*)malloc(sizeof(struct GA_Battle));
        General->general=P->general;
        General->horse_id=P->horse_id;
        General->soldier_id=P->soldier_id;
        General->next=NULL;
          S=General;
      }
    }else{
        while(S->next!=NULL) S=S->next;
        if(P->general==i){
       S->next=(struct GA_Battle*)malloc(sizeof(struct GA_Battle));
       S=S->next;
       S->next=NULL;
        S->general=P->general;
        S->horse_id=P->horse_id;
        S->soldier_id=P->soldier_id;
        S->next=NULL;
        }
    }

  P=P->next;
    }
  return General;
}


struct Satrapy *makemySatrapy(struct Satrapy* Nicktron,int id){
   
    struct Satrapy *tmp;
    struct Satrapy *P=Nicktron->next;
      
    tmp=(struct Satrapy*)malloc(sizeof(struct Satrapy));
    
    tmp->s_army=NULL;
    tmp->sentinel=NULL;
    tmp->id=id;
    if(Nicktron->next==NULL){
        Nicktron->next=tmp;
        Nicktron->prev=tmp;
        tmp->next=Nicktron;
        tmp->prev=Nicktron;
    }else{
        while(P->next!=Nicktron){
            P=P->next;
        }
            
    tmp->next = P->next; 
  
    P->next = tmp; 
    tmp->prev = P; 
    if (tmp->next != NULL) 
        tmp->next->prev = tmp; 
 

    }
    
    return Nicktron;
}



 struct S_Battle *MakeArmy( struct S_Battle *P,struct Army* List,int idd){
      struct S_Battle *ready;
      if(List!=NULL){
    if(P==NULL){
        P= (struct S_Battle*)malloc(sizeof( struct S_Battle));
        P->next=NULL;
        P->satrapy_id=idd;
        P->soldier_id=List->id;
        P->type=List->type;
    }
    ready=P;
while(List->id!=-1){
    while(ready->next!=NULL) ready=ready->next;
        ready->next= (struct S_Battle*)malloc(sizeof( struct S_Battle));
        ready=ready->next;
        ready->next=NULL;
        ready->satrapy_id=idd;
        ready->soldier_id=List->id;
        ready->type=List->type;
        List=List->next;
 
}
      }
    ready=P;
   
    return P;
 }



struct Satrapy *makesatrapiesArmy(struct Satrapy* Nicktron,int id,int soldier_id,int general,int type){
    struct Satrapy* Bronztron=Nicktron->next;
   
    while(Bronztron->id!=id){
        Bronztron=Bronztron->next;
       
    }
   
    struct Army *Darius;
     struct Army *Darios=Bronztron->s_army;
        if(Darios==NULL){
           
            Bronztron->s_army= (struct Army*)malloc(sizeof(struct Army));
            Bronztron->s_army->general=general;
          
            Bronztron->s_army->id=soldier_id;
            Bronztron->s_army->type=type;
            Bronztron->sentinel =(struct Army*)malloc(sizeof(struct Army));
            Bronztron->sentinel->id=-1;
            Bronztron->sentinel->general=-1;
            Bronztron->sentinel->type=-1;
            Bronztron->s_army->next=Bronztron->sentinel;
           Darios=Bronztron->s_army; 
         
        }else{
            while(Darios->next!=Bronztron->sentinel){
                        Darios=Darios->next;
            }
            Darius=(struct Army*)malloc(sizeof(struct Army));
            Darius->next=Bronztron->sentinel;
            Darius->general=general;
            Darius->id=soldier_id;
            Darius->type=type;
            Darios->next=Darius;
        }


    


    return Nicktron;
}


struct S_Battle *SATRAPIEESARMIEESS(struct S_Battle *Nickbronze,int central,struct Satrapy *Nicktron,int komboi){
    struct S_Battle *P=Nickbronze;
    struct Satrapy *tmp1,*tmp2;
    struct Army *Army;
    int ar=0;
    struct Satrapy *L=Nicktron->next;
while(L->id!=central){
        L=L->next;
}
Army=L->s_army;
if(komboi==1){
    while(Army!=L->sentinel){
        if(Nickbronze==NULL){
            Nickbronze=(struct S_Battle*)malloc(sizeof(struct S_Battle));
            Nickbronze->next=NULL;
            P=Nickbronze;
            P->satrapy_id=L->id;
            P->soldier_id=Army->id;
            P->type=Army->type;
            Army=Army->next;
        }else{
            P->next=(struct S_Battle*)malloc(sizeof(struct S_Battle));
            P=P->next;
            P->next=NULL;
            P->satrapy_id=L->id;
            P->soldier_id=Army->id;
            P->type=Army->type;
             Army=Army->next;
        }

    }
}else{
     while(Army!=L->sentinel){
        if(Nickbronze==NULL){
            Nickbronze=(struct S_Battle*)malloc(sizeof(struct S_Battle));
            Nickbronze->next=NULL;
            P=Nickbronze;
            P->satrapy_id=L->id;
            P->soldier_id=Army->id;
            P->type=Army->type;
            Army=Army->next;
        }else{
            P->next=(struct S_Battle*)malloc(sizeof(struct S_Battle));
            P=P->next;
            P->next=NULL;
            P->satrapy_id=L->id;
            P->soldier_id=Army->id;
            P->type=Army->type;
             Army=Army->next;
        }
     }
    tmp1=L->prev;
    tmp2=L->next;
    P=Nickbronze;
    while(1){
        ar++;
        if(tmp1==Nicktron)tmp1=tmp1->prev;
        if(tmp2==Nicktron)tmp2=tmp2->next;
        if(tmp1->s_army!=tmp1->sentinel)
        Nickbronze=MakeArmy(Nickbronze,tmp1->s_army,tmp1->id);
        if(!(komboi%2)){
            if(tmp1!=tmp2){
                Nickbronze=MakeArmy(Nickbronze,tmp2->s_army,tmp2->id);
            }else break;
        }else{
            if(ar!=(komboi/2)){
                Nickbronze=MakeArmy(Nickbronze,tmp2->s_army,tmp2->id);
            }else {
                tmp1=tmp1->prev;
                if(tmp1==Nicktron)tmp1=tmp1->prev;
                 Nickbronze=MakeArmy(Nickbronze,tmp1->s_army,tmp1->id);
                 break;
            }


        }
    tmp1=tmp1->prev;
    tmp2=tmp2->next;



    }

if(Nickbronze!=NULL){
    if(Nickbronze->next!=NULL){
    if(Nickbronze->soldier_id==Nickbronze->next->soldier_id)
        Nickbronze=Nickbronze->next;
}
}

}


    return Nickbronze;
}

struct Army* Delete_my_soldiers_from_satrapy(struct Army *L,struct Army *P){
    struct Army *S=L;
    
            if(S == NULL) {
            return NULL;
                }
                if(P==NULL){
                        return NULL;
                        }
            if( S == P) {
                       S = S->next;
                      
                       return S;
                    }
              S ->next = Delete_my_soldiers_from_satrapy(S->next, P);
}

struct S_Battle* Delete_this_S(struct S_Battle *L,struct S_Battle *P){
    struct S_Battle *S=L;
    
            if(S == NULL) {
            return NULL;
                }
                if(P==NULL){
                        return NULL;
                        }
            if( S == P) {
                       S = S->next;
                       free(P);
                       return S;
                    }
              S ->next = Delete_this_S(S->next, P);
}

void Delete_my_hsoldiers(struct S_Battle** L){
    // Store head node 
    struct S_Battle* temp = *L,*prev;
    // If head node itself holds the key or multiple occurrences of key 
    while (temp != NULL && temp->type == 1) 
    { 
        *L = temp->next;   // Changed head 
        free(temp);               // free old head 
        temp = *L;        // Change Temp 
    } 
  
    // Delete occurrences other than head 
    while (temp != NULL) 
    { 
        // Search for the key to be deleted, keep track of the 
        // previous node as we need to change 'prev->next' 
        while (temp != NULL && temp->type!= 1) 
        { 
            prev = temp; 
            temp = temp->next; 
        } 
  
        // If key was not present in linked list 
        if (temp == NULL) return; 
  
        // Unlink the node from linked list 
        prev->next = temp->next; 
  
        free(temp);  // Free memory 
  
        //Update Temp for next iteration of outer loop 
        temp = prev->next; 
    }
 
}

struct Army *makelist(struct Army *L,int id,int general,int type){
    struct Army *P=L;
    int flag=1;
    struct Army *tmp,*tmp1,*current;
    if(L==NULL){
          L = (struct Army*)malloc(sizeof(struct Army));
          L->next=NULL;   
          L->type=type;
          L->general=general;
          L->id=id;
          
    }else{
        tmp = (struct Army*)malloc(sizeof(struct Army));
        tmp->id=id;
        tmp->general=general;
        tmp->type=type;
        P=L;
        if (L == NULL || L->id > id) 
    { 
        tmp->next = L; 
        L = tmp; 
    } 
    else
    { 
        
        current = L; 
        while (current->next!=NULL && 
               current->next->id < tmp->id) 
        { 
            current = current->next; 
        } 
        tmp->next = current->next; 
        current->next = tmp; 
    } 
        }
        return L;
        }


        void *MakemyEmpire(struct GA_Battle **NASASKA,struct Army*L,struct Army*P){
          int i;
	  struct Army *mysoldiers=L,*horses=P;
          struct GA_Battle *Empire=*NASASKA;
          for(i=1;i<=5;i++){
            mysoldiers=L;
          while(mysoldiers!=NULL){
            if(mysoldiers->type==i){
              if(Empire==NULL){
                   Empire=(struct GA_Battle*)malloc(sizeof(struct GA_Battle));
                   Empire->general=mysoldiers->general;
                   Empire->next=NULL;
                   Empire->soldier_id=mysoldiers->id;
                   if(horses!=NULL && (mysoldiers->type==1)){
                   Empire->horse_id=horses->id;
                   horses= horses->next;
                   }
                   else Empire->horse_id=-1;
                  *NASASKA=Empire;
                  mysoldiers=mysoldiers->next;
                 
                  
              }else{
                Empire->next=(struct GA_Battle*)malloc(sizeof(struct GA_Battle));
                  Empire=Empire->next;
                   Empire->next=NULL;
                   Empire->general=mysoldiers->general;
                   Empire->soldier_id=mysoldiers->id;
                    if(horses!=NULL&&(mysoldiers->type==1)){
                   Empire->horse_id=horses->id;
                   horses= horses->next;
                   }
                   else Empire->horse_id=-1;
                   mysoldiers=mysoldiers->next;
                  
                
                }
            }else{
              mysoldiers=mysoldiers->next;
            }
          }
         
              
            
          } 
              

        }


 struct Army* Delete_this(struct Army *L,struct Army *P){
    struct Army *S=L;
    
            if(S == NULL) {
            return NULL;
                }
                if(P==NULL){
                        return NULL;
                        }
            if( S == P) {
                       S = S->next;
                       free(P);
                       return S;
                    }
              S ->next = Delete_this(S->next, P);
 
}

struct GA_Battle* Delete_thisArmy(struct GA_Battle *L,struct GA_Battle *P){
    struct GA_Battle *S=L;
    
            if(S == NULL) {
            return NULL;
                }
                if(P==NULL){
                        return NULL;
                        }
            if( S == P) {
                       S = S->next;
                       free(P);
                       return S;
                    }
              S ->next = Delete_thisArmy(S->next, P);
 
}

struct Army *Delete_my_hsoldiersGA(struct Army* L){
    struct Army *S=L,*P=L;
    int i=0,j=0;
    while(S!=NULL){
      if(i!=0){
        i=0;
        j=0;
        while(j<2){
          if(S->type==1) {
            S=S->next;
            j++;
          }else S=S->next;
          
          if(S==NULL) return L;
        }

      }else {
        while(S->type!=1){
          S=S->next;
          if(S==NULL) return L;
          
        }
        i=1;
        L=Delete_this(L,S);
      }
      
      
    }


  return L;
}

#endif /* __GAUGAMELA_H__ */

