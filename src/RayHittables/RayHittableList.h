#pragma once
#include <RayHittables/RayHittableObject.h>
#include <vector>
#include <memory>
class RayHittableList : public RayHittableObject{

    private:
        std::vector<std::shared_ptr<RayHittableObject>> _objects;

    public:
        RayHittableList() {}
        RayHittableList(shared_ptr<RayHittableObject> object) { add(object); }
        void add(std::shared_ptr<RayHittableObject> newHittable){_objects.push_back(newHittable);}
        virtual bool hit(const Ray& currentRay, double t_min, double t_max, RayHitRecord& hitRecord) const override;


};