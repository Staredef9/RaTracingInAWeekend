#include "rtweekend.h"
#include "camera.h"
#include "color.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"
//MATH TO UNDERSTAND IF A VECTOR STARTING FROM POSITION x (our RAYS) does in fact intersect with the SPHERE
//AND HOW MANY TIMES, iF 0 we paint the color that is behind the SPHERE
//					  if 1 we paint a certain color that is FRONT of camera
//					  if 2 we paint a certain two colors, one for front of camera one for the back
//					  ACCORDINGLY to the position of the light 
/*
double	hit_sphere(const point3& center, double radius, const ray& r){
			vec3	oc = r.origin() - center;
			auto	a =	r.direction().lenght_squared();
			auto	half_b = dot(oc, r.direction());
			auto	c = oc.lenght_squared() - radius*radius;
			auto	discriminant = half_b*half_b - a*c;

			if (discriminant < 0){
				return (-1.0);
			} else {
				return(-half_b - sqrt(discriminant)) / a; //quadratic function 
			}
		//	return	(discriminant >= 0);
}*/
/*
color	ray_color(const	ray& r, const	hittable& world){

	hit_record rec;
	if(world.hit(r,  interval(0, infinity), rec)){
		return 0.5 * (rec.normal + color(1,1,1));
	}
	*auto t = (hit_sphere(point3(0,0,-1),0.5, r ));
		//return color(1, 0, 0);
	if (t > 0.0){
		vec3	N = unit_vector(r.at(t) - vec3(0,0,-1));
		return(0.5 * color(N.x()+1, N.y()+1, N.z()+1));
	}*/
/*
	vec3	unit_direction = unit_vector(r.direction());
	auto	a = 0.5*(unit_direction.y() + 1.0);
	return	(1.0-a)*color(1.0,1.0,1.0) + a*color(0.5,0.7,1.0);
//	return color(0,0,0);
}*/


int main()
{
	hittable_list world;
	
	/*
	auto	R = cos(pi/4);

	auto	material_left = make_shared<lambertian>(color(0,0,1));
	auto	material_right = make_shared<lambertian>(color(1,0,0));

	world.add(make_shared<sphere>(point3(-R, 0, -1), R, material_left));
	world.add(make_shared<sphere>(point3(R, 0, -1), R, material_right));
*/


	/*auto	material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
	auto	material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
	auto	material_left	= make_shared<dielectric>(1.5);
	auto	material_right	= make_shared<metal>(color(0.8, 0.6, 0.2), 0.0);



	world.add(make_shared<sphere>(point3(0.0, -100.5,-1.0), 100.0, material_ground));
	world.add(make_shared<sphere>(point3(0.0, 0.0, -1.0), 0.5, material_center));
	world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
	world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), -4, material_left));
	world.add(make_shared<sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right));
*/

	auto	ground_material = make_shared<lambertian>(color(0.5, 0.5,0.5));
	world.add(make_shared<sphere>(point3(0,-1000,0), 1000, ground_material));

	for (int a = -11; a < 11; a++){
		for(int b = -11; b < 11; b++){

			auto choose_mat = random_double();
			point3	center(a + 0.9 * random_double(), 0.2,b + 0.9 * random_double());
			if ((center - point3(4, 0.2, 0)).lenght() > 0.9){
				shared_ptr<material> sphere_material;

				if (choose_mat < 0.8) {
					auto albedo = color::random() * color:: random();
					sphere_material = make_shared<lambertian>(albedo);
					world.add(make_shared<sphere>(center, 0.2, sphere_material));
				} else if (choose_mat < 0.95){
					
					auto albedo = color::random(0.5, 1);
					auto fuzz = random_double(0, 0.5);
					sphere_material = make_shared<metal>(albedo, fuzz);
					world.add(make_shared<sphere>(center, 0.2, sphere_material));
				} else {
						sphere_material = make_shared<dielectric>(1.5);
						world.add(make_shared<sphere>(center, 0.2, sphere_material));
				}
			}
		}
	}

	auto material1 = make_shared<dielectric>(1.5);
	world.add(make_shared<sphere>(point3(0,1,0), 1.0, material1));

	auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
	world.add(make_shared<sphere>(point3(-4,1,0), 1.0, material2));

	auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
	world.add(make_shared<sphere>(point3(4,1,0), 1.0, material3));


	camera	cam;

	cam.aspect_ratio = 16.0/9.0;
	cam.image_width = 1200;
	cam.samples_per_pixel = 50;
	cam.max_depth = 50;

	cam.vfov = 20;
	cam.lookfrom	= point3(13, 2, 3);
	cam.lookat		= point3(0,0,0);
	cam.vup			= vec3(0,1,0);

	cam.defocus_angle = 0.6;
	cam.focus_dist = 10;

	cam.render(world);

}
