#ifndef EX_FAKE_ITEMSTACKBASE_HPP
#define EX_FAKE_ITEMSTACKBASE_HPP

#include <dlfcn.h>
#include "HashedStringFaker.hpp"
#include "./includes/tools/gsl/gsl"
#include "ActorFaker.hpp"
#include "BlockSourceFaker.hpp"
#include "./includes/tools/lib_json/json/json.h"

//ItemStackBase

static short (*fake_ItemStackBase_getId)(ItemStackBase *);
#endif