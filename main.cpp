#include <cstdlib>
#include <iostream>
#include <queue>
#include <stdexcept>
#include <unordered_set>
#include <vector>

//Edge struct
typedef struct {
    char vertex1;
    char vertex2;
    int cost;

} edge_t;

//Matrix class
class Graph {
private:
    //SHOULD we tract num edge? 
    int num_edge = 0;
    std::unordered_set<char> vertices_list;
    std::vector<edge_t> matrix;//What can we use here??? should we do an edge struct?

public:
    //Constructor
    Graph(){}

    //Destructor (optional)
    ~Graph(){}

    void insert_edge(char ver1, char ver2, int cost){
        edge_t new_edge;
        new_edge.vertex1 = ver1;
        new_edge.vertex2 = ver2;
        new_edge.cost = cost;

        matrix.push_back(new_edge);
        num_edge += 1;

        if (vertices_list.find(ver1) == vertices_list.end()) {
            vertices_list.insert(ver1);
        }

        if (vertices_list.find(ver2) == vertices_list.end()) {
            vertices_list.insert(ver2);
        }
    }

    void insert_adj_matrix (std::vector<std::vector<int>> adj_matrix) {
        for (int i = 0; i < adj_matrix.size(); i++) {
            for (int j = 0; j < adj_matrix.size(); j++) {
                if (adj_matrix[i][j] != 0) {
                    char ver1 = '0' + char(i);
                    char ver2 = '0' + char(j);
                    insert_edge(ver1, ver2, adj_matrix[i][j]);
                }
            }
        }
    }


    void display() {
        for (const edge_t & edge : matrix) {
            std::cout << "("<< edge.vertex1 << ","<< edge.vertex2 << ") : " << edge.cost << std::endl;
        }
        std::cout << "Number of edges: " << num_edge << std::endl;
        std::cout << "Vertices: [";
        for (const char & v : vertices_list) {
            std::cout << v << ",";
        }
        std::cout << "]" << std::endl;
        
    }

    std::unordered_map<std::vector<char>, int> Dijkstras (Graph graph, char s) {

        if (vertices_list.find(s) == vertices_list.end()) {
            throw std::runtime_error("source node doesn't exist in the graph");
        }

        typedef struct {
            int distance;
            bool known;
            char parent;
        } vertex_t;

        std::unordered_map<std::vector<char>, int> final;
        std::unordered_map<char, vertex_t> info_map;
        std::priority_queue<char> p_queue;

        for (const char & v : vertices_list) {
            vertex_t new_vertex;
            new_vertex.distance = 10000000;
            new_vertex.known = false;
            new_vertex.parent = '\0';

            info_map[v] = new_vertex;

        }
        
        
       return final; 
    }

};


int main () {

    Graph graph;

    graph.insert_edge('a', 'b', 1);
    graph.insert_edge('b', 'c', 2);
    graph.insert_edge('a', 'c', 4);
    graph.insert_edge('a', 'c', 5);

    graph.display();
    
    //Use adj matrix graph

    std::vector<std::vector<int>> adj_matrix;
    adj_matrix = {{0,1,0,0}, 
                  {1,0,0,1},
                  {1,0,0,1},
                  {0,0,0,0},
                };

    Graph graph2;

    graph2.insert_adj_matrix(adj_matrix);
    graph2.display();

    return 0;
}
