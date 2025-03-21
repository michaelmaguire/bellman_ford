#include <iostream>
using namespace std;

vector<int> bellmanFord(int number_of_nodes, vector<vector<int>>& edges, int src) {
    vector<int> dist(number_of_nodes, numeric_limits<int>::max());
    dist[src] = 0;

    // Bellman-Ford should complete in (number_of_node - 1) iterations.
    // If we can still relax edges in the number_of_node-th iteration, then there is a negative weight cycle.
    // Instead of running V-1 iterations, do one extra iteration and check for negative weight cycle.
    bool relaxation_took_place = true; // starting true to enter the loop
    for (int i = 0; ( i < number_of_nodes) && relaxation_took_place; i++) {
        relaxation_took_place = false;
        for (vector<int>& edge : edges) {
            int u = edge[0], v = edge[1], wt = edge[2];
            int new_dist_to_v = dist[u] + wt;
            if (dist[u] != numeric_limits<int>::max() && new_dist_to_v < dist[v]) {

                relaxation_took_place = true;

                if(i == number_of_nodes - 1) {
                    cout << "Negative weight cycle found!";
                    exit(-1);
                }                

                dist[v] = new_dist_to_v;
            }
        }

        if( ! relaxation_took_place) {
            cout << "No relaxation took place in iteration " << i << endl;
        }
    }

    return dist;
}



int main(int argc, char **argv)
{
    cout << "Hello World bellman-ford" << endl;


    const int number_of_nodes = 6;

    // Each triplet { start node, end node, weight }
    vector<vector<int>> edges = {{0, 1, 10}, {0, 5, 8}, {1, 3, 2}, 
                                 {2, 1, 1}, {3, 2, -2}, {4, 1, -4}, 
                                 {4, 3, -1}, {5, 4, 1} };

    int src = 0;
    vector<int> ans = bellmanFord(number_of_nodes, edges, src);
    for (int dist : ans) 
        cout << dist << " ";
    return 0;    
}