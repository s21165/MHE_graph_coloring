// A C++ program to implement greedy algorithm for graph coloring
#include <iostream>
#include <list>
#include <time.h>
using namespace std;

// A class that represents an undirected graph
class Graph {
    int V; // No. of vertices
    list<int> *adj; // A dynamic array of adjacency lists
public:
    // Constructor and destructor
    Graph(int V) {
        this->V = V;
        adj = new list<int>[V];
    }

    ~Graph() {
        delete[] adj;
    }

    // function to add an edge to graph
    void addEdge(int v, int w);

    // Prints greedy coloring of the vertices
    void greedyColoring();

    // Prints how manny collor was used in coloring
    int colorUsed(int result[]);

    // Prints how manny colors where used bad (adjacent color same)
    int colorUsedBad(int *result);

    // Function that scores how well our alrorithm did, if score is bellow 0 the alrorithm placed colors wrong(neighbor have same color). If else the score give us how manny colors were diffrent colors were used.
    int scoreOfAlrorithm(int result[]);



    // Hillclimbing algorythm.
    void hillClimbingAlgorithm(int iteracion );

    void whiteout(int result[]);
};


int Graph::colorUsed(int result[]) {
    int max = 0;
    for (int i = 0; i < sizeof(result) + 1; i++) { max = std::max(result[i], max); }
    //  printf ("There is %d different of colors \n",  max+1);
    return max;
}

void Graph::addEdge(int v, int w) {
    adj[v].push_back(w);
    adj[w].push_back(v); // Note: the graph is undirected
}


int Graph::colorUsedBad(int *result) {
    bool goodColor[V];
    int sum = 0;
    for (int u = 0; u < V; u++) {
        goodColor[u] = true;

        list<int>::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i) {
            if (result[*i] != -1 && result[*i] == result[u])
                goodColor[result[u]] = false;
        }
    }
    for (auto const &value: goodColor) {
        sum += value;

    }
    return sum - V;
}

int Graph::scoreOfAlrorithm(int result[]) {
    int score = (colorUsed(result) + (colorUsed(result) * colorUsedBad(result)));
   // cout << "score of our alrorithm is: " << score << endl;
    return score;
}
// Algorytm gorki
void Graph::hillClimbingAlgorithm(int iteracion) {
    srand(time(nullptr));
    int random[V];
    int result[V];
    whiteout(result); // nuclear white
    for (int x = 0; x < V; x++) random[x] = x;


    for (int i = 0; i < iteracion; i++)

        for (int j = 0; j < V; j++) {
            int stretch = sizeof(random)/sizeof(random[0]);
            int RanIndex = rand() % stretch;
            random[RanIndex];

            list<int>::iterator y;
            for (y = adj[j].begin(); y != adj[j].end(); ++j) {
                int currentState = scoreOfAlrorithm(result);
                int currentResult = result[*random];
                if (result[j] == result[*random])
                    result[*random] = result[j] + 1;  // if our random point is same as his neihber make him bigger
                if ((currentState > scoreOfAlrorithm(result) && currentState<0) ||  (currentState < scoreOfAlrorithm(result))){
                    for (int x = *random; x <= stretch - 1; x++) {
                        random[x] = random[i + 1];
                    }
                    random[stretch - 1] = {};     // deleting point that have been chacked allready from our array.
                } else result[j]=currentResult;


            }
        }
    for (int u = 0; u < V; u++)
        cout << "Vertex " << u << " ---> Color "
             << result[u] << endl;
}





void Graph::greedyColoring() {
    int result[V];

    // Assign the first color to first vertex
    result[0] = 0;

    // Initialize remaining V-1 vertices as unassigned
    for (int u = 1; u < V; u++)
        result[u] = -1; // no color is assigned to u

    // A temporary array to store the available colors. True
    // value of available[cr] would mean that the color cr is
    // assigned to one of its adjacent vertices
    bool available[V];
    for (int cr = 0; cr < V; cr++)
        available[cr] = false;

    // Assign colors to remaining V-1 vertices
    for (int u = 1; u < V; u++) {
        // Process all adjacent vertices and flag their colors
        // as unavailable
        list<int>::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
            if (result[*i] != -1)
                available[result[*i]] = true;


        // Find the first available color
        int cr;
        for (cr = 0; cr < V; cr++)

            if (available[cr] == false) {
                break;
            }
        result[u] = cr; // Assign the found color
        // Reset the values back to false for the next iteration
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
            if (result[*i] != -1)
                available[result[*i]] = false;
    }

    // print the result
    for (int u = 0; u < V; u++)
        cout << "Vertex " << u << " ---> Color "
             << result[u] << endl;

    scoreOfAlrorithm(result);
    printf("There is %d different  colors \n", colorUsed(result) + 1);
}

void Graph::whiteout(int result[]) {
    for (int u = 0; u < V; u++)
        result[u] = 0;

}


// Driver program to test above function
int main() {
    Graph g1(5);
    g1.addEdge(0, 1);
    g1.addEdge(0, 2);
    g1.addEdge(1, 2);
    g1.addEdge(1, 3);
    g1.addEdge(2, 3);
    g1.addEdge(3, 4);
    g1.addEdge(4, 1);
    g1.addEdge(2, 4);
    cout << "Coloring of graph 1 \n";
  //  g1.greedyColoring();
  g1.hillClimbingAlgorithm(1);

   // Graph g2(5);
   // g2.addEdge(0, 1);
   // g2.addEdge(0, 2);
   // g2.addEdge(1, 2);
   // g2.addEdge(1, 4);
   // g2.addEdge(2, 4);
   // g2.addEdge(4, 3);
   // cout << "\nColoring of graph 2 \n";
   // g2.greedyColoring();
   // return 0;
}
