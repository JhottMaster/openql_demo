#include "texture_object.hpp"

TextureObject::TextureObject(const char * textureFilePath, int slot, TextureUsage usage, GLenum format, GLenum type) {
		unitSlot = slot;
   
    int Width, Height;
    unsigned char* image = SOIL_load_image(textureFilePath, &Width, &Height, 0, SOIL_LOAD_RGB);
    if (image == nullptr) {
      printf("SOIL Texture Error; Could not load '%s':\n'%s'\n\n", textureFilePath, SOIL_last_result());
      return;
    }

    // Create device object able to store texture in graphics card memory:
		glActiveTexture(GL_TEXTURE0 + unitSlot);
    glGenTextures(unitSlot, &handle);
    glBindTexture(_type, handle);

    glTexImage2D(type, 0, GL_RGB, Width, Height, 0, format, GL_UNSIGNED_BYTE, image);
    
    SOIL_free_image_data(image);

		glGenerateMipmap(type);
    glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    _type = type;
    _format = format;
    Usage = usage; 
    FilePath = textureFilePath;

    glBindTexture(type, 0);

}

void TextureObject::UseTexture(Shader* shader) {
  glActiveTexture(GL_TEXTURE0 + unitSlot);
  
  if (Usage == SPECULAR) {
    shader->SetIntVariable("material.specular_texture_0", unitSlot);
  } else {
    shader->SetIntVariable("material.diffuse_texture_0", unitSlot);
  }
 
  glBindTexture(_type, handle);
}

TextureObject::~TextureObject() {
	glDeleteTextures(unitSlot, &handle);
}