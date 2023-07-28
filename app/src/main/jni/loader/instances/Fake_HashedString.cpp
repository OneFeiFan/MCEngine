//
// Created by 30225 on 2023/7/26.
//
#include "../headers/Fake_HashedString.h"

//fake区
void (*fake_HashedString_HashedString)(HashedString *, char *const);

const char *(*fake_HashedString_c_str)(HashedString *);