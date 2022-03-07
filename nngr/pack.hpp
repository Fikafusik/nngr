#pragma once

#include <nlohmann/json.hpp>

#include "problem.hpp"
#include "type.hpp"

namespace nngr {

    using problems_t = std::vector<problem_t>;

    struct pack_t {
        size_t id;
        type_t type;
        problems_t problems;
    };
    
    using json = nlohmann::json;

    void to_json(json& j, const pack_t& pack);
    void from_json(const json& j, pack_t& pack);

};
