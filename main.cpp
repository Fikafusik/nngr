
#include <nlohmann/json.hpp>
#include <iostream>
#include <string>

#include "nngr/nonogram.hpp"

int main() {
    using json = nngr::json;

    json problem_json = "{\"id\": 42, \"verticals\": [[8], [7], [7], [8], [11], [1, 8], [6], [7], [7], [4, 9], [17], [14], [14], [17], [4, 9], [7], [7], [6], [1, 8], [11], [8], [7], [7], [8]], \"horizontals\": [[1, 1], [2, 2], [2, 2], [2, 6, 2], [2, 4, 2], [4, 4, 4], [7, 4, 7], [22], [24], [24], [24], [24], [2, 2, 10, 2, 2], [1, 1, 8, 1, 1], [1, 6, 1], [1, 6, 1], [4], [1, 1]]}"_json;

    nngr::problem_t problem = problem_json.get<nngr::problem_t>();

    for (const auto& vertical : problem.horizontals) {
        for (const auto& value : vertical) {
            std::cout << value << '\t';
        }
        std::cout << std::endl;
    }

    nngr::solver_t solver{problem};
    
    nngr::solution_t solution{3, 5};
    solution[0][0] = nngr::cell_t::box;
    solution[2][4] = nngr::cell_t::space;
    solution[1][1] = nngr::cell_t::space;

    std::cout << solution << std::endl;

    return 0;
}