// A C Program to demonstrate adjacency list 
// representation of graphs 
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>


#define MAX_VERTICES 10000
#define MAX_EDGES 3000

int S=0;
int I=0;
int R=0;
int times =0;

//*****************************For graph struct *************************************
// A structure to represent an adjacency list node 

struct AdjListNode 
{ 
  int dest; 
  struct AdjListNode* next; 
}; 

// A structure to represent an adjacency list 


// STATUS 0 = S
// STATUS 1 = I
// STATUS 2 = R


struct AdjList 
{ 
  struct AdjListNode *head; 
  int status;
  int pred_inf_time;
  int rec_time;
}; 

// A structure to represent a graph. A graph 
// is an array of adjacency lists. 
// Size of array will be V (number of vertices 
// in graph) 
struct Graph 
{ 
  int V; 
  struct AdjList* array; 
}; 



// *******************************************FOr QUEUE*************************************
typedef struct node { 
  int data; 

  // Lower values indicate higher priority 
  int priority; 
  int t_ime;
  int action;
  //if action = 0 -> TRANSMIT
   //if action = 1 -> RECOVER

  struct node* next; 

}Node;
Node* pq; 



//*****************************************completed Queue struct **********************************************


//****************************************FOR GRAPH WITH ADJ. LIST ********************************************

// A utility function to create a new adjacency list node 
struct AdjListNode* newAdjListNode(int dest) 
{ 
  struct AdjListNode* newNode = 
  (struct AdjListNode*) malloc(sizeof(struct AdjListNode)); 
  newNode->dest = dest; 
  newNode->next = NULL; 
  return newNode; 
} 

// A utility function that creates a graph of V vertices 
struct Graph* createGraph(int V) 
{ 
  struct Graph* graph = 
    (struct Graph*) malloc(sizeof(struct Graph)); 
  graph->V = V; 

  // Create an array of adjacency lists. Size of 
  // array will be V 
  graph->array = 
  (struct AdjList*) malloc(V * sizeof(struct AdjList)); 

  // Initialize each adjacency list as empty by 
  // making head as NULL 
  int i; 
  for (i = 0; i < V; ++i) 
    graph->array[i].head = NULL; 

  return graph; 
} 

// Adds an edge to an undirected graph 
void addEdge(struct Graph* graph, int src, int dest) 
{ 
  // Add an edge from src to dest. A new node is 
  // added to the adjacency list of src. The node 
  // is added at the begining 
  struct AdjListNode* newNode = newAdjListNode(dest); 
  newNode->next = graph->array[src].head; 
  graph->array[src].head = newNode; 

  // Since graph is undirected, add an edge from 
  // dest to src also 
 
} 

// A utility function to print the adjacency list 
// representation of graph 
void printGraph(struct Graph* graph) 
{ 
  int v; 
  for (v = 0; v < graph->V; ++v) 
  { 
    struct AdjListNode* pCrawl = graph->array[v].head; 
    printf("\n Adjacency list of vertex %d\n head ", v); 
    while (pCrawl) 
    { 
      printf("-> %d", pCrawl->dest); 
      pCrawl = pCrawl->next; 
    } 
    printf("\n"); 
  } 
} 

//*********************************For graph completed****************************************


//*********************************For QUEUE*****************************************************
// Function to Create A New Node 
Node* newNode(int d, int p,int t,int a) 
{ 
  Node* temp = (Node*)malloc(sizeof(Node)); 
  temp->data = d; 
  temp->priority = p; 
  temp->t_ime = t;
  temp->action = a;
  temp->next = NULL; 

  return temp; 
} 

// Return the value at head 
Node* peek(Node** head) 
{ 
  return (*head); 
} 

// Removes the element with the 
// highest priority form the list 
void pop() 
{ 
  Node* temp = pq; 
  pq = pq->next; 
  free(temp); 
} 

// Function to push according to priority 
void push(int d, int p,int t,int a) 
{ 
  Node* start = (pq); 
  if(start == NULL)
  {
    pq = newNode(d,p,t,a);
    return;
  }
  // Create new Node 
  Node* temp = newNode(d, p,t,a); 

  // Special Case: The head of list has lesser 
  // priority than new node. So insert new 
  // node before head node and change head node. 
  if ((pq)->priority > p) { 

    // Insert New Node before head 
    temp->next = pq; 
    (pq) = temp; 
  } 
  else { 

    // Traverse the list and find a 
    // position to insert new node 
    while (start->next != NULL && 
      start->next->priority > p) { 
      start = start->next; 
    } 

    // Either at the ends of the list 
    // or at required position 
    temp->next = start->next; 
    start->next = temp; 
  } 
} 

// Function to check is list is empty 
int isEmpty(Node** head) 
{ 
  return (*head) == NULL; 
} 

