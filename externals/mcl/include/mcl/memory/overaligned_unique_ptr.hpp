// This file is part of the mcl project.
// Copyright (c) 2022 merryhime
// SPDX-License-Identifier: MIT

#pragma once

#include <cstdlib>
#include <type_traits>

namespace mcl {

namespace detail {
struct std_free_deleter {
    template<typename T>
    void operator()(T *p) const
    {
        std::free(const_cast<std::remove_const_t<T>*>(p));
    }
};
}  // namespace detail

template<size_t, typename T>
using overaligned_unique_ptr = std::unique_ptr<T, detail::std_free_deleter>;

template<size_t alignment, typename T>
auto make_overaligned_unique_ptr_array(size_t element_count)
{
    const size_t min_size = element_count * sizeof(T);
    const size_t alloc_size = (min_size + alignment - 1) / alignment * alignment;
    return overaligned_unique_ptr<alignment, T[]>{static_cast<T*>(std::aligned_alloc(alignment, alloc_size))};
}

}  // namespace mcl
