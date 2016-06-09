#include "textures.h"

static const char *szTextureFiles[TEXTURE_COUNT] = { "data/nebula.tga","data/the_sun.tga","data/plasma.tga", "data/plasma_green.tga"
, "data/earth.tga", "data/mars.tga", "data/jupiter.tga", "data/venus.tga",
"data/radar.tga", "data/air_pointer.tga", "data/life_bar.tga", "data/sheild_bar.tga", "data/health_bar.tga", "data/score_orb.tga"};

static GLuint  textureList[TEXTURE_COUNT];

void Textures::Use(int which)
{
	glEnable(GL_TEXTURE_2D);
	if(which < TEXTURE_COUNT && which >= 0)
	{
        glBindTexture(GL_TEXTURE_2D, textureList[which]);
	}
}
void Textures::Done()
{
	glDisable(GL_TEXTURE_2D);
}
void Textures::LoadAll()
{
	GLint width, height, components;
	GLenum format;
	GLbyte *memTexture;
    GLuint texture;    
    glGenTextures( 1, &texture );
    glPixelStorei(GL_UNPACK_ALIGNMENT,1);

    glGenTextures(TEXTURE_COUNT, textureList);
    glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
    for(int i = 0; i < TEXTURE_COUNT; i++)
    {
        glBindTexture(GL_TEXTURE_2D, textureList[i]);
        
        memTexture = gltLoadTGA(szTextureFiles[i],&width, &height, &components, &format);
    		
		glTexImage2D(GL_TEXTURE_2D, 0, components, width, height, 0, format, GL_UNSIGNED_BYTE, memTexture);
		free(memTexture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    }
}