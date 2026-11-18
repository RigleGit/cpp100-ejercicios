#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

int main() {
    std::unordered_map<std::string, int> votos;
    int total = 0;
    std::string candidato;
    while (std::cin >> candidato) {
        ++votos[candidato];
        ++total;
    }

    std::vector<std::pair<std::string, int>> ranking(votos.begin(),
                                                     votos.end());
    std::sort(ranking.begin(), ranking.end(),
              [](const auto& a, const auto& b) {
                  if (a.second != b.second) {
                      return a.second > b.second;
                  }
                  return a.first < b.first;
              });

    std::cout << "Votos: " << total << '\n';
    std::cout << "Candidatos: " << ranking.size() << '\n';
    for (const auto& [nombre, cuantos] : ranking) {
        std::cout << nombre << ": " << cuantos << '\n';
    }
}
