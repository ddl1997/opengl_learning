#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include <iostream>
#include <vector>

class Texture
{
public:
    int width, height, nrChannels;
    unsigned char* data;

    Texture(unsigned int& id, const char* filepath, GLenum target, GLint level, GLint internalformat, GLint border, GLenum format, GLenum type)
    {
        stbi_set_flip_vertically_on_load(true);

        glGenTextures(1, &id);
        //glActiveTexture(GL_TEXTURE0);
        glBindTexture(target, id);
        // 为当前绑定的纹理对象设置环绕、过滤方式
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        data = stbi_load(filepath, &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(target, level, internalformat, width, height, border, format, type, data);
            glGenerateMipmap(target);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
    }

    void setWrap()
    {

    }

    void setFilter()
    {

    }
};

#endif
