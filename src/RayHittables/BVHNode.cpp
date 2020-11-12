#include "BVHNode.h"


BVHNode::BVHNode(){


}

BVHNode::BVHNode(const HittableList& list, double time0, double time1): BVHNode(list.objects, 0, list.objects.size(), time0, time1){
    

}

BVHNode::BVHNode(const std::vector<shared_ptr<Hittable>>& src_objects, size_t start, size_t end, double time0, double time1){
    std::vector<std::shared_ptr<Hittable>> objects = src_objects;
    int axis = (int)random_double(0, 2);
    bool (*comparator)(std::shared_ptr<Hittable> a, std::shared_ptr<Hittable> b) = axis==0 ? boxAxisXCompare : axis==1 ? boxAxisYCompare : boxAxisZCompare;


     size_t object_span = end - start;

    if (object_span == 1) {
        left = right = objects[start];
    } else if (object_span == 2) {
        if (comparator(objects[start], objects[start+1])) {
            left = objects[start];
            right = objects[start+1];
        } else {
            left = objects[start+1];
            right = objects[start];
        }
    } else {
        std::sort(objects.begin() + start, objects.begin() + end, comparator);

        auto mid = start + object_span/2;
        left = make_shared<BVHNode>(objects, start, mid, time0, time1);
        right = make_shared<BVHNode>(objects, mid, end, time0, time1);
    }

    AABB box_left, box_right;

    if (!left->boundingBox(time0, time1, box_left)|| !right->boundingBox(time0, time1, box_right)) std::cerr << "No bounding box in bvh_node constructor.\n";

    boundBox = surrounding_box(box_left, box_right);
}

bool BVHNode::hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const {
    if (!boundBox.hit(ray, tMin, tMax))
        return false;

    bool hit_left = left->hit(ray, tMin, tMax, record);
    bool hit_right = right->hit(ray, tMin, hit_left ? record.t : tMax, record);

    return hit_left || hit_right;

}

bool BVHNode::boundingBox(double time0, double time1, AABB& outputBox) const {
    outputBox = boundBox;
    return true;
}
