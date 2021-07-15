//Libraries to be included
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define max_vertices 10000 // defining maximum no.of vertices in the graph
#define max_edges 3000     // defining maximum no. of edges from each vertex

int no_of_days=0,no_of_susceptible=0,no_of_infected=0,no_of_recovered=0;
// struct for priority queue
struct queue  
{ 
    int no_inserted_vertices;  //no.of inserted vertices
    int *nodes_value;          //create an array for storing node value
    int *event_time;           // create an array for storing event_time for the node.
    int *event_type;           //create an array for storing event_type for the node.
};
// Each node has 4 types susceptible,infected,recovered,transmit
// Consider 0=susceptible, 1=infected, 2=recovered, 3=transmit
struct queue *root = NULL;     // making root NULL
//Function for swapping the values
void swap(struct queue* head,int i, int j)
{
	int time = head->event_time[i];
	int type = head->event_type[i];
	int value = head->nodes_value[i];      

    head->event_time[i] = head->event_time[j];
    head->event_type[i] = head->event_type[j];
    head->nodes_value[i] = head->nodes_value[j];

    head->event_time[j] = time;
	head->event_type[j] = type;
	head->nodes_value[j] = value;
}
//Function for initializing the queue
void initialize_queue(int size)  
{
    struct queue *head = NULL;
    head = (struct queue*)malloc(sizeof(struct queue));
    head->no_inserted_vertices = 0;                      // No. of inserted vertices in the queue are 0 initially
    head->nodes_value = (int*)malloc(sizeof(int)*size);  // size of node_value array
    head->event_time   = (int*)malloc(sizeof(int)*size); // size of event_time array
    head->event_type   = (int*)malloc(sizeof(int)*size); // size of event_type array
    root = head;
}
//Function for heapifying,this heapify function is for min heap
void heapify(int index)  
{ 
    struct queue* head = root;
    int left = (2*index)+1;                              //Corresponding node's left child index
    int right = (2*index)+2;                             //Corresponding node's right child index
    int smallest = index;
    //If left child index < no.of inserted vertices & it's event_time <= node's event_time,execute this if loop.
    if((left < head->no_inserted_vertices) && (head->event_time[left] <= head->event_time[smallest]))
    {
        smallest = left;
    }
    //If right child index < no.of inserted vertices & it's event_time <= node's event_time,execute this else if loop.
    else if ((right < head->no_inserted_vertices) && (head->event_time[right] <= head->event_time[smallest]))
    {
        smallest = right;
    }
    if(smallest != index)                                 
    {                               
        swap(head,smallest,index);                        //Swapping the values
        heapify(smallest);                                //Call heapify function on the swapped index
    }

}
//Function for inserting into priority queue
void insert(int event_time, int event_type, int nodes_value) 
{
    struct queue* head = root;
    if(head->no_inserted_vertices==0)                     //If no. of vertices=0,then insert the first element into queue
    {
		head->event_time[0] = event_time;
        head->event_type[0] = event_type;
        head->nodes_value[0] = nodes_value;
        head->no_inserted_vertices++;                     //Now increase the count of no. of vertices
    }
    else                                                  //Otherwise ,execute this else loop
    {
		head->event_time[head->no_inserted_vertices] = event_time;
        head->event_type[head->no_inserted_vertices] = event_type;
        head->nodes_value[head->no_inserted_vertices] = nodes_value;
        head->no_inserted_vertices++;                     //Now increase the count of no. of vertices
        int index = (head->no_inserted_vertices/2)-1;
        while(index>=0)
        {
			heapify(index);                               //Now, heapify
			index--;
		}
	}
}
//Function for deleting root of the queue
void delete()  
{
    struct queue* head = root;
    if(head->no_inserted_vertices == 1)                  //If no.of vertices in the queue=0,make no.of inserted vertices 0
    {
        head->no_inserted_vertices = head->no_inserted_vertices-1;
    }
    else                                                 //Else swap the head event_time with right most node in queue and call heapify function on head node
    {
        head->event_time[0] = head->event_time[head->no_inserted_vertices-1];  // swapping head values with last node values
        head->event_type[0] = head->event_type[head->no_inserted_vertices-1];
        head->nodes_value[0] = head->nodes_value[head->no_inserted_vertices-1];

        head->no_inserted_vertices = head->no_inserted_vertices-1;             //As we are deleting a node, decrease no. of vertices by 1
        heapify(0);                                                            //hepify on head node
    }
}
//This function initializes adjacency matrix
void initialize_graph(int **adjacency_matrix, int no_of_vertices)  
{
    for(int i=0; i<no_of_vertices; i++)
    {
        for(int j=0; j<no_of_vertices; j++)
        {
            adjacency_matrix[i][j] = 0;                 //All values in adjacency matrix are 0 initially
        }
    }
}
//Function for creating graph
void create_graph(int **adjacent_matrix, int no_of_vertices, int max_no_of_edges)  
{
    int vertexCounter,edgeCounter,linkedVertex;
    for(vertexCounter=0; vertexCounter < no_of_vertices; vertexCounter++) //'for' loop for incrementing the vertexCounter
    {
        for(edgeCounter=0; edgeCounter < max_no_of_edges; edgeCounter++)  //'for' loop for incrementing the edgeCounter
        {
            if(rand()%2==1)                                               //vertex has an edge if this 'if' condition satisfies
            {
                linkedVertex = rand() % no_of_vertices;                   //randomly generate vertex for creating an edge between vertices
                adjacent_matrix[vertexCounter][linkedVertex] = 1;         //if there is an edge between the two vertices then make this 1
            }
        }
    }
}
//Function for printing graph
void print_graph(int **adjacent_matrix,int no_of_vertices)
{
    for(int i=0;i<no_of_vertices;i++)
    {
        for(int j=0;j<no_of_vertices;j++)
        {
            printf("%d ", adjacent_matrix[i][j]);
        }
        printf("\n");
    }
}
// struct for status
struct status
{
	int *type;                    //Create an array for storing type
	int *type_time;               //Create an array for storing type
};
struct status*array1 = NULL;      //Make array1 NULL
//Function for initializing the status
void initialize_status(int size)  
{
    struct status *array = NULL;
    array = (struct status*)malloc(sizeof(struct status));
    array->type   = (int*)malloc(sizeof(int)*size);       // size of the type array
    array->type_time   = (int*)malloc(sizeof(int)*size);  // size of type_time array
    array1 = array;
}
//Function for storing initial status of the vertices
void statusarray(int no_of_vertices, int t_max) 
{
	struct status*array = array1;
    for(int i=0; i<no_of_vertices;i++)
    {
        array->type[i] = 0;                // initially all the vertices are taken susceptible = 0
        array->type_time[i] = 3*t_max;  // initially all vertices has some infinite time
    }
}
//Function for updating status of the vertices that are infected 
void initial_infectants(int no_of_infected_vertices)
{
	struct status*array = array1;
    for(int i=0; i<no_of_infected_vertices;i=i+1)
    {
        array->type_time[i] = 0;          //Infected node's event time is made zero
        insert(0,3,i);                    //Add infected vertices to queue
    }
}
//Function for calculating minimum value of the three given values
int minimum(int source_time,int target_time,int t_max)  
{
    if(source_time < target_time)        //If source_time is less than target_time,then compare among source_time & t_max.
    {
        if(source_time < t_max)
            return source_time;
        else
            return t_max;
    }
    else                                 //If source_time greater than target_time,compare among target_time & t_max
    {
        if(target_time < t_max)
            return target_time;
        else
            return t_max;
    }
}
//Function for tossing a biased coin.This returns the count at which first head occured.
int coin_toss(float val)
{
	int value=val*100;
    int number,count=1;
    number = rand() % 100 + 1;     //generates a random no. between 0 to 100.
    if(count==1&&number<=value)
    {
		return count;
	}
    while(number>value)
    {
		number = rand() % 100 + 1;
		count++;	
	}
    return count;
}
//Helper function for process_trans_SIR
void find_trans_SIR(int event_time, float transmission_rate, int source, int target, int t_max)
{
	struct status* array = array1;
    if(array->type[target] == 0)         //If it's susceptible,execute this if loop.
    {
      int inf_time = event_time + coin_toss(transmission_rate);
      int minimum_value = minimum(array->type_time[source],array->type_time[target],t_max);
      if(inf_time < minimum_value)
      {
          insert(inf_time,3,target);
          array->type_time[target] = inf_time;
      }
    }
}
//Function for transmission vertices,when vertice is susceptible and has the possibility to transmit
void process_trans_SIR(int **adjacency_matrix,int nodes_value,int event_time,float transmission_rate,float recovery_rate,int *days_array,int *susceptible_vertices, int *infected_vertices,int *recovered_vertices,int t_max,int no_of_vertices)
{
	struct status* array = array1;
    days_array[no_of_days] = no_of_days;
    susceptible_vertices[no_of_days] = --no_of_susceptible;     // No. of susceptible vertices reduce by 1
    infected_vertices[no_of_days] = ++no_of_infected;           // No. of infected vertices increase by 1
    recovered_vertices[no_of_days] = no_of_recovered;           // No. of recovered vertices is the same
    no_of_days++;
    array->type[nodes_value] = 1;                            // Updating the status of array to infected
    array->type_time[nodes_value] = event_time + coin_toss(recovery_rate); // Time gets updated

    if(array->type_time[nodes_value] < t_max)
    {
        insert(array->type_time[nodes_value],2,nodes_value);
    }
    for(int adjacent_count = 0;adjacent_count<no_of_vertices;adjacent_count++)
    {
		if(adjacency_matrix[nodes_value][adjacent_count] == 1)
		{
			find_trans_SIR(event_time,transmission_rate,nodes_value,adjacent_count,t_max);
		}
	}
}
//Function for recovered vertices 
void process_rec_SIR(int nodes_value,int event_time,int *days_array,int *susceptible_vertices,int *infected_vertices,int *recovered_vertices)
{
	struct status* array = array1;
    days_array[no_of_days] = no_of_days;
    susceptible_vertices[no_of_days] = no_of_susceptible; //No. of susceptible vertices is the same
    infected_vertices[no_of_days] = --no_of_infected;     //No. of infected vertices reduce by 1
    recovered_vertices[no_of_days] = ++no_of_recovered;   //No. of recovered vertices increase by 1
    no_of_days++;
    array->type[nodes_value] = 2;                      //Updating the status of that vertex to recovered
}
//Function for initializing times,susceptible,infected and recovered array to 0
void initialize_array(int *array, int t_max)           
{
    for(int i=0;i<t_max;i=i+1)
    {
        array[i] = 0;
    }
}
//
int main()
{
	srand(time(NULL));
	float recovery_rate=0.2,transmission_rate=0.5; // recovery and transmission rate
    int t_max=300;                                 // Maximum no. of days for the simulation
    int no_of_vertices=0;
    no_of_vertices = rand() % max_vertices + 1;
    int max_no_of_edges = rand() % max_edges;      // Maximum no of edges from each vertex

    int **adjacency_matrix = (int**)malloc(no_of_vertices*sizeof(int *));   // Implementing graph using adjacency matrix
        for (int i=0; i<no_of_vertices; i++)
            adjacency_matrix[i] = (int*)malloc(no_of_vertices*sizeof(int));  // Adjacency matrix is a square matrix with no_of vertices size

    initialize_queue(2*no_of_vertices);                                      //Initialize priority queue
    printf("No. of vertices in graph:%d\n",no_of_vertices);
    printf("Maximum edges from each vertex:%d\n",max_no_of_edges);
    initialize_graph(adjacency_matrix,no_of_vertices);                       //Initialize the adjacency matrix 
    create_graph(adjacency_matrix,no_of_vertices,max_no_of_edges);           //Create a graph

    int no_of_infected_vertices=rand() % no_of_vertices+1;
    printf("No. of infected vertices:%d\n",no_of_infected_vertices);
    initialize_status(no_of_vertices);                                      //Initializing status
    statusarray(no_of_vertices,t_max);                               //Call statusarray function
    initial_infectants(no_of_infected_vertices);                     //Call initial_infectants function.

    int *days_array = (int*)malloc(sizeof(int)*t_max);                      //Initialize array for days.
    initialize_array(days_array,t_max);
    int *susceptible_vertices = (int*)malloc(sizeof(int)*t_max);               //Initialize the array for no. of susceptible vertices 
    initialize_array(susceptible_vertices,t_max);
    int *infected_vertices = (int*)malloc(sizeof(int)*t_max);                  //Initialize the array for no. of susceptible vertices 
    initialize_array(infected_vertices,t_max);
    int *recovered_vertices = (int*)malloc(sizeof(int)*t_max);                 //Initialize the array for no. of susceptible vertices 
    initialize_array(recovered_vertices,t_max);
    days_array[0] = 0;                                                      //Initially at 0th day
    susceptible_vertices[0] = no_of_vertices;                                  //Initially all the vertices are susceptible
    infected_vertices[0] = 0;                                                  //Initially 0 vertices are infected
    recovered_vertices[0] = 0;                                                 //Initially 0 vertices are recovered
     
    no_of_days++;
    no_of_susceptible = no_of_vertices;
    int day = 1;                                                           //Starting the day counting with 1 as data for 0th day is entered
    while(root->no_inserted_vertices != 0 && day < t_max)                  //Execute this while loop until it's empty queue or until max days 
    {
        int event_time = day;                                              //Consider the first vertex of queue
        int event_type = root->event_type[0];
        int nodes_value = root->nodes_value[0];
        delete();                                                          // Delete the first vertex
        if(event_type == 3)  //If vertex has a possibility of transmitting the disease,that vertex is infected vertex
        {
            if(array1->type[nodes_value] == 0) //If vertex is susceptible
            {
                //Call process_trans_SIR
                process_trans_SIR(adjacency_matrix,nodes_value,event_time,transmission_rate,recovery_rate,days_array,susceptible_vertices,infected_vertices,recovered_vertices,t_max,no_of_vertices);
            }
        }
        else    //If vertex has no possibility to transmit then it can infect any other vertex and it can get recovered but it remains in the susceptible array
        {
            //Call process_rec_SIR function
            process_rec_SIR(nodes_value,event_time,days_array,susceptible_vertices,infected_vertices,recovered_vertices);
        }
        day++; 
    }
    //Finally prints the times,S,I,R
    printf("Time\tS\tI\tR\n");
    for (int i = 0; i < no_of_days; ++i)
    {
        printf("%d\t%d\t%d\t%d\n", days_array[i], susceptible_vertices[i], infected_vertices[i], recovered_vertices[i]);
    }

    return 0;
}
