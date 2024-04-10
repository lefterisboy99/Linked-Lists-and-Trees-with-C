#include <math.h>
#include<stdbool.h>
#include<time.h>
struct Army{
	unsigned int id;
	struct Army *lc;
	struct Army *rc;
};

struct Horse{
	unsigned int id;
	unsigned int age;
};

struct HorsePQ{
	int size; /* Current size of the priority queue. Update accordingly when inserting/deleting nodes */
	struct Horse *horsePQ; /* Dynamically allocated array (once at startup) to implement the priority queue as a heap. */
};

struct GA_Battle{
	unsigned int soldier_id;
	unsigned int horse_id;
	struct GA_Battle *lc;
	struct GA_Battle *rc;
};

struct GA_Tree{
	int size; /* Current size of the complete tree. Update accordingly when inserting/deleting nodes */
	struct GA_Battle *Ga_tree; /* Pointer to the root of the GA battle complete tree */
};

struct AR_Battle{
	unsigned int id;
	struct AR_Battle *next;
};

unsigned int max_horses; /* Max # of GA horses */

/*Global variable for enemy army's hash table. Remember to choose the array's size carefully and use universal hashing */
struct AR_Battle **hash_table;
unsigned int max_soldiers_g; /* Max # of enemy soldiers */
unsigned int max_soldiers_id_g; /* Max enemy soldiers' ID */

/* Primes for your universal hashing implementation */
unsigned int primes_g[368] = {  5,   7,  11,  13,  17,  19,  23,  29,  31,  37,
                               41,  43,  47,  53,  59,  61,  67,  71,  73,  79,
                               83,  89,  97, 101, 103, 107, 109, 113, 127, 131,
                              137, 139, 149, 151, 157, 163, 167, 173, 179, 181,
                              191, 193, 197, 199, 211, 223, 227, 229, 233, 239,
                              241, 251, 257, 263, 269, 271, 277, 281, 283, 293,
                              307, 311, 313, 317, 331, 337, 347, 349, 353, 359,
                              367, 373, 379, 383, 389, 397, 401, 409, 419, 421,
                              431, 433, 439, 443, 449, 457, 461, 463, 467, 479,
                              487, 491, 499, 503, 509, 521, 523, 541, 547, 557,
                              563, 569, 571, 577, 587, 593, 599, 601, 607, 613,
                              617, 619, 631, 641, 643, 647, 653, 659, 661, 673,
                              677, 683, 691, 701, 709, 719, 727, 733, 739, 743,
                              751, 757, 761, 769, 773, 787, 797, 809, 811, 821,
                              823, 827, 829, 839, 853, 857, 859, 863, 877, 881,
                              883, 887, 907, 911, 919, 929, 937, 941, 947, 953,
                          	  947, 953, 967, 971, 977, 983, 991, 997, 1009, 1013, 1019, 1021, 1031, 1033, 1039, 1049, 1051, 1061, 1063, 1069,
                          	  1087, 1091, 1093, 1097, 1103, 1109, 1117, 1123, 1129, 1151, 1153, 1163, 1171, 1181, 1187, 1193, 1201, 1213, 1217, 1223,
                          	  1229, 1231, 1237, 1249, 1259, 1277, 1279, 1283, 1289, 1291, 1297, 1301, 1303, 1307, 1319, 1321, 1327, 1361, 1367, 1373,
                          	  1381, 1399, 1409, 1423, 1427, 1429, 1433, 1439, 1447, 1451, 1453, 1459, 1471, 1481, 1483, 1487, 1489, 1493, 1499, 1511,
                          	  1523, 1531, 1543, 1549, 1553, 1559, 1567, 1571, 1579, 1583, 1597, 1601, 1607, 1609, 1613, 1619, 1621, 1627, 1637, 1657,
                          	  1663, 1667, 1669, 1693, 1697, 1699, 1709, 1721, 1723, 1733, 1741, 1747, 1753, 1759, 1777, 1783, 1787, 1789, 1801, 1811,
                          	  1823, 1831, 1847, 1861, 1867, 1871, 1873, 1877, 1879, 1889, 1901, 1907, 1913, 1931, 1933, 1949, 1951, 1973, 1979, 1987,
                          	  1993, 1997, 1999, 2003, 2011, 2017, 2027, 2029, 2039, 2053, 2063, 2069, 2081, 2083, 2087, 2089, 2099, 2111, 2113, 2129,
                          	  2131, 2137, 2141, 2143, 2153, 2161, 2179, 2203, 2207, 2213, 2221, 2237, 2239, 2243, 2251, 2267, 2269, 2273, 2281, 2287,
                          	  2293, 2297, 2309, 2311, 2333, 2339, 2341, 2347, 2351, 2357, 2371, 2377, 2381, 2383, 2389, 2393, 2399, 2411, 2417, 2423,
                          	  2437, 2441, 2447, 2459, 2467, 2473, 2477, 2503 };



