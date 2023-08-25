//
// Created by 30225 on 2023/8/23.
//

#ifndef MCENGINE_FAKE_MATERIAL_HPP
#define MCENGINE_FAKE_MATERIAL_HPP
#include <map>

class Material
{

};
extern std::map<int,Material *> materialsPool;
//fake区
extern Material const& (*fake_Material_getMaterial)(int);
//_ZN8Material11getMaterialE12MaterialType(a1);
//hook区

extern void (*base_Material__setupSurfaceMaterials)(Material *);

extern void NC_Material__setupSurfaceMaterials(Material *);
//_ZN8Material22_setupSurfaceMaterialsEv
#endif //MCENGINE_FAKE_MATERIAL_HPP
