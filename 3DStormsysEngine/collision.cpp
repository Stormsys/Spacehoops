#include "collision.h"

/* note to self:
to detect collsion for sphere-box first treat the sphere like a box.
if box-box collides, then do more accurate check.
*/
bool collision::collides(shape *s1, shape *s2)
{
	if(s1->type == AP_BOX && s2->type == AP_BOX)
	{
		return collides_box_box(s1, s2);
	}else if(s1->type == SPHERE && s2->type == SPHERE)
	{
		return collides_sphere_sphere(s1, s2);
	}else if((s1->type == SPHERE && s2->type == UR_TORUS) || (s2->type == SPHERE && s1->type == UR_TORUS))
	{
		if(s2->type == UR_TORUS)		
			return collides_sphere_torus(s1, s2);
		else	
			return collides_sphere_torus(s2, s1);
	}
	return false;
}
bool collision::collides_box_box(shape *s1, shape *s2)
{
	//s1
	float s1_x_min = s1->location->x;
	float s1_x_max = s1->location->x + s1->size->w;

	float s1_y_min = s1->location->y;
	float s1_y_max = s1->location->y + s1->size->h;

	float s1_z_min = s1->location->z;
	float s1_z_max = s1->location->z + s1->size->d;

	//s2
	float s2_x_min = s2->location->x;
	float s2_x_max = s2->location->x + s2->size->w;

	float s2_y_min = s2->location->y;
	float s2_y_max = s2->location->y + s2->size->h;

	float s2_z_min = s2->location->z;
	float s2_z_max = s2->location->z + s2->size->d;

	if( /*x*/s1_x_min <= s2_x_max && s1_x_max >= s1_x_min &&
		/*y*/s1_y_min <= s2_y_max && s1_y_max >= s1_y_min &&
		/*z*/s1_z_min <= s2_z_max && s1_z_max >= s1_z_min)
	{
		return true;
	}
	return false;
}
bool collision::collides_sphere_sphere(shape *s1, shape *s2)
{
	float d = pointDistance(s1->location, s2->location);
	if(s1->radius + s2->radius >= d)
	{
		return true;
	}
	return false;
}

bool collision::collides_sphere_sphere_edge(shape *s1, shape *s2)
{
	/*s1 colliding with the edge of spgere 2*/
	float d = pointDistance(s1->location, s2->location);
	if(s2->radius - s1->radius  <= d && s2->radius + s1->radius  >= d )
	{
		return true;
	}
	return false;
}
bool collision::collides_sphere_torus(shape *s1, shape *s2)
{
	float closest_distance = 0;
	for(int i = 0; i <= 360; i+=10)
	{
		point3d *C = spherePoint(s2->location, s2->radius, i, s2->roty + 90);
		float d = pointDistance(s1->location, C);
		if(i == 0 || closest_distance > d)
			closest_distance = d;
	}
	if(s1->radius + s2->csRadius >= closest_distance)
	{
		return true;
	}
	return false;
}
