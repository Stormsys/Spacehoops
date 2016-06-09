#include "ObjLoader.h"

#define WHITESPACE " \t\n\r"

ObjModel::ObjModel(char * filename)
{
	FILE* obj_file_stream;	
	char *current_token = NULL;
	char current_line[500];
	int line_number = 0;
	int mtlIndex = -1;
	nFace = 0;
	char _filename[255];
	sprintf(_filename, "%s%s", "./data/", filename);

	obj_file_stream = fopen( _filename, "r");
	if(obj_file_stream == 0)
	{
		std::cout << "error reading file" << std::endl;
		return;
	}else{
		while( fgets(current_line, 500, obj_file_stream) )
		{
			current_token = strtok( current_line, WHITESPACE);
			line_number++;

			if( current_token == NULL || current_token[0] == '#')
				continue;
			else if(strcmp(current_token, "v") == 0)
			{
				vertexList.push_back(new point3d(atof(strtok(NULL, WHITESPACE)),atof(strtok(NULL, WHITESPACE)),atof(strtok(NULL, WHITESPACE))));
			}else if(strcmp(current_token, "vt") == 0)
			{
				textureList.push_back(new point3d(atof(strtok(NULL, WHITESPACE)),atof(strtok(NULL, WHITESPACE)),atof(strtok(NULL, WHITESPACE))));
			}else if(strcmp(current_token, "vn") == 0)
			{
				normalList.push_back(new point3d(atof(strtok(NULL, WHITESPACE)),atof(strtok(NULL, WHITESPACE)),atof(strtok(NULL, WHITESPACE))));
			}else if(strcmp(current_token, "f") == 0)
			{
				  obj_face *newFace = new obj_face();
					
				  newFace->vertex_count = 0;

				  char *face_list;
				  char *curentFace;			  
				  face_list = strtok (NULL, WHITESPACE);
				  while (face_list != NULL)
				  {
					newFace->face_data.push_back(getFaceData(face_list));
					newFace->vertex_count++;				
					face_list = strtok (NULL, WHITESPACE);
				  }
				  newFace->material_index = mtlIndex;
				  faceList.push_back(newFace);
				  nFace++;
			}else if(strcmp(current_token, "mtllib") == 0)
			{
				loadMtl(strtok(NULL, WHITESPACE));
			}else if(strcmp(current_token, "usemtl") == 0)
			{
				mtlIndex = getMtlIndex(strtok(NULL, WHITESPACE));
			}
		}
	}
}
int ObjModel::getMtlIndex(char *name)
{
	for(int i = 0; i < materialList.size(); i++)
	{
		if(strcmp(name, materialList[i]->name)==0)
			return i;
	}
	return -1;
}
void ObjModel::loadMtl(char * filename)
{
	
	FILE* obj_file_stream;	
	char *current_token = NULL;
	char current_line[500];
	int line_number = 0;

	mtl_data *newMtl = NULL;

	nFace = 0;
	char _filename[255];
	sprintf(_filename, "%s%s", "./data/", filename);

	obj_file_stream = fopen( _filename, "r");

	if(obj_file_stream == 0)
	{
		std::cout << "error reading file" << std::endl;
		return;
	}
	while( fgets(current_line, 500, obj_file_stream) )
	{
		current_token = strtok( current_line, WHITESPACE);
		line_number++;

		if( current_token == NULL || current_token[0] == '#')
			continue;
		else if(strcmp(current_token, "newmtl") == 0)
		{
			if(newMtl != NULL)
				materialList.push_back(newMtl);

			newMtl = new mtl_data();
			//newMtl->name = "";
			strcpy(newMtl->name,strtok(NULL, WHITESPACE));
		}else if(strcmp(current_token, "Ka") == 0)
		{
			newMtl->Ka = new point3d(atof(strtok(NULL, WHITESPACE)),atof(strtok(NULL, WHITESPACE)),atof(strtok(NULL, WHITESPACE)));
		}else if(strcmp(current_token, "Kd") == 0)
		{
			newMtl->Kd = new point3d(atof(strtok(NULL, WHITESPACE)),atof(strtok(NULL, WHITESPACE)),atof(strtok(NULL, WHITESPACE)));
		}else if(strcmp(current_token, "Ks") == 0)
		{
			newMtl->Ks = new point3d(atof(strtok(NULL, WHITESPACE)),atof(strtok(NULL, WHITESPACE)),atof(strtok(NULL, WHITESPACE)));
		}else if(strcmp(current_token, "illum") == 0)
		{
			newMtl->i = atof(strtok(NULL, WHITESPACE));
		}else if(strcmp(current_token, "d") == 0)
		{
			newMtl->d = atof(strtok(NULL, WHITESPACE));
		}else if(strcmp(current_token, "Ns") == 0)
		{
			newMtl->s = atof(strtok(NULL, WHITESPACE));
		}
	}
	if(newMtl != NULL)
		materialList.push_back(newMtl);
}

