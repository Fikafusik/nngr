#pragma once

// Third-Party Includes
#include <nlohmann/json.hpp>

// Standard Includes:
#include <algorithm>
#include <cassert>
#include <vector>

// Local Includes:
#include "orientation.hpp"
#include "problem.hpp"
#include "solution.hpp"
#include "solver.hpp"

namespace nngr {

    enum class direction_t : uint8_t {
        before, after
    };
    
}; // namespace nngr