char* CalculatePath(int);

int a,b;
int minimum_number=1;
int max_number;
int elem=0;
struct Army *ptolemeos=NULL;
 struct Army*mitsos=NULL;
 struct Army*kassandros=NULL;
 struct Army*lysas=NULL;
 struct Army*seleykos=NULL;
struct HorsePQ A;
 struct GA_Tree ARXIGOS;
 struct Army *HayateKirino=NULL;
 
void randomnum(){
      a=rand();
     b=rand();
    a=a%(max_number + 1 - minimum_number) + minimum_number;
    b=b%20;
}

int hash(int X){
    randomnum();
    return (a*X+b)%max_number%(max_soldiers_g/2);
}


void insert_S(int thesi,int id){
    struct AR_Battle * node=malloc(sizeof(struct AR_Battle));
    node->id=id;
    if(hash_table[thesi]==NULL){
       hash_table[thesi]=node;
        hash_table[thesi]->next=NULL;
    }else{
         node->next=hash_table[thesi];
        hash_table[thesi]=node;
    }
}

void print_this_S(struct AR_Battle *nicktron){
    while(nicktron!=NULL) {
        printf("<%d>",nicktron->id);
        nicktron=nicktron->next;
    }
}


void deleteAlt(int thesi) 
{ 
    int ar=0;
    if (hash_table[thesi] == NULL) 
        return; 
  while(hash_table[thesi]!=NULL&&ar!=3){
      hash_table[thesi]=hash_table[thesi]->next;
        ar++;
  }     

} 


void Start_Delete(struct GA_Battle *tmp){
    if(tmp==NULL)return;
    int start=tmp->soldier_id;
    int thesi=hash(start);
    deleteAlt(thesi);
    Start_Delete(tmp->lc);
    Start_Delete(tmp->rc);

}



/*
void reset() {
     if (trial) {
         free(trial);
         trial = NULL;
         elem=0;
     }
 }*/




struct Horse HeapDeleteMin() {
            int m = 0;
            int p;
            struct Horse h;
            h.age=-1;
            h.id=-1;
        if (A.size == 0) return h;
        struct Horse I = A.horsePQ[0]; 
        int K = A.horsePQ[A.size-1].age;
        int L=A.horsePQ[A.size-1].id;
        A.size--; 
        if (A.size == 0)  return I ; 
        
        while ((((2*m+1 )< A.size) && (K > A.horsePQ[2*m+1].age)) || (((2*m+2) < A.size) && (K > A.horsePQ[2*m+2].age))) {
        if ((2*m +2) < A.size) { 
        if (A.horsePQ[2*m+1].age < A.horsePQ[2*m+2].age)
        p = 2*m+1; 
        else p = 2*m+2;
        }
        else p = A.size-1;
        A.horsePQ[m].age = A.horsePQ[p].age;
        A.horsePQ[m].id = A.horsePQ[p].id;
        m = p;
        }
        A.horsePQ[m].age = K;
        A.horsePQ[m].id=L;
        return I;
}



/*
void Path(int size){
    if(size==0) return ;
    if(elem==0){
        trial = (int*)malloc( sizeof(int));
    }else{
        trial = (int*)realloc(trial, sizeof(int));
    }
     elem++;
    // printf("emfanizo ton arithmo ton stoixeion pou dynamic array %d",elem);
   if(size%2==0){
    trial[elem-1] = 0;
    Path((size-2)/2);
   }else{
       trial[elem-1] = 1;
   Path((size-1)/2);
   }
}*/


char* CalculatePath(int treeSize) {
	 if (treeSize <= 1) return '\0';
    const int BITVECTOR_LENGTH = (int) log2(treeSize) + 1;
	elem=BITVECTOR_LENGTH;
    char *bitvector = calloc(BITVECTOR_LENGTH, sizeof(char));
    bitvector[BITVECTOR_LENGTH - 1] = '\0';
    int i;
    for (i = BITVECTOR_LENGTH - 2; i >= 0; i--) {
        bitvector[i] = '0' + treeSize % 2;
        treeSize /= 2;
    }
    return bitvector;
}

