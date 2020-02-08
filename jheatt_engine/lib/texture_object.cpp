#include "texture_object.hpp"

TextureObject::TextureObject(const char * textureFilePath, int slot, GLenum type) {
		unitSlot = slot;
    // Create device object able to store texture in graphics card memory:
    glGenTextures(unitSlot, &handle);
    glBindTexture(type, handle); // Bind so we can apply operations to it

    int width, height;
    unsigned char* image = SOIL_load_image(textureFilePath, &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(type, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    if (image == nullptr) {
        printf("SOIL Texture Error; Could not load '%s':\n'%s'\n\n", textureFilePath, SOIL_last_result());
        return;
    }
    SOIL_free_image_data(image);

    glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

TextureObject::~TextureObject() {
	glDeleteTextures(unitSlot, &handle);
}