//**********************************For QUEUE completed**************************************


//*********************************For COIN**************************************************

int b_coin(int p)
{
  int i=0;
  while(1){
    int r = rand()%100;
    if(r<p)                   ///If prob. of the coin is < then the number generated then it is head
    {
      return i;
    }
    i = i+1;
  }
  return 301;
}
//************************************MIN FUNCTION**********************************************
int mini(int x,int y,int z)
{
   if((x < y)&&(x < z))
   return x;
   else
    {
      if(y < z)
      return y;
      else
      return z;
    }
}


//**********************************SIR**************************************************************

//*********************************FIND_TRANS_SIR****************************************************

void find_trans_SIR(struct Graph *G,int t,int T,int Y,int source,int target,int t_max)
{
  //printf("target sourcr is %d \n",G->array[target].status);
  if(G->array[target].status == 0)
  {
    int inf_time = t+b_coin(T);
    int minimum = mini(G->array[source].rec_time,G->array[target].pred_inf_time,t_max);
    if(inf_time < minimum)
    {
      push(target,inf_time,t,0);
      G->array[target].pred_inf_time = inf_time;
    }
  }
}

////***********************PROCESS_TRANS_SIR*****************************************

void process_trans_SIR(struct Graph* G,int u,int t,int T,int Y,int t_max){
  S = S-1;
  I = I+1;
  times = t;
  G->array[u].status = 2;
  G->array[u].rec_time = t+b_coin(Y);

  if(G->array[u].rec_time < t_max){

    push(u,G->array[u].rec_time, t,1);
  }
  struct AdjListNode* pCrawl = G->array[u].head;  
  while (pCrawl) 
  { 
    find_trans_SIR(G,t,T,Y,u,pCrawl->dest,t_max) ;
    pCrawl = pCrawl->next; 
  }
}

//****************************PROCESS_REC_SIR*********************************************


void  process_rec_SIR(struct Graph* G,int u,int t){
  times = t;
  I = I-1;
  R = R+1;

  G->array[u].status = 2;
  pop();
 }



//*******************************************************************************************


// Driver program to test above functions 


int main() 
{ 
  // create the graph given in above fugure 
  int numberOfVertices =MAX_VERTICES;
  srand ( time(NULL) );
    int maxNumberOfEdges = rand() % MAX_EDGES;
   // printf("maxNumberOfEdges %d\n",maxNumberOfEdges );
  struct Graph* graph = createGraph(numberOfVertices); 


 // *******Creating random graph************************
            srand ( time(NULL) );

    for (int i = 0; i < numberOfVertices; i++){
      graph->array[i].status = 0;
      graph->array[i].pred_inf_time = 500;
      
        for (int j=0; j < maxNumberOfEdges; j++){
          
            if (rand()%2 == 1){ 
                int linkedVertex = rand() % numberOfVertices;
                addEdge(graph,i,linkedVertex);
            }

        }
    }

//**************************************************************

    int t_max = 300;
    double T = 50; //prob for transmitting to neighbour
    double Y = 20; //prob for recovery


//*****************IF WANT FOR RANDOM NUMBER OF INI_INFECTED THEN*******************

//use   int ran_init_infected = rand()%10000;
//And comment the bellow line


    int ran_init_infected = 1;
    int inital_infecteds[ran_init_infected];



    for(int t = 0;t<ran_init_infected;t++)
    {
      int i = rand()%numberOfVertices;
      inital_infecteds[t] = i;
    }

    S = numberOfVertices -  ran_init_infected;
    R =0;
    I = ran_init_infected;
    for(int i=0;i<ran_init_infected;i++)
    {
      graph->array[inital_infecteds[i]].pred_inf_time = 0;
      push(inital_infecteds[i], 0,0,0);  ///(node,priorit,time,action)

    }

   int count =0;
   printf("Day 0 : Suspectible count : %d || Infected count : %d || Recovered count : %d\n",S,I,R);
///**********************************************************************************************

//**************************THE FAST_SIR LOOP**************************************************
 while (!isEmpty(&pq) & count<300){
  int c=pq->action;

      if(c == 0) ///if it is transmit 
      {
        if(graph->array[peek(&pq)->data].status == 0)
        {
          process_trans_SIR(graph,peek(&pq)->data,peek(&pq)->t_ime,T,Y,t_max);   // process_trans_SIR(graph,EVENT.node,EVENT.time,probabilty,probability,MAX_TIME)
        }   else{
                  pop();

  }
    }
      else{
                  process_rec_SIR(graph,peek(&pq)->data,peek(&pq)->t_ime);

  }
  printf("\n");
      count++;
      printf("Day %d : Suspectible count : %d || Infected count : %d || Recovered count : %d\n",count,S,I,R);
  }

   printf("\n");




  return 0; 
} 
