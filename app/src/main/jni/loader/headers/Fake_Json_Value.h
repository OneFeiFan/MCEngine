//
// Created by 30225 on 2023/7/27.
//

#ifndef MCENGINE_FAKE_JSON_VALUE_H
#define MCENGINE_FAKE_JSON_VALUE_H

//namespace Json {
//    class Value {
//    public:
//        //Methods
////        Value(char const*, char const*);
////        Value(Json::ValueType);
////        Value(Json::StaticString const&);
////        Value(Json::Value const&);
////        Value(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> > const&);
////        Value(char const*);
////        Value(bool);
////        Value(double);
////        Value(int);
////        Value(unsigned int);
////        Value(long long);
////        Value(unsigned long long);
////        ~Value();
////        void isArray() const;
////        void clear();
////        void isConvertibleTo(Json::ValueType) const;
////
////        void isNull() const;
////        void operator[](int);
////        void operator[](unsigned int);
////        void resolveReference(char const*, bool);
////        void operator>=(Json::Value const&) const;
////        void get(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> > const&, Json::Value const&) const;
////        void asBool(bool) const;
////
////
////        void isValidIndex(unsigned int) const;
////        void append(Json::Value const&);
////        void operator!=(Json::Value const&) const;
////        void operator!() const;
////        void empty() const;
////        void operator<=(Json::Value const&) const;
////        void get(unsigned int, Json::Value const&) const;
////        void swap(Json::Value&);
////        void getComment(Json::CommentPlacement) const;
////        void hasComment(Json::CommentPlacement) const;
////        void isUInt() const;
////        void resize(unsigned int);
////        void asInt64(long long) const;
////        void operator>(Json::Value const&) const;
////        void asLargestUInt() const;
////        void type() const;
////        void removeMember(char const*);
////        void isString() const;
////        void asDouble(double) const;
////        void setComment(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> > const&, Json::CommentPlacement);
////        void asInt(int) const;
////        void isObject() const;
////        void operator[](int) const;
////        void operator[](unsigned int) const;
////        void operator[](std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> > const&) const;
////        void isDouble() const;
////        void operator[](char const*);
////        void asFloat(float) const;
////        void toStyledString() const;
////        void begin();
////        void asLargestInt() const;
////        void operator[](std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> > const&);
////        void isIntegral() const;
////        void isNumeric() const;
////        void setComment(char const*, Json::CommentPlacement);
////        void operator==(Json::Value const&) const;
////        void operator<(Json::Value const&) const;
////        void asUInt(unsigned int) const;
////        void compare(Json::Value const&) const;
////        void asUInt64(unsigned long long) const;
////        void end();
////        void asString(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> > const&) const;
////        void get(char const*, Json::Value const&) const;
////        void isMember(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> > const&) const;
////        void operator[](Json::StaticString const&);
////        void isBool() const;
////        void removeMember(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> > const&);
////        void isInt() const;
////        void operator[](char const*) const;
////        void end() const;
////        void isMember(char const*) const;
////        void operator=(Json::Value const&);
////        void begin() const;
//    public:
//        //Objects
//        static Json::Value * minLargestInt;
//        static Json::Value * maxUInt;
//        static Json::Value * maxLargestUInt;
//        static Json::Value * maxUInt64;
//        static Json::Value * maxLargestInt;
//        static Json::Value * maxInt64;
//        static Json::Value * maxInt;
//        static Json::Value * minInt;
//        static Json::Value * minInt64;
//        static Json::Value * null;
//    };//Value
//}//Json
#include "../includes/lib_json/json/json.h"
//fake区
extern int (*fake_Json_Value_size)(Json::Value *);
extern const char * (*fake_Json_Value_asCString)(Json::Value *);//把值为string的结果转换为const char*
extern std::vector<std::string> (*fake_Json_Value_getMemberNames)(Json::Value *);//
extern Json::Value & (*fake_Json_Value_resolveReference)(Json::Value * ptr,const char* key,bool b);//
extern std::string (*fake_Json_Value_toStyledString)(Json::Value * ptr);//
extern std::string (*fake_Json_Value_toStyledString)(Json::Value * ptr);//
extern bool (*fake_Json_Reader_parse)(Json::Reader *, const char *, const char *, Json::Value *, bool);//
extern void (*fake_Json_Reader_Reader)(Json::Reader *);
extern void (*fake_Json_Value_Value)(Json::Value *,int);
extern Json::Value& (*fake_Json_Value_append)(Json::Value *,Json::Value const&);


//_ZN4Json5Value6appendERKS0_
extern void (*base_Json_Value_Value)(Json::Value *,char const*, char const*);//无用

extern void NC_Json_Value_Value(Json::Value * ptr,char const* a, char const* b);


#endif //MCENGINE_FAKE_JSON_VALUE_H
