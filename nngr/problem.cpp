
#include "problem.hpp"

namespace nngr {

    void to_json(json& j, const problem_t& nonogram) {
        j = json{
            { "id", nonogram.id },
            { "verticals", nonogram.verticals },
            { "horizontals", nonogram.horizontals }
        };
    }

    void from_json(const json& j, problem_t& nonogram) {
        j.at("id").get_to(nonogram.id);
        j.at("verticals").get_to(nonogram.verticals);
        j.at("horizontals").get_to(nonogram.horizontals);
    }

};