#include "stb_image.h"
#include <GL/freeglut.h>
#include <iostream>
#include "Texture.h"

GLuint bg_texture, intro_texture, end_texture;
extern int width1, height1;
extern int level;

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
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//------------------------------------------------------------------------------------------------------------------

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    //PixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(1, &end_texture);
    glBindTexture(GL_TEXTURE_2D, end_texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    int widthe, heighte, nrChannelse;
    unsigned char* data3 = stbi_load("Res/Textures/2.png", &widthe, &heighte, &nrChannelse, 4);

    if (stbi_failure_reason())
        std::cout << stbi_failure_reason();

    if (data3)
    {
        std::cout << data3 << std::endl;
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, widthe, heighte, 0, GL_RGBA, GL_UNSIGNED_BYTE, data3);
    }
    else
    {
        std::cout << "Failed to load background" << std::endl;
    }

    stbi_image_free(data3);

    //-----------------------------------------------------------------------------------------------------------------------

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    //PixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(1, &intro_texture);
    glBindTexture(GL_TEXTURE_2D, intro_texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    int widthk, heightk, nrChannelsk;
    unsigned char* data1 = stbi_load("Res/Textures/intro.png", &widthk, &heightk, &nrChannelsk, 4);

    if (stbi_failure_reason())
        std::cout << stbi_failure_reason();

    if (data1)
    {
        std::cout << data1 << std::endl;
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, widthk, heightk, 0, GL_RGBA, GL_UNSIGNED_BYTE, data1);
    }
    else
    {
        std::cout << "Failed to load background" << std::endl;
    }

    stbi_image_free(data1);


    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void intro() {
    glEnable(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, intro_texture);
   
    //Image size = 1536*1536
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 0.0f);   glVertex2f(0.0, 0.0);
    glTexCoord2f(1.0f, 1.0f);   glVertex2f(0.0, (float)1000);
    glTexCoord2f(0.0f, 1.0f);   glVertex2f((float)2000, (float)1000);
    glTexCoord2f(0.0f, 0.0f);   glVertex2f((float)2000, 0.0);
    glEnd();
    glDisable(GL_TEXTURE_2D);

}

void end() {
    glEnable(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, end_texture);

    //Image size = 1536*1536
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 0.0f);   glVertex2f(0.0, 0.0);
    glTexCoord2f(1.0f, 1.0f);   glVertex2f(0.0, (float)1000);
    glTexCoord2f(0.0f, 1.0f);   glVertex2f((float)2000, (float)1000);
    glTexCoord2f(0.0f, 0.0f);   glVertex2f((float)2000, 0.0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}