#include <iostream>
#include <vector>


//How to represent a graph? -> adjacency matrix (yes) we can add a cost assocciated using matrix
//DAMN I just realized it's directed graph so ab != ba smh
//How to construct a vetices pair?
// --> std::pair? struct?
//How to add weighted cost?
//The algo? We must be given a source node
//Test cases
//

typedef struct {
  char vertex1;
  char vertex2;
  int cost;
  
} edge_t;

class Graph {
  private:
    //SHOULD we tract num edge? 
  int num_edge = 0;
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
  }

  void display() {
    for (const edge_t & edge : matrix) {
      std::cout << edge.vertex1 << edge.vertex2 << ": " << edge.cost << std::endl;
    }
    std::cout << "Number of edges: " << num_edge << std::endl;
  }

};

int main () {

  Graph graph;
  graph.insert_edge('a', 'b', 1);
  graph.insert_edge('b', 'c', 2);
  graph.insert_edge('a', 'c', 4);
  graph.insert_edge('a', 'c', 5);
  //DO we allow multiple edges for 2 vertices?
  //



  graph.display();
  return 0;
}
