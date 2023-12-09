#include <iostream>
#include <vector>
#include <iterator>
#include <numeric>
#include "edmonds_optimum_branching.hpp"
#include "edmonds_optimum_branching_impl.hpp"
#include <boost/graph/adjacency_list.hpp>

// Supondo que você esteja usando a biblioteca Boost Graph para representar seu grafo
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
                              boost::no_property, boost::property<boost::edge_weight_t, int>> Graph;
typedef boost::graph_traits<Graph>::edge_descriptor Edge;
typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;

int main() {
    // Exemplo de criação do grafo com 4 vértices
    Graph g(4);

    // Adicionando arestas ao grafo com pesos
    add_edge(0, 1, 1, g);
    add_edge(0, 2, 2, g);
    add_edge(1, 2, 3, g);
    add_edge(2, 3, 4, g);
    add_edge(3, 1, 5, g);

    // Mapas de índice e peso
    auto index_map = get(boost::vertex_index, g);
    auto weight_map = get(boost::edge_weight, g);

    std::cout << "Número de vértices: " << num_vertices(g) << std::endl;
    std::cout << "Número de arestas: " << num_edges(g) << std::endl;

    // Iteradores para os vértices raízes (aqui supomos todos os vértices como raízes potenciais)
    std::vector<Vertex> roots(num_vertices(g));
    std::iota(roots.begin(), roots.end(), 0); // Preenchendo com 0, 1, 2, ..., n-1

    std::cout << "Número de raízes: " << roots.size() << std::endl;

    // Vetor para armazenar a arborescência mínima resultante
    std::vector<Edge> minimumArborescence;

    // Chamada da função
    edmonds_optimum_branching<false, false, false>(g, index_map, weight_map, roots.begin(), roots.end(), std::back_inserter(minimumArborescence));

    std::cout << "Número de arestas da arborescência mínima: " << minimumArborescence.size() << std::endl;

    // Imprimir os resultados
    for (const auto& edge : minimumArborescence) {
        std::cout << "Aresta: " << source(edge, g) << " -> " << target(edge, g) << std::endl;
    }

    return 0;
}
