#pragma once
#include <RayHittables/Hittable.h>
#include <Core.h>
#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

class HittableList : public Hittable{

    public:
        std::vector<shared_ptr<Hittable>> objects;

    public:
        HittableList();
        HittableList(shared_ptr<Hittable> object);

        void clear();
        void add(shared_ptr<Hittable> object);
        virtual bool hit(const Ray& r, double tMin, double tMax, HitRecord& record) const;


};