#pragma once

#include <nlohmann/json.hpp>

namespace nngr {

    struct problem_t {
        using value_type = std::vector<std::vector<size_t>>;

        size_t id;
        value_type verticals;
        value_type horizontals;
    };

    using json = nlohmann::json;

    void to_json(json& j, const problem_t& problem);
    void from_json(const json& j, problem_t& problem);
};