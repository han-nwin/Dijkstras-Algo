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
                    char ver1 = '0' + i;
                    char ver2 = '0' + j;
                    insert_edge(ver1, ver2, adj_matrix[i][j]);
                }
            }
        }
    }

    //display
    void display() {
        std::cout << "Number of edges: " << num_edge << std::endl;
        for (const edge_t & edge : matrix) {
            std::cout << "("<< edge.vertex1 << ","<< edge.vertex2 << ") : " << edge.cost << std::endl;
        }
        std::cout << "Vertices: [";
        for (const char & v : vertices_list) {
            std::cout << v << ",";
        }
        std::cout << "]" << std::endl;

        
    }

    //Function to return neighbor and assocciated cost
    std::vector<std::pair<char, int>> neighbors(char v) {
        std::vector<std::pair<char, int>> neighbor_list;
        for (const auto & e : matrix) {
            if (e.vertex1 == v) {
                neighbor_list.push_back(std::pair(e.vertex2, e.cost));
            }
        }
        return neighbor_list;
    }

    //Dijkstras
    std::unordered_map<char, std::pair<char,int>> Dijkstras(char s) {

        if (vertices_list.find(s) == vertices_list.end()) {
            throw std::runtime_error("source node doesn't exist in the graph");
        }

        typedef struct {
            int distance;
            bool known;
            char parent;
        } vertex_t;

        std::unordered_map<char, std::pair<char,int>> final;
        std::unordered_map<char, vertex_t> info_map;
        auto cmp = [](std::pair<int,char> left, std::pair<int,char> right) {
            return left.first > right.first;
        };
        std::priority_queue<std::pair<int,char>, std::vector<std::pair<int,char>>, decltype(cmp)> p_queue(cmp);

        for (const char & v : vertices_list) {
            vertex_t new_vertex;
            new_vertex.distance = 99999999;
            new_vertex.known = false;
            new_vertex.parent = '$';

            info_map[v] = new_vertex;
        }
        
        info_map[s].distance = 0;
        p_queue.emplace(0, s);
        
        while (!p_queue.empty()) {
            //Get an element from the queue
            char v = p_queue.top().second;
            p_queue.pop();

            if (!info_map[v].known) {
                info_map[v].known = true;
                std::vector<std::pair<char, int>> neighbor_list = neighbors(v);

                //For all neighbor of w of v??
                for (const auto & pair : neighbor_list) {
                    if (!info_map[pair.first].known && info_map[pair.first].distance > (info_map[v].distance + pair.second)) {
                        info_map[pair.first].distance = info_map[v].distance + pair.second;
                        info_map[pair.first].parent = v;
                        p_queue.emplace(info_map[pair.first].distance, pair.first);
                    }
                }
            }

        }

        //Insert all into the final
        for (const char & v : vertices_list) {
            final[v] = std::pair(info_map[v].parent, info_map[v].distance);
        }
        
       return final; 
    }

};


int main () {
    //Use adj matrix graph
    std::vector<std::vector<int>> adj_matrix;
    adj_matrix = {{0, 2, 0, 1, 0, 0, 0}, 
                  {0, 0, 0, 2, 10, 0, 0},
                  {4, 0, 0, 0, 0, 5, 0},
                  {0, 0, 2, 0, 2, 8, 4},
                  {0, 0, 0, 0, 0, 0, 6},
                  {0, 0, 0, 0, 0, 0, 0},
                  {0, 0, 0, 0, 0, 1, 0},
                };

    Graph graph;

    graph.insert_adj_matrix(adj_matrix);
    graph.display();

    //Run dijkstras from vertex '0'
    std::unordered_map<char, std::pair<char, int>> dijkstras = graph.Dijkstras('0');
    
    std::cout << "vertex |" <<" distance |" << " parent" << std::endl;
    for (const auto & ele : dijkstras) {
        std::cout << ele.first << " | " << ele.second.second << " | " << ele.second.first << std::endl;
    }
    return 0;
}
