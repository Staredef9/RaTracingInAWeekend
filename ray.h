#ifndef RAY_H
#define RAY_H

#include "vec3.h"


class	ray{

	public:
		ray(){}
		
		ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction) {}
		//the type& alllows us to access to the value and change it as if it was passed by ref and not by value
		point3	origin() const {return orig;}
		vec3	direction() const{return dir;}

		point3	at(double t) const{
			return orig + t * dir;
		}

	private:
		point3	orig;
		vec3	dir;
};


#endif
