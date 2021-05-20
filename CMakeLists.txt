cmake_minimum_required(VERSION 3.19)
project(current)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I . -fsanitize=address -g -O0 -Wfatal-errors -Wall -Wextra -pedantic -Wshadow -Wformat=2 -Wfloat-equal -Wconversion -Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Wcast-qual -Wcast-align -Wno-unused-result -Wno-sign-conversion -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all -fstack-protector -D_FORTIFY_SOURCE=2 -fvisibility=hidden")

add_library(current
        atcoder/convolution.hpp
        atcoder/fenwicktree.hpp
        atcoder/internal_bit.hpp
        atcoder/internal_csr.hpp
        atcoder/internal_math.hpp
        atcoder/internal_queue.hpp
        atcoder/internal_scc.hpp
        atcoder/internal_type_traits.hpp
        atcoder/lazysegtree.hpp
        atcoder/math.hpp
        atcoder/maxflow.hpp
        atcoder/mincostflow.hpp
        atcoder/modint.hpp
        atcoder/scc.hpp
        atcoder/segtree.hpp
        atcoder/string.hpp
        atcoder/twosat.hpp

        atcoder/convolution
        atcoder/fenwicktree
        atcoder/internal_bit
        atcoder/internal_csr
        atcoder/internal_math
        atcoder/internal_queue
        atcoder/internal_scc
        atcoder/internal_type_traits
        atcoder/lazysegtree
        atcoder/math
        atcoder/maxflow
        atcoder/mincostflow
        atcoder/modint
        atcoder/scc
        atcoder/segtree
        atcoder/string
        atcoder/twosat

        # me
        atcoder/combinatorics.hpp
        atcoder/dag.hpp
        atcoder/link_cut_splay.hpp
        atcoder/matrix_exp.hpp
        atcoder/prime_sieve.hpp
        atcoder/sparse_table.hpp
        atcoder/tree.hpp
        atcoder/y_combinator.hpp
        )


add_executable(a a.cpp)
add_executable(b b.cpp)
add_executable(c c.cpp)
add_executable(d d.cpp)
add_executable(e e.cpp)
add_executable(f f.cpp)
add_executable(gen testing/gen.cpp)

set_target_properties(current PROPERTIES LINKER_LANGUAGE CXX)
