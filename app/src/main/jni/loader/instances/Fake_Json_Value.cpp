#include <iostream>
#include "../headers/Fake_Json_Value.h"

//
// Created by 30225 on 2023/7/27.
//fake区
int (*fake_Json_Value_size)(Json::Value *);

const char *(*fake_Json_Value_asCString)(Json::Value *);

const char *(*fake_Json_Value_getMemberNames)(Json::Value *);//
Json::Value &(*fake_Json_Value_resolveReference)(Json::Value *ptr, const char *key, bool b);//
std::string (*fake_Json_Value_toStyledString)(Json::Value *ptr);//

bool (*fake_Json_Reader_parse)(Json::Reader *, const char *, const char *, Json::Value *, bool);

void (*fake_Json_Reader_Reader)(Json::Reader *);

void (*fake_Json_Value_Value)(Json::Value *,int);
//hook区
void (*base_Json_Value_Value)(Json::Value *, char const *, char const *);

void NC_Json_Value_Value(Json::Value *ptr, char const *a, char const *b)
{
    base_Json_Value_Value(ptr, a, b);
}