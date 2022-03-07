#pragma once

#include <cstddef>
#include <utility>

#include "orientation.hpp"

namespace nngr {

    class island_t {
    public:
        island_t(size_t left, size_t right, orientation_t orientation);

        size_t const& left() const;
        size_t const& right() const;
        orientation_t const& orientation() const;

        std::pair<island_t, island_t> split(size_t where) const;

        size_t get_length() const;

    private:
        size_t m_left;
        size_t m_right;
        orientation_t m_orientation;
    };

}; // namespace nngr;