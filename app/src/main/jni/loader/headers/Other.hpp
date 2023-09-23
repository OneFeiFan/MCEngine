//
// Created by 30225 on 2023/8/31.
//

#ifndef MCENGINE_OTHER_HPP
#define MCENGINE_OTHER_HPP

#include <cstdint>
#include <string>
struct cmp_str
{
    bool operator()(char const *, char const *) const;
};
//fake
//extern uintptr_t *(*fake_setBlockDisplayName)(uintptr_t*,std::string const&);
//_ZN6Social11UserProfile14setDisplayNameERKNSt6__ndk112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE_0


#endif //MCENGINE_OTHER_HPP