struct Army *newNode(int item) { 
    struct Army *temp =  (struct Army *)malloc(sizeof(struct Army)); 
    temp->id = item; 
    temp->lc = temp->rc = NULL; 
    return temp; 
} 

struct GA_Battle *makeNode_emp(int item,int i) { 
    struct GA_Battle *temp =  (struct GA_Battle *)malloc(sizeof(struct GA_Battle)); 
    temp->soldier_id = item; 
    temp->horse_id=i;
    temp->lc = NULL;
    temp->rc = NULL; 
    return temp; 
} 

struct GA_Tree createmyempire(struct GA_Tree ARXIGOS,struct Army* NASASKA){
          char *trial;
		int i;
            struct Horse h=HeapDeleteMin(A);
            struct GA_Battle*tmp=ARXIGOS.Ga_tree;
            //printf("mpika stin sinartisi me timi %d\n",NASASKA->id);
            if(ARXIGOS.size==0){
             //   printf("mpika edo gt to dentro einai keno arithmos stoixeion %d\n",ARXIGOS.size);
                tmp=makeNode_emp(NASASKA->id,h.id);
                ARXIGOS.Ga_tree=tmp;
                ARXIGOS.size++;
            }else if(ARXIGOS.size==1) {
                    ARXIGOS.Ga_tree->lc=makeNode_emp(NASASKA->id,h.id);
                  // printf("to deftero mpainei edo");
                   ARXIGOS.size++;
                  }else if(ARXIGOS.size==2){
                      ARXIGOS.Ga_tree->rc=makeNode_emp(NASASKA->id,h.id);
                      ARXIGOS.size++;
                     // printf("to trito mpainei edo");
                  }else{

              //  printf("mpika edo gt to dentro den einai keno arithmos stoixeion %d\n",ARXIGOS.size);
               //printf("%d",ARXIGOS.size);
           
               trial= CalculatePath(ARXIGOS.size+1);
               /* printf("o pinakas einai\n");
                for(int i=elem-1;i>-1;i--){
                    printf("%d",trial[i]);
                    }*/
                tmp=ARXIGOS.Ga_tree;
                ARXIGOS.size++;
                for(i=0;i<elem-2;i++){
                    if(trial[i]=='1'){
                        tmp=tmp->rc;
                      // printf("kinoume deksia\n");
                    }else if(trial[i]=='0') {
                        tmp=tmp->lc;
                        //printf("kinoume aristera\n");
                    }
                }
              //  printf("to kleidi einai %c",trial[elem-2]);
                if(trial[elem-2]=='0'){
                //   printf("topotheto aristera\n");
                        tmp->lc=makeNode_emp(NASASKA->id,h.id);
                        
                    }else if(trial[elem-2]=='1'){
                       tmp->rc=makeNode_emp(NASASKA->id,h.id);
                  //     printf("topotheto deksia\n");
                    }
                    
     
            }
     // reset();      
    return ARXIGOS;

}

void PreOrder(struct Army* p) { 
        if (p == NULL) return; 
        //printf("diavasa %d\n",p->id);
        //printf("hi");
        PreOrder(p->lc);
       // printf("mpika stin sinartisi\n");
        ARXIGOS=createmyempire(ARXIGOS,p);
       
        //printf("pao deksia\n");
        PreOrder(p->rc);
}

void PeOrder(struct Army* p) { 
        if (p == NULL) return;
        PeOrder(p->lc);
        printf("<%d>",p->id);
        PeOrder(p->rc);
}

void PeOrder1(struct GA_Battle* p) { 
        if (p == NULL) return;
        PeOrder1(p->lc);
        printf("<%d %d> ",p->soldier_id,p->horse_id);
        
        PeOrder1(p->rc);
}


struct Army* insert(struct Army* node, int key) { 
    if (node == NULL) return newNode(key); 
  
    if (key < node->id) 
        node->lc  = insert(node->lc, key); 
    else if (key > node->id) 
        node->rc = insert(node->rc, key);    
  
    return node; 
}


void PrintHorses(struct HorsePQ A){
      int i = 1;
      int metr=0;
    int j = 1;
    int k = 2;

    while(i<=A.size){
        printf("Level %d  ",metr);
        while(j<k){
            if(A.size-(j-1) <= 0) break;
            printf("<%d,%d>,",A.horsePQ[i-1].id,A.horsePQ[i-1].age);
            j++;
            i++;
        }
        printf("\n");
        metr++;
        k = k*2;
    }
    
   

}



