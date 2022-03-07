#pragma once

#include <cstddef>
#include <vector>

#include "island.hpp"
#include "problem.hpp"

namespace nngr {

    class ocean_t {
    public:
        using value_type = std::vector<std::vector<size_t>>;

        ocean_t(size_t horizontals, size_t verticals);
        ocean_t(problem_t problem);

        value_type const& operator[](size_t index) const;
        value_type& operator[](size_t index);

        size_t const& horizontals() const;
        size_t const& verticals() const;
        
        void add(island_t island);

    private:
        size_t m_horizontals;
        size_t m_verticals;
        std::vector<value_type> m_ocean;
    };

}; // namespace nngr;