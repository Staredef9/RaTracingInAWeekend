#ifndef HITTABLE_H
#define HITTABLE_H


#include "ray.h"
#include "rtweekend.h"


class	material;

class	hit_record{

	public: 
		point3	p;
		vec3	normal;
		double	t;
		bool	front_face;
		shared_ptr<material> mat;
		void	set_face_normal(const ray& r, const vec3& outward_normal){
		//SETS the hit record normal vector
		//the parameter ouward_normal is assumed to have unit length
		front_face = dot(r.direction(), outward_normal) < 0;
		normal = front_face ? outward_normal : -outward_normal;
		}
};

//the virtual keyword allows the compiler to understand 
//which is the correct function I am trying to call from a possibly derived class from hittable 
//in c++ 11 you also get the override keyword that helps clarity


//the = 0 at the end of a virtual function definition
//makes this a pure virtual function, and the class becomes an abstract class. 
//meaning that each derived class MUST redefine the content of the function 
//
//
//BLUEPRINT for an hittable object
//you can't use this abstract class directly, 
//you must use it a derived class from this. 
//
//
class	hittable{
	public:
		virtual	~hittable() = default;

		virtual	bool	hit(const ray& r, interval ray_t, hit_record& rec) const = 0;
};

#endif

