// A C++ program to implement greedy algorithm for graph coloring
#include <iostream>
#include <list>
#include <time.h>
#include <algorithm>

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


    // Function that scores how well our alrorithm did, if score is bellow 0 the alrorithm placed colors wrong(neighbor have same color). If else the score give us how manny colors were diffrent colors were used.
    int scoreOfAlrorithm(int result[]);


    // Hillclimbing algorythm.
    void hillClimbingAlgorithm(int iteracion);

    // Nuclear white color
    void whiteout(int result[]);

    // prints how manny unique_colors where ussed
    int unique_color(int *arr);


    int badConnections(list<int> *adj_list, int v, int *result);

    int adjListNodes(list<int> *adj_list, int v);

    void hillClimbingAlgorithmBestPoint(int iteracion);

    int worstPointColor( int *result,int worstPoints[]);
};

void Graph::addEdge(int v, int w) {
    adj[v].push_back(w);
    adj[w].push_back(v); // Note: the graph is undirected
}

int Graph::unique_color(int arr[]) {
    int counter = 0;
    int backup[V];

    for (int u = 0; u < V; u++) {
        backup[u] = arr[u];
    }
    sort(backup, backup + V);

    //  Finding unique numbers
    for (int i = 0; i < V; i++) {
        if (backup[i] == backup[i + 1]) {
            continue;
        } else {
            // cout<<arr[i]<<" ";
            counter++;
        }
    }
    return counter;
}

int Graph::adjListNodes(list<int> adj_list[], int v) {
    int maxNodesConnected = 0;
    int nodes[V] = {0};
    for (int i = 0; i < v; i++) {
        //    cout << i << "--->";
        list<int>::iterator it;
        for (it = adj_list[i].begin(); it != adj_list[i].end(); ++it) {
            nodes[i]++;
            //      cout << *it << " ";
        }
        //    cout << endl;
        maxNodesConnected = max(maxNodesConnected, i);
    }
    // cout << "maximum connection in noddes: " << maxNodesConnected;
    return maxNodesConnected;
}

int Graph::badConnections(list<int> *adj_list, int v, int result[]) {
    int bad = 0;

    for (int i = 0; i < v; i++) {
        list<int>::iterator it;
        for (it = adj_list[i].begin(); it != adj_list[i].end(); ++it) {
            if (result[i] == result[*it]) {
                //cout << "\n kolor: " << result[i] << " na miejscu: " << i << " jest taki sam jak kolor " << result[*it]
                //  << " na pozycji: " << *it;
                bad++;
            }
        }
    }
    return bad;
}

int Graph::scoreOfAlrorithm(int result[]) {
    //int score = (unique_color(result) - (unique_color(result) * unique_color(result)));
    int score = (badConnections(adj, V, result) + unique_color(result));

    // cout << "score of our alrorithm is: " << score << endl;
    return score;
}

// Algorytm gorki
void Graph::hillClimbingAlgorithm(int iteracion) {
    srand(time(nullptr));
    int randomColor;
    int result[V];
    int currentState;
    int backup[V];
    whiteout(result); // nuclear white

    for (int i = 0; i < iteracion; i++) {
        for (int u = 0; u < V; u++) {
            backup[u] = result[u];
        }
        currentState = scoreOfAlrorithm(result);
        for (int x = 0; x < V; x++) {
            randomColor = (rand() % adjListNodes(adj, V));
            result[x] = randomColor;
        }
        if (currentState < scoreOfAlrorithm(result)) {
            for (int u = 0; u < V; u++) {
                result[u] = backup[u];
            }
        }
    }

    for (int u = 0; u < V; u++) {
        cout << "Vertex " << u << " ---> Color "
             << result[u] << endl;
    }
    printf("There is %d different  colors \n", unique_color(result));
    cout << " \n Wrong connection happend" << badConnections(adj, V, result) << endl;
    cout << "Our algorithm recived score:  " << scoreOfAlrorithm(result);

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

            if (!available[cr]) {
                break;
            }
        result[u] = cr; // Assign the found color
        // Reset the values back to false for the next iteration
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
            if (result[*i] != -1)
                available[result[*i]] = false;
    }

    // print the result
    for (int u = 0; u < V; u++) {
        cout << "Vertex " << u << " ---> Color "
             << result[u] << endl;
    }
    // scoreOfAlrorithm(result);
    printf("There is %d different  colors \n", unique_color(result));

    cout << " wyswietlanie polaczen : \n";
    adjListNodes(adj, V);

    cout << " \n bad connection are: " << badConnections(adj, V, result) << endl;
    cout << "Nasz algorytm uzyskal ocene: " << scoreOfAlrorithm(result);

}


void Graph::whiteout(int result[]) {
    for (int u = 0; u < V; u++)
        result[u] = 0;

}

void Graph::hillClimbingAlgorithmBestPoint(int iteracion) {
    srand(time(nullptr));
    int randomColor;
    int result[V];
    int currentState;
    int backup[V];
    int badPoints[V];
    whiteout(result); // nuclear white
    whiteout(badPoints);


    for (int i = 0; i < iteracion; i++) {
        for (int u = 0; u < V; u++) {
            backup[u] = result[u];
        }
        currentState = scoreOfAlrorithm(result);
        for (int x = 0; x < V; x++) {
            worstPointColor(result,badPoints);

            randomColor = (rand() % adjListNodes(adj, V));
            if (badPoints[x]!=0)       {
                result[x] = randomColor;

            }
        }
        if (currentState < scoreOfAlrorithm(result)) {
            for (int u = 0; u < V; u++) {
                result[u] = backup[u];
            }
        }
    }

    for (int u = 0; u < V; u++) {
        cout << "Vertex " << u << " ---> Color "
             << result[u] << endl;
    }
    printf("There is %d different  colors \n", unique_color(result));
    cout << " \n Wrong connection happend:  " << badConnections(adj, V, result) <<" times"<< endl;
    cout << "Our algorithm recived score:  " << scoreOfAlrorithm(result)<< endl;
    whiteout(result);

    worstPointColor(result,badPoints);

}

int Graph::worstPointColor(int *result, int *worstPoints) {
    whiteout(worstPoints);
    for (int i = 0; i < V; i++) {
        list<int>::iterator it;
        for (it = adj[i].begin(); it != adj[i].end(); ++it) {
            if (result[i] == result[*it]) {
                worstPoints[i]++;

            }
        }
    }


    return 0;

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


    //g1.greedyColoring();
    // g1.hillClimbingAlgorithm(100);
    g1.hillClimbingAlgorithmBestPoint(100);
    cout << endl;

    // g1.greedyColoring();
    // Graph g2(5);
    // g2.addEdge(0, 1);
    // g2.addEdge(0, 2);
    // g2.addEdge(1, 2);
    // g2.addEdge(1, 4);
    // g2.addEdge(2, 4);
    // g2.addEdge(4, 3);
    // cout << "\nColoring of graph 2 \n";
    // g2.hillClimbingAlgorithm(100);
    return 0;
}
