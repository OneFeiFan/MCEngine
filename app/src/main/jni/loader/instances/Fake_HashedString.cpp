//
// Created by 30225 on 2023/7/26.
//
#include "../headers/Fake_HashedString.h"

//fake区
HashedString * (*fake_HashedString_HashedString)(char *const);

const char *(*fake_HashedString_c_str)(HashedString *);
std::string (*fake_HashedString_getString)(HashedString *);