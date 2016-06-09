#ifndef OBJLOADER_H
#define OBJLOADER_H
#include "shared/gltools.h"
#include "geometry.h"
#include <vector>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

using namespace std;
struct obj_face_data
{
	int vertex;
	int normal;
	int texture;
};
struct obj_face
{
	vector<obj_face_data *> face_data;	
	int vertex_count;
	int material_index;
};
struct mtl_data
{
	char name[50];
	point3d *Ka;
	point3d *Kd;
	point3d *Ks;
	float i;
	float d;
	float s;
};

class ObjModel
{
public:
	vector<obj_face *> faceList;
	vector<point3d *> vertexList;
	vector<point3d *> normalList;
	vector<point3d *> textureList;
	vector<mtl_data *> materialList;

	int nFace;

	int getMtlIndex(char *name);
	ObjModel(char* filename);
	void loadMtl(char* filename);
	void drawModel();
	obj_face_data *getFaceData(char *token);
	int *basic_face_data(char * input);
};


#endif