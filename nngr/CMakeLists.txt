
include_directories(
    ${CMAKE_SOURCE_DIR}/nngr
)

set(NNGR_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/cell.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/island.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/nonogram.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ocean.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/orientation.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/pack.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/problem.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/solution.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/solver.cpp
)

add_library(nngr ${NNGR_SRC})
