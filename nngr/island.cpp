
#include "island.hpp"

#include <cassert>

namespace nngr {

    island_t::island_t(size_t left, size_t right, orientation_t orientation)
    : m_left{left}
    , m_right{right}
    , m_orientation{orientation}
    {
    }

    size_t const& island_t::left() const {
        return m_left;
    }

    size_t const& island_t::right() const {
        return m_right;
    }

    orientation_t const& island_t::orientation() const {
        return m_orientation;
    }

    std::pair<island_t, island_t> island_t::split(size_t where) const {
        assert(m_left < where && where < m_right);

        return { { m_left, where, m_orientation }, { where, m_right, m_orientation } };
    }

    size_t island_t::get_length() const {
        assert(m_left <= m_right);

        return m_right - m_left;
    }

}; // namespace nngr