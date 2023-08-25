//
// Created by 30225 on 2023/8/23.
//

#include <iostream>
#include "../headers/Fake_BlockTypeRegistry.hpp"
BlockLegacy *(*fake_BlockTypeRegistry_registerBlock)(std::string const&,int *,Material const&);

//hook区
BlockLegacy * (*base_BlockTypeRegistry_registerBlock)(std::string const&,int *,Material const&);
BlockLegacy * NC_BlockTypeRegistry_registerBlock(std::string const& str,int * a,Material const& b){
    std::cout<<str<<std::endl;
    return base_BlockTypeRegistry_registerBlock(str,a,b);
}