obj_face_data *ObjModel::getFaceData(char *token)
{		    
	obj_face_data *newFaceData = new obj_face_data();
	int *p = basic_face_data(token);
	newFaceData->vertex = p[0];	
	newFaceData->texture = p[1];	
	newFaceData->normal = p[2];
	return newFaceData;
}
int *ObjModel::basic_face_data(char * input)
{
  int result[3];
  int curval = 0;
  char store_num[20];
  sprintf(store_num, "");/*emptry the number storage*/
  while (*input != NULL)
  {
	if(*input=='/')
	{
		result[curval] = atoi(store_num);
		curval++;
		sprintf(store_num, "");
	}else
		sprintf(store_num, "%s%c",store_num,*input);
	*input++;
  }
  result[curval] = atoi(store_num);

  return result;
}

void ObjModel::drawModel()
{
	
	glDisable(GL_COLOR_MATERIAL);
	int prevMtlIndex = -1;
			for(int i = 0; i < nFace; i++)
			{
				if(faceList[i]->material_index != prevMtlIndex && faceList[i]->material_index != -1)
				{
					prevMtlIndex = faceList[i]->material_index;
					
					GLfloat	 matAmbiant[] = { materialList[prevMtlIndex]->Ka->z, materialList[prevMtlIndex]->Ka->y, materialList[prevMtlIndex]->Ka->x, 1.0f };
					GLfloat	 matDiff[] = { materialList[prevMtlIndex]->Kd->z, materialList[prevMtlIndex]->Kd->y, materialList[prevMtlIndex]->Kd->x, 1.0f };
					GLfloat	 matSpec[] = { materialList[prevMtlIndex]->Ks->z, materialList[prevMtlIndex]->Ks->y, materialList[prevMtlIndex]->Ks->x, 1.0f };
					GLfloat	 shine[] = {materialList[prevMtlIndex]->s };
					//glColor3f(materialList[prevMtlIndex]->Kd->x, materialList[prevMtlIndex]->Kd->y, materialList[prevMtlIndex]->Kd->z); 
					glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matAmbiant);
					glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matDiff);
					glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpec);
					glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shine);
				}
				glBegin(GL_POLYGON);					
				for(int j = 0; j < faceList[i]->vertex_count; j++)
				{			
					float nx = normalList[faceList[i]->face_data[j]->normal-1]->x;
					float ny = normalList[faceList[i]->face_data[j]->normal-1]->y;
					float nz = normalList[faceList[i]->face_data[j]->normal-1]->z;
				
					float x = vertexList[faceList[i]->face_data[j]->vertex-1]->x;
					float y = vertexList[faceList[i]->face_data[j]->vertex-1]->y;
					float z = vertexList[faceList[i]->face_data[j]->vertex-1]->z;
					
					glNormal3f(nx,ny,nz);
					glVertex3f(x,y,z);	
		
				}			
	
				glEnd();
			}			
	glEnable(GL_COLOR_MATERIAL);
}