struct HorsePQ HeapInsert(struct HorsePQ A,struct Horse h){
    int m;
        if(A.size==100) {
            printf("max horses");
            return A;
        }
        m=A.size;
    while(m>0 && h.age<A.horsePQ[(m-1)/2].age){
        A.horsePQ[m].age=A.horsePQ[(m-1)/2].age;
        A.horsePQ[m].id=A.horsePQ[(m-1)/2].id;
        m=(m-1)/2;
    }
     A.horsePQ[m].age=h.age;
     A.horsePQ[m].id=h.id;

    A.size++;
        return A;
}

struct GA_Battle *Delete_this_shit(){
    char*trial;
	int i;
        struct GA_Battle *tmp=ARXIGOS.Ga_tree;
        struct GA_Battle *tmp1=(struct GA_Battle*)malloc(sizeof(struct GA_Battle));
        trial=CalculatePath(ARXIGOS.size);
        //printf("to size einai %d",ARXIGOS.size);
        //printf("@@@@@@@@@");
        for( i=0;i<elem-2;i++){
           // printf("%c",trial[i]);
                if(trial[i]=='1'){
                        tmp=tmp->rc;
                       // printf("kinoume deksia\n");
                       // if(tmp==NULL)printf("MALAKA");
                    }else if(trial[i]=='0') {
                        tmp=tmp->lc;
                       // printf("kinoume aristera\n");
                       //if(tmp==NULL)printf("MALAKA");
                    }
                }
       // printf("hi");
       // if(tmp==NULL)printf("MALAKA");
     
                if(trial[elem-2]=='0'){
                       // if(tmp->lc==NULL)printf("MALAKA1");
                    //printf("hi");
                  // printf("to deksiotero einai to %d\n",tmp->lc->soldier_id);
                    tmp1->horse_id=tmp->lc->horse_id;
                    tmp1->soldier_id=tmp->lc->soldier_id;
                   // printf("hi");
                        tmp->lc=NULL;
                        
                    }else if(trial[elem-2]=='1') {
                        /*if(tmp->rc==NULL)printf("MALAKA");
                        printf("to deksiotero einai to %d\n",tmp->rc->soldier_id);
                        printf("hey");*/
                       tmp1->horse_id=tmp->rc->horse_id;
                    tmp1->soldier_id=tmp->rc->soldier_id;
                      // printf("hi");
                        tmp->rc=NULL;
                    }
                    
     
            
     // reset();  
     
      return tmp1;

}



struct GA_Battle *Delete_the_fucking_hitler(struct GA_Battle * tmp,int del){
    static int ar=0;
    struct GA_Battle *t;
    if(tmp==NULL)return NULL;
    if(ar==del){
       // printf("ARXIGOOOS%d",ARXIGOS.size);
        t=Delete_this_shit();
         ARXIGOS.size--;
       // printf("%d",t->soldier_id);
        tmp->soldier_id=t->soldier_id;
        tmp->horse_id=t->horse_id;
        ar=0;
    }else{
        ar++;
       tmp->lc= Delete_the_fucking_hitler(tmp->lc,del);
       tmp->rc= Delete_the_fucking_hitler(tmp->rc,del);
    }
    return tmp;


}


bool isFullTree (struct GA_Battle* root, int index, int number_nodes){ 
    // An empty tree is complete 
    if (root == NULL) 
        return (true); 
  
    // If index assigned to current node is more than 
    // number of nodes in tree, then tree is not complete 
    if (index >= number_nodes) 
        return (false); 
  
    // Recur for left and right subtrees 
    return (isFullTree(root->lc, 2*index + 1, number_nodes) && 
            isFullTree(root->rc, 2*index + 2, number_nodes)); 
} 



void print2DUtil(struct GA_Battle *root, int space) 
{ 
int i;
    // Base case 
int flag=0;
    if (root == NULL) {
        flag=1;
    }
    // Increase distance between levels 
    space += 10; 
  
    // Process right child first 
    print2DUtil(root->rc, space); 
  
    // Print current node after space 
    // count 
    printf("\n"); 
    for (i = 10; i < space; i++) 
        printf(" "); 
    if(flag){
        printf("S");
        return;
    }
    printf("%d\n", root->soldier_id); 
  
    // Process left child 
    print2DUtil(root->lc, space); 
} 

unsigned int countNodes(struct GA_Battle* root) 
{ 
    if (root == NULL) 
        return (0); 
    return (1 + countNodes(root->lc) + countNodes(root->lc)); 
} 
