#include "HittableList.h"


HittableList::HittableList(){

}

HittableList::HittableList(shared_ptr<Hittable> object){
    add(object);
}


void HittableList::clear(){
    objects.clear(); 
}

void HittableList::add(shared_ptr<Hittable> object){
    objects.push_back(object);
}

bool HittableList::hit(const Ray& r, double tMin, double tMax, HitRecord& record) const{
    HitRecord tempRec;
    bool hit_anything = false;
    auto closest_so_far = tMax;

    for (const auto& object : objects) {
        if (object->hit(r, tMin, closest_so_far, tempRec)) {
            hit_anything = true;
            closest_so_far = tempRec.t;
            record = tempRec;
        }
    }

    return hit_anything;
}
