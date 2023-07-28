#include <iostream>
#include "../headers/Fake_Json_Value.h"

//
// Created by 30225 on 2023/7/27.
//
int (*fake_Json_Value_size)(Json::Value *);
const char * (*fake_Json_Value_asCString)(Json::Value *);
const char * (*fake_Json_Value_getMemberNames)(Json::Value *);//
Json::Value & (*fake_Json_Value_resolveReference)(Json::Value * ptr,const char* key,bool b);//
void (*base_Json_Value_Value)(Json::Value *,char const*, char const*);
std::string (*fake_Json_Value_toStyledString)(Json::Value * ptr);//
void NC_Json_Value_Value(Json::Value * ptr,char const* a, char const* b){
    base_Json_Value_Value(ptr,a,b);
}