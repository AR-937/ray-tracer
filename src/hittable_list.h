#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"

#include <memory>
#include <vector>

namespace raytracer {

class hittable_list : public hittable {
public:
    using object_ptr = std::shared_ptr<hittable>;
    std::vector<object_ptr> objects;

    hittable_list() noexcept = default;
    
    explicit hittable_list(object_ptr object) {
        add(std::move(object));
    }

    // Copy and move operations
    hittable_list(const hittable_list&) = default;
    hittable_list(hittable_list&&) noexcept = default;
    hittable_list& operator=(const hittable_list&) = default;
    hittable_list& operator=(hittable_list&&) noexcept = default;

    void clear() noexcept { 
        objects.clear(); 
    }

    void add(object_ptr object) {
        objects.push_back(std::move(object));
    }

    bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
        hit_record temp_rec;
        bool hit_anything = false;
        auto closest_so_far = ray_t.max;

        for (const auto& object : objects) {
            if (object->hit(r, interval(ray_t.min, closest_so_far), temp_rec)) {
                hit_anything = true;
                closest_so_far = temp_rec.t;
                rec = temp_rec;
            }
        }

        return hit_anything;
    }
};

} // namespace raytracer

#endif
