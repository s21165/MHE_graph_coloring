#include <iostream>
#include <list>
#include <time.h>
#include <algorithm>
#include <vector>
#include <fstream>
#include <chrono>


using namespace std::chrono;


using namespace std;
const int V = 100;

const int tabuSize = 100;
const int familySize = 10;
int a[10];

// A class that represents an undirected graph
class Graph {
    int V; // No. of vertices
    list<int> *adj; // A dynamic array of adjacency lists
public:
    // Constructor and destructor
    Graph(int V) {
        this->V = V;
        adj = new list<int>[::V];
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


    int badConnections(int *result);

    int adjListNodes(list<int> *adj_list, int v);

    void hillClimbingAlgorithmBestPoint(int iteracion);

    void tabuSearch(int iteracion, int tabuSize);

    void tabuSearchBack(int iteracion, int tabuSize);

    int worstPointColor(int *result, int worstPoints[]);

    void simulatedAnnealing(int iteracion);

    void simulatedAnnealingGreedy(int iteracion);

    double randProb();

    void geneticAlgorithm(int iteracion, int familySize, int splitMode, int mutacionMode);


};


class Family {
public:
    int score = 0;
    vector<int> resultsFamily;

};

void write_csv(std::string filename, std::vector<int> vals) {
    // Make a CSV file with one column of integer values
    // filename - the name of the file
    // colname - the name of the one and only column
    // vals - an integer vector of values

    // Create an output filestream object
    ofstream myFile(filename);
    // Send the column name to the stream
    myFile << "id,score" << "\n";

    // Send data to the stream
    for (int i = 0; i < vals.size(); ++i) {
        myFile << i << "," << vals.at(i) << "\n";

    }

    // Close the file
    myFile.close();
}


void Graph::addEdge(int v, int w) {
    adj[v].push_back(w);
    adj[w].push_back(v); // Note: the graph is undirected
}

double Graph::randProb() {
    double p = (rand() / (RAND_MAX + 1.0));
    return p;
}

int Graph::unique_color(int arr[]) {
    int counter = 0;
    int backup[::V];

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


void Graph::whiteout(int result[]) {
    for (int u = 0; u < V; u++)
        result[u] = 0;

}

void whiteoutFamily(int result[]) {
    for (int u = 0; u < ::familySize; u++)
        result[u] = 0;

}

int Graph::adjListNodes(list<int> adj_list[], int v) {
    int maxNodesConnected = 0;
    int nodes[::V] = {0};
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

int Graph::badConnections(int result[]) {
    int bad = 0;

    for (int i = 0; i < V; i++) {
        list<int>::iterator it;
        for (it = adj[i].begin(); it != adj[i].end(); ++it) {
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
    int score = (badConnections(result) + unique_color(result));

    // cout << "score of our alrorithm is: " << score << endl;
    return score;
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


// Algorytm gorki
void Graph::hillClimbingAlgorithm(int iteracion) {
    auto start = high_resolution_clock::now();
    srand(time(nullptr));
    int randomColor;
    int result[::V];
    int currentState;
    int backup[::V];
    whiteout(result); // nuclear white
    std::vector<int> vec;

    for (int i = 0; i < iteracion; i++) {
        for (int u = 0; u < V; u++) {
            backup[u] = result[u];
        }
        currentState = scoreOfAlrorithm(result);

        //for (int x = 0; x < V; x++) {
        randomColor = (rand() % adjListNodes(adj, V));

        result[rand() % V] = randomColor;
        //}
        if (currentState < scoreOfAlrorithm(result)) {
            for (int u = 0; u < V; u++) {
                result[u] = backup[u];
            }
        } else { vec.push_back(scoreOfAlrorithm(result)); }
    }

    for (int u = 0; u < V; u++) {
        cout << "Vertex " << u << " ---> Color "
             << result[u] << endl;
    }
    printf("There is %d different  colors \n", unique_color(result));
    cout << " \n Wrong connection happend " << badConnections(result) << endl;
    cout << "Our algorithm recived score:  " << scoreOfAlrorithm(result);

    write_csv("HillClimbing.csv", vec);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl;
}


void Graph::greedyColoring() {
    int result[::V];

    // Assign the first color to first vertex
    result[0] = 0;

    // Initialize remaining V-1 vertices as unassigned
    for (int u = 1; u < V; u++)
        result[u] = -1; // no color is assigned to u

    // A temporary array to store the available colors. True
    // value of available[cr] would mean that the color cr is
    // assigned to one of its adjacent vertices
    bool available[::V];
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

    cout << " \n bad connection are: " << badConnections(result) << endl;
    cout << "Nasz algorytm uzyskal ocene: " << scoreOfAlrorithm(result);
}


void Graph::hillClimbingAlgorithmBestPoint(int iteracion) {
    auto start = high_resolution_clock::now();
    srand(time(nullptr));
    int randomColor;
    int result[::V];
    int bestNeighbor[::V];
    int backup[::V];
    int badPoints[::V];
    whiteout(result); // nuclear white
    whiteout(badPoints);
    whiteout(bestNeighbor);
    std::vector<int> vec;

    for (int i = 0; i < iteracion; i++) {

        for (int u = 0; u < V; u++) {
            backup[u] = result[u];
        }

        for (int y = 1; y < 5; y++) {

            for (int x = 0; x < V * 4; x++) {
                worstPointColor(result, badPoints); // changing value of badPoits if point have bad neighbor.
                for (int k = 0; k < V; k++) {
                    result[k] = y % 4;
                    if (scoreOfAlrorithm(result) < scoreOfAlrorithm(bestNeighbor)) {
                        bestNeighbor[k] = result[x];
                    }
                    for (int u = 0; u < V; u++) {
                        result[u] = backup[u];
                    }


                }
            }
        }
        for (int u = 0; u < V; u++) {
            result[u] = bestNeighbor[u];

        }
        //vec.push_back(scoreOfAlrorithm(result));
    }
    write_csv("HillClimbingBest.csv", vec);
    for (int u = 0; u < V; u++) {
        cout << "Vertex " << u << " ---> Color "
             << result[u] << endl;
    }
    printf("There is %d different  colors \n", unique_color(result));
    cout << " \n Wrong connection happend:  " << badConnections(result) << " times" << endl;
    cout << "Our algorithm recived score:  " << scoreOfAlrorithm(result) << endl;
    whiteout(result);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl;
}

void Graph::tabuSearch(int iteracion, int tabuSize) {
    auto start = high_resolution_clock::now();
    srand(time(nullptr));
    int randomColor;
    int result[::V];
    int backup[::V];
    string tabuList[::tabuSize];
    int badPoints[::V];
    bool isTabu;
    int bestNeighbor[::V];
    int tabuLastPosision;
    std::vector<int> vec;


    whiteout(result); // nuclear white
    whiteout(badPoints);
    whiteout(bestNeighbor);


    for (int i = 0; i < iteracion; i++) {
        isTabu = false;

        for (int u = 0; u < V; u++) {
            backup[u] = result[u];
        }
        vec.push_back(scoreOfAlrorithm(result));
        for (int y = 0; y < V * 4; y++) {



            result[y%V] =y%4;

            if (scoreOfAlrorithm(result) < scoreOfAlrorithm(bestNeighbor)) {
                bestNeighbor[y] = result[y];
                tabuLastPosision = y;
            } else {
                for (int u = 0; u < V; u++) {
                    result[u] = backup[u];
                }
            }


        }
        if (i > tabuSize) {  // when tabulsit is full we begin to clean old tabu
            tabuList[i % tabuSize] = "";
        }

        if (to_string(bestNeighbor[tabuLastPosision]) == tabuList[i % tabuSize]) {
            isTabu = true;
            //        cout<<"\njest tabu "<<tabuList[y%tabuSize] << " bo tutaj jest " << tabuList[i%tabuSize];

        }
        if (i == 0) isTabu = false;

        if (!isTabu) {
            for (int u = 0; u < V; u++) {
                result[u] = bestNeighbor[u];

                tabuList[i % tabuSize] += to_string(result[u]);
            }
        }
    }

    write_csv("TabuSearch.csv", vec);
    for (int u = 0; u < V; u++) {
        cout << "Vertex " << u << " ---> Color "
             << result[u] << endl;
    }
    printf("There is %d different  colors \n", unique_color(result));
    cout << " \n Wrong connection happend:  " << badConnections(result) << " times" << endl;
    cout << "Our algorithm recived score:  " << scoreOfAlrorithm(result) << endl;
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl;

}


void Graph::tabuSearchBack(int iteracion, int tabuSize) {
    auto start = high_resolution_clock::now();
    srand(time(nullptr));
    int randomColor, tabuLastPosision;
    int result[::V];
    int backup[::V];
    string tabuList[::tabuSize];
    int badPoints[::V];
    bool isTabu;
    int bestNeighbor[::V];
    std::vector<int> vec;


    whiteout(result); // nuclear white
    whiteout(badPoints);
    whiteout(bestNeighbor);


    for (int i = 0; i < iteracion; i++) {
        isTabu = false;
        vec.push_back(scoreOfAlrorithm(result));
        if (badConnections(result) ==
            0) { // if we don't have bad connection let's go back to tabu and try to go from there
            for (int u = 0; u < V; u++) {
                result[u] = backup[u];
            }
        } else {
            for (int u = 0; u < V; u++) {
                backup[u] = result[u];
            }

        }

        for (int x = 0; x < V * 4; x++) {
            for (int y = 1; y < 5; y++) {


                worstPointColor(result, badPoints); // changing value of badPoits if point have bad neighbor.
                    result[x%4] = y%4;
                    if (scoreOfAlrorithm(result) < scoreOfAlrorithm(bestNeighbor)) {
                        bestNeighbor[x] = result[x];
                        tabuLastPosision = x;
                    } else {
                        for (int u = 0; u < V; u++) {
                            result[u] = backup[u];
                        }
                    }
                }


            }


        if (i > tabuSize) {  // when tabulsit is full we begin to clean old tabu
            tabuList[i % tabuSize] = "";
        }
        if (to_string(bestNeighbor[tabuLastPosision]) == tabuList[i % tabuSize]) {
            isTabu = true;
            //        cout<<"\njest tabu "<<tabuList[y%tabuSize] << " bo tutaj jest " << tabuList[i%tabuSize];

        }
        if (i == 0) isTabu = false;

        if (!isTabu) {
            for (int u = 0; u < V; u++) {
                result[u] = bestNeighbor[u];
                tabuList[i % tabuSize] += to_string(result[u]);

            }
        }

    }

    for (int u = 0; u < V; u++) {
        backup[u] = result[u];
    }
    write_csv("TabuSearchBack.csv", vec);
    for (int u = 0; u < V; u++) {
        cout << "Vertex " << u << " ---> Color "
             << result[u] << endl;
    }
    printf("There is %d different  colors \n", unique_color(result));
    cout << " \n Wrong connection happend:  " << badConnections(result) << " times" << endl;
    cout << "Our algorithm recived score:  " << scoreOfAlrorithm(result) << endl;
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl;


}

void Graph::simulatedAnnealingGreedy(int iteracion) {
    int result[::V];
    // Assign the first color to first vertex
    result[0] = 0;
    double particleHeat;
    double temperature = iteracion * 0.6;
    double cooling = iteracion * 0.1;
    int bestResult[::V];

    for (int x = 0; x < iteracion; x++) {





        // Initialize remaining V-1 vertices as unassigned
        for (int u = 1; u < V; u++)
            result[u] = -1; // no color is assigned to u

        // A temporary array to store the available colors. True
        // value of available[cr] would mean that the color cr is
        // assigned to one of its adjacent vertices
        bool available[::V];
        for (int cr = 0; cr < V; cr++)
            available[cr] = false;

        // Assign colors to remaining V-1 vertices
        for (int u = 1; u < V; u++) {
            // Process all adjacent vertices and flag their colors
            // as unavailable
            list<int>::iterator i;
            for (i = adj[u].begin(); i != adj[u].end(); ++i) {
                particleHeat = (rand() % iteracion);

                if (result[*i] != -1 && particleHeat > temperature)
                    available[result[*i]] = true;
            }

            // Find the first available color
            int cr;
            for (cr = 0; cr < V; cr++) {
                particleHeat = (rand() % iteracion);
                if (!available[cr]) {
                    break;
                }
            }
            result[u] = cr; // Assign the found color
            // Reset the values back to false for the next iteration
            for (i = adj[u].begin(); i != adj[u].end(); ++i)
                if (result[*i] != -1)
                    available[result[*i]] = false;
        }
        temperature -= cooling;
        if (scoreOfAlrorithm(result) < scoreOfAlrorithm(bestResult)) {
            for (int u = 0; u < V; u++) {
                bestResult[u] = result[u];
                if (x == iteracion)
                    result[u] = bestResult[u];
            }
        }
    }




    // print the result
    for (int u = 0; u < V; u++) {
        cout << "Vertex " << u << " ---> Color "
             << result[u] << endl;
    }
    // scoreOfAlrorithm(result);
    printf("There is %d different  colors \n", unique_color(result));

    adjListNodes(adj, V);

    cout << " \n bad connection are: " << badConnections(result) << endl;
    cout << "Nasz algorytm uzyskal ocene: " << scoreOfAlrorithm(result);


}

void Graph::simulatedAnnealing(int iteracion) {


    auto start = high_resolution_clock::now();
    srand(time(nullptr));
    int randomColor;
    int result[::V];
    int backup[::V];
    double particleHeat;
    double temperature = iteracion * 0.6;
    double cooling = iteracion * 0.1;
    int badPoints[::V];
    int bestNeighbor[::V];
    std::vector<int> vec;
    whiteout(result); // nuclear white
    whiteout(bestNeighbor);
    double p;
    double expP;

    for (int i = 0; i < iteracion; i++) {

        for (int u = 0; u < V; u++) {
            backup[u] = result[u];
        }
        for (int y = 1; y < V * 4; y++) {

            for (int x = 0; x < V; x++) {
                worstPointColor(result, badPoints); // changing value of badPoits if point have bad neighbor.

                randomColor = (rand() % adjListNodes(adj, V));
                if (badPoints[x] != 0) {
                    while (result[x] == randomColor) randomColor = (rand() % adjListNodes(adj, V));
                    result[x] = randomColor;
                    particleHeat = (rand() % iteracion);
                    double deltaE = temperature;
                    expP = randProb();

                    p = 1 / (1 + exp(-1 * deltaE));
                    expP = randProb();

                    if (scoreOfAlrorithm(result) < scoreOfAlrorithm(bestNeighbor)) {
                        bestNeighbor[x] = result[x];
                    } else if (expP < p) {
                        bestNeighbor[x] = result[x];
                    } else {
                        for (int u = 0; u < V; u++) {
                            result[u] = backup[u];
                        }
                    }
                    temperature -= cooling;


                }
            }
        }


        for (int u = 0; u < V; u++) {
            result[u] = bestNeighbor[u];
        }
        vec.push_back(scoreOfAlrorithm(result));
    }
    write_csv("SimulatedAnnealing.csv", vec);
    for (int u = 0; u < V; u++) {
        cout << "Vertex " << u << " ---> Color "
             << result[u] << endl;
    }
    printf("There is %d different  colors \n", unique_color(result));
    cout << " \n Wrong connection happend" << badConnections(result) << endl;
    cout << "Our algorithm recived score:  " << scoreOfAlrorithm(result);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl;

}

void Graph::geneticAlgorithm(int iteracion, int familySize, int splitMode, int mutaccionMode) {
   auto start = high_resolution_clock::now();
   srand(time(nullptr));
   int randomColor;
   int bestScore=0;
   std::vector<int> vec;
   int result[::V];
   int bestResults[::V];
   int worstPoints[::V];
   Family fam[::familySize];
   Family kids[::familySize];
   Family parrents[::familySize];
   whiteout(result); // nuclear white
   whiteout(bestResults);

   for (int i = 0; i < iteracion; i++) {
       if (i == 0) {
           for (int f = 0; f < familySize; f++) {
               fam[f].resultsFamily.clear();
               for (int x = 0; x < V; x++) {
                   randomColor = (rand() % adjListNodes(adj, V));
                   fam[f].resultsFamily.push_back(randomColor);    // adding family colors
                   result[x] = randomColor;
               }
               whiteoutFamily(a);

               copy(fam[f].resultsFamily.begin(), fam[f].resultsFamily.end(), a);
               fam[f].score = scoreOfAlrorithm(a);

           }
       }


       for (int f = 0; f < familySize; f++) {

           if (fam[f].score < bestScore) {
               bestScore = fam[f].score;
               copy(fam[f].resultsFamily.begin(), fam[f].resultsFamily.end(), bestResults);
               vec.push_back(bestScore);
           }
           int parrent1 = (rand() % familySize);
           int parrent2 = (rand() % familySize);
           while (parrent1 == parrent2)
               parrent2 = (rand() % familySize);
           if (fam[parrent1].score >=
               fam[parrent2].score) // winner of our coloseum is becoming parrents of our kids.
           {
               parrents[(f) % familySize] = fam[parrent1];
           } else parrents[(f) % familySize] = fam[parrent2];

       }
   }

   for (int f = 0; f < familySize - 1; f++) { // making kids from halfs of parrents
       kids[f].resultsFamily.clear();
       if (splitMode == 0) {
           kids[familySize - 1].resultsFamily.clear();
               int random=(rand()%familySize)+1;
           for (int x = 0; x < parrents[f].resultsFamily.size() / (parrents[f].resultsFamily.size()/random); x++) {
               kids[f].resultsFamily.push_back(parrents[f].resultsFamily[x]);
               //  cout << parrents[f].resultsFamily[x] << " ";
           }

           for (int x = parrents[f + 1].resultsFamily.size() / random;
                x < parrents[f + 1].resultsFamily.size(); x++) {
               kids[f].resultsFamily.push_back(parrents[f + 1].resultsFamily[x]);
               //cout << parrents[f].resultsFamily[x] << " ";
           }

           if (f == familySize - 2) {
               for (int x = 0; x < parrents[0].resultsFamily.size() / random; x++) {
                   kids[familySize - 1].resultsFamily.push_back(parrents[0].resultsFamily[x]);
               }
               for (int x = parrents[familySize - 1].resultsFamily.size() / random;
                    x < parrents[familySize - 1].resultsFamily.size(); x++) {
                   kids[familySize - 1].resultsFamily.push_back(parrents[familySize - 1].resultsFamily[x]);
               }
           }
       } else { //secounds method of slicing our parrent's to get their biological material for our next generacion
           kids[familySize - 1].resultsFamily.clear();

           for (int x = 0; x < parrents[f].resultsFamily.size() / 3; x++) {
               kids[f].resultsFamily.push_back(parrents[f].resultsFamily[x]);
               //  cout << parrents[f].resultsFamily[x] << " ";
           }

           for (int x = parrents[f + 1].resultsFamily.size() / 3;
                x < parrents[f + 1].resultsFamily.size() * (2 / 3); x++) {
               kids[f].resultsFamily.push_back(parrents[f + 1].resultsFamily[x]);
               //cout << parrents[f].resultsFamily[x] << " ";
           }

           for (int x = parrents[f + 1].resultsFamily.size() * (2 / 3);
                x < parrents[f + 1].resultsFamily.size(); x++) {
               kids[f].resultsFamily.push_back(parrents[f + 1].resultsFamily[x]);
               //cout << parrents[f].resultsFamily[x] << " ";
           }

           if (f == familySize - 2) {
               for (int x = 0; x < parrents[0].resultsFamily.size() / 3; x++) {
                   kids[familySize - 1].resultsFamily.push_back(parrents[0].resultsFamily[x]);
               }
               for (int x = parrents[familySize - 1].resultsFamily.size() / 3;
                    x < parrents[familySize - 1].resultsFamily.size() * (2 / 3); x++) {
                   kids[familySize - 1].resultsFamily.push_back(parrents[familySize - 1].resultsFamily[x]);
               }

               for (int x = parrents[familySize - 1].resultsFamily.size() * (2 / 3);
                    x < parrents[familySize - 1].resultsFamily.size(); x++) {
                   kids[familySize - 1].resultsFamily.push_back(parrents[familySize - 1].resultsFamily[x]);
               }
           }

       }

   }
   if (mutaccionMode == 0) {
       for (int f = 0; f < familySize; f++) { // mutacion of middle point's in our kids
           double x = (rand() % 100);
           int randompoint=(rand() %V-1)+1;
           if (x < 90) {
               randomColor = (rand() % 4);
               kids[f].resultsFamily.at(randompoint) = randomColor;
           }
           fam[f] = kids[f];             // our kids now become parrent's after they went through mutacion
       }
   } else {
       for (int f = 0; f < familySize; f++) { // mutacion of bad poits in kids
           double x = (rand() % 100);
           if (x > 90) {
               copy(fam[f].resultsFamily.begin(), fam[f].resultsFamily.end(), a);
               worstPointColor(a, worstPoints);
               for (int x = V / 3; x < V * (2 / 3); x++) {
                   int randomPoints = (rand() % adjListNodes(adj, V));
                   if (worstPoints[randomPoints] != 0) {
                       while (result[x] == randomColor) randomColor = (rand() % adjListNodes(adj, V));
                       randomColor = (rand() % adjListNodes(adj, V));
                       kids[f].resultsFamily.at(x) = randomColor;
                   }

               }
           }

           fam[f] = kids[f];             // our kids now become parrent's after they went through mutacion
       }

   }


   for (int f = 0; f < familySize; f++) { // scoring our next generacion
       whiteout(a);
       copy(fam[f].resultsFamily.begin(), fam[f].resultsFamily.end(), a);
       fam[f].score = scoreOfAlrorithm(a);

   }
   for (int f = 0; f < familySize; f++) { // searching for best results in our next generacion
       if (fam[f].score < bestScore) {
           bestScore = fam[f].score;
           copy(fam[f].resultsFamily.begin(), fam[f].resultsFamily.end(), bestResults);
           vec.push_back(bestScore);

       }
   }

//    write_csv("GeneticAlgorithmCutmod10Mutacionmode1.csv", vec);
//
//
//for (int u = 0; u < V; u++) {
//    cout << "Vertex " << u << " ---> Color "
//         << bestResults[u] << endl;
//}
//
//   printf("There is %d different  colors \n", unique_color(bestResults));
//   cout << " \n Wrong connection happend" << badConnections(bestResults) << endl;
//   cout << "Our algorithm recived score:  " << scoreOfAlrorithm(bestResults) << endl;
   auto stop = high_resolution_clock::now();
   auto duration = duration_cast<microseconds>(stop - start);
   cout << "Time taken by function: "
        << duration.count() << " microseconds" << endl;

}


// Driver program to test above function
int main() {

    Graph g1(100);
    g1.addEdge(0, 25);
    g1.addEdge(0, 33);
    g1.addEdge(1, 58);
    g1.addEdge(3, 52);
    g1.addEdge(4, 96);
    g1.addEdge(5, 37);
    g1.addEdge(5, 31);
    g1.addEdge(6, 91);
    g1.addEdge(7, 25);
    g1.addEdge(8, 74);
    g1.addEdge(10, 89);
    g1.addEdge(10, 1);
    g1.addEdge(11, 41);
    g1.addEdge(12, 73);
    g1.addEdge(13, 36);
    g1.addEdge(16, 61);
    g1.addEdge(17, 76);
    g1.addEdge(18, 74);
    g1.addEdge(19, 14);
    g1.addEdge(19, 70);
    g1.addEdge(20, 91);
    g1.addEdge(21, 32);
    g1.addEdge(21, 23);
    g1.addEdge(22, 72);
    g1.addEdge(22, 86);
    g1.addEdge(24, 44);
    g1.addEdge(24, 37);
    g1.addEdge(27, 15);
    g1.addEdge(27, 47);
    g1.addEdge(28, 5);
    g1.addEdge(28, 80);
    g1.addEdge(29, 92);
    g1.addEdge(29, 81);
    g1.addEdge(30, 53);
    g1.addEdge(31, 63);
    g1.addEdge(31, 94);
    g1.addEdge(32, 95);
    g1.addEdge(33, 47);
    g1.addEdge(34, 38);
    g1.addEdge(34, 40);
    g1.addEdge(35, 59);
    g1.addEdge(36, 81);
    g1.addEdge(37, 13);
    g1.addEdge(38, 16);
    g1.addEdge(38, 51);
    g1.addEdge(39, 3);
    g1.addEdge(39, 61);
    g1.addEdge(40, 41);
    g1.addEdge(41, 18);
    g1.addEdge(42, 48);
    g1.addEdge(43, 20);
    g1.addEdge(44, 43);
    g1.addEdge(48, 96);
    g1.addEdge(51, 56);
    g1.addEdge(52, 12);
    g1.addEdge(52, 40);
    g1.addEdge(53, 0);
    g1.addEdge(55, 89);
    g1.addEdge(55, 35);
    g1.addEdge(56, 21);
    g1.addEdge(58, 67);
    g1.addEdge(59, 90);
    g1.addEdge(60, 79);
    g1.addEdge(60, 87);
    g1.addEdge(61, 59);
    g1.addEdge(65, 76);
    g1.addEdge(66, 3);
    g1.addEdge(67, 14);
    g1.addEdge(67, 32);
    g1.addEdge(69, 8);
    g1.addEdge(70, 11);
    g1.addEdge(70, 23);
    g1.addEdge(71, 30);
    g1.addEdge(72, 6);
    g1.addEdge(73, 88);
    g1.addEdge(74, 42);
    g1.addEdge(75, 63);
    g1.addEdge(75, 4);
    g1.addEdge(76, 66);
    g1.addEdge(78, 13);
    g1.addEdge(78, 7);
    g1.addEdge(81, 72);
    g1.addEdge(83, 17);
    g1.addEdge(83, 16);
    g1.addEdge(84, 64);
    g1.addEdge(84, 4);
    g1.addEdge(85, 84);
    g1.addEdge(85, 42);
    g1.addEdge(86, 25);
    g1.addEdge(87, 64);
    g1.addEdge(87, 78);
    g1.addEdge(88, 60);
    g1.addEdge(89, 22);
    g1.addEdge(90, 80);
    g1.addEdge(90, 66);
    g1.addEdge(91, 44);
    g1.addEdge(92, 36);
    g1.addEdge(93, 1);
    g1.addEdge(93, 5);
    g1.addEdge(94, 3);
    g1.addEdge(95, 8);
    g1.addEdge(95, 18);
    g1.addEdge(96, 92);
    g1.addEdge(97, 86);
    g1.addEdge(97, 35);
    cout << "Coloring of graph 1 \n";


    // g1.greedyColoring();
    //g1.hillClimbingAlgorithm(100);
   // g1.hillClimbingAlgorithmBestPoint(1);
    // g1.tabuSearch(3, 10);
    //g1.tabuSearchBack(100, 10);
    g1.simulatedAnnealing(1);
    // g1.geneticAlgorithm(1, 10, 0, 0);
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
