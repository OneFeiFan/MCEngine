//
// Created by 30225 on 2023/8/31.
//

#include "../headers/Other.hpp"
    bool cmp_str::operator()(char const *a, char const *b) const
    {
        return std::strcmp(a, b) < 0;
    }
//uintptr_t *(*fake_setBlockDisplayName)(uintptr_t*,std::string const&);