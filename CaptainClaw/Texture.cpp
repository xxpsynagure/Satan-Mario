#include "stb_image.h"
#include <GL/freeglut.h>
#include <iostream>
#include "Texture.h"

GLuint bg_texture;
extern int width1, height1;

void background() {
    glEnable(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, bg_texture);
    /*
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);   glVertex2f(0.0, 0.0);
    glTexCoord2f(0.0f, 1.0f);   glVertex2f(0.0, (float)height1);
    glTexCoord2f(1.0f, 1.0f);   glVertex2f((float)width1, (float)height1);
    glTexCoord2f(1.0f, 0.0f);   glVertex2f((float)width1, 0.0);
    glEnd();
    */
    //Image size = 1536*1536
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);   glVertex2f(0.0, 0.0);
    glTexCoord2f(0.0f, 1.0f);   glVertex2f(0.0, (float)1536);
    glTexCoord2f(1.0f, 1.0f);   glVertex2f((float)1536, (float)1536);
    glTexCoord2f(1.0f, 0.0f);   glVertex2f((float)1536, 0.0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void loadtexture()
{
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    //PixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(1, &bg_texture);
    glBindTexture(GL_TEXTURE_2D, bg_texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    int width, height, nrChannels;
    unsigned char* data2 = stbi_load("Res/Textures/level1_background.png", &width, &height, &nrChannels, 4);

    if (stbi_failure_reason())
        std::cout << stbi_failure_reason();

    if (data2)
    {
        std::cout << data2 << std::endl;
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
    }
    else
    {
        std::cout << "Failed to load background" << std::endl;
    }

    stbi_image_free(data2);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}