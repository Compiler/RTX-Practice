#pragma once

#include <RayHittables/Hittable.h>
#include <RayHittables/HittableList.h>
#include <maths/Ray.h>
#include <maths/AABB.h>
#include <maths/Vec3.h>
#include <algorithm>
class BVHNode : public Hittable{
    
    public:
        std::shared_ptr<Hittable> left;
        std::shared_ptr<Hittable> right;
        AABB boundBox;

    public:
        BVHNode();
        BVHNode(const HittableList& list, double time0, double time1);
        BVHNode(const std::vector<shared_ptr<Hittable>>& src_objects, size_t start, size_t end, double time0, double time1);
        virtual bool hit(const Ray& r, double tMin, double tMax, HitRecord& record) const ;
        virtual bool boundingBox(double time0, double time1, AABB& outputBox) const ;


};



inline bool boxCompare(const shared_ptr<Hittable> a, const shared_ptr<Hittable> b, int axis) {
    AABB box_a;
    AABB box_b;

    if (!a->boundingBox(0,0, box_a) || !b->boundingBox(0,0, box_b))
        std::cerr << "No bounding box in bvh_node constructor.\n";

    return box_a.min().e[axis] < box_b.min().e[axis];
}


inline bool boxAxisXCompare (const shared_ptr<Hittable> a, const shared_ptr<Hittable> b) {
    return boxCompare(a, b, 0);
}

inline bool boxAxisYCompare (const shared_ptr<Hittable> a, const shared_ptr<Hittable> b) {
    return boxCompare(a, b, 1);
}

inline bool boxAxisZCompare (const shared_ptr<Hittable> a, const shared_ptr<Hittable> b) {
    return boxCompare(a, b, 2);
}