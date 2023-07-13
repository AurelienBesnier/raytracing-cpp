#ifndef HITTABLE_HPP
#define HITTABLE_HPP

#include "utils.hpp"

class material;

struct hit_record {
    point3 p;
    vec3 normal;
    float t;
    bool front_face;
    shared_ptr<material> mat_ptr;

    inline void set_face_normal(const ray& r, const vec3& outward_normal) {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal :-outward_normal;
    }
};

class hittable {
public:
    virtual bool hit (const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};

#endif // HITTABLE_HPP
