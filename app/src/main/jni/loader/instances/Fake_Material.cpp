//
// Created by 30225 on 2023/8/23.
//

#include "../headers/Fake_Material.hpp"

std::map<const char*,Material *,cmp_str> materialsPool;
//fake区
Material const& (*fake_Material_getMaterial)(int);

//hook区
void (*base_Material__setupSurfaceMaterials)(Material *);

void NC_Material__setupSurfaceMaterials(Material * ptr){
    base_Material__setupSurfaceMaterials(ptr);
    materialsPool["Dirt"] = (Material *)&fake_Material_getMaterial(1);//泥制方块
    materialsPool["Wood"] = (Material *)&fake_Material_getMaterial(2);//木制方块
    materialsPool["Stone"] = (Material *)&fake_Material_getMaterial(3);//石制方块
}
