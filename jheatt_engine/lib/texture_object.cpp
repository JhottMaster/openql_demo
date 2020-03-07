#include "texture_object.hpp"

TextureObject::TextureObject(const char * textureFilePath, int slot, TextureUsage usage, GLenum format, GLenum type) {
		unitSlot = slot;
   
    int Width, Height;
    unsigned char* image = SOIL_load_image(textureFilePath, &Width, &Height, 0, SOIL_LOAD_RGB);
    if (image == nullptr) {
      printf("SOIL Texture Error; Could not load '%s':\n'%s'\n\n", textureFilePath, SOIL_last_result());
      return;
    }
        
    glGenTextures(1, &handle); // Create device object able to store texture in graphics card memory
    glBindTexture(_type, handle); // Bind to it so we can perform operations
    glTexImage2D(type, 0, GL_RGB, Width, Height, 0, format, GL_UNSIGNED_BYTE, image); // Create texture
    
	glGenerateMipmap(type);

    glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    SOIL_free_image_data(image);

    _type = type;
    _format = format;
    Usage = usage; 
    FilePath = textureFilePath;

    glBindTexture(type, 0);
}

void TextureObject::UseTexture(Shader* shader) {
  glActiveTexture(GL_TEXTURE0 + unitSlot);
  
  if (Usage == TextureUsage::SPECULAR) {
    shader->SetIntVariable("material.specular_texture_0", unitSlot);
  } else {
    shader->SetIntVariable("material.diffuse_texture_0", unitSlot);
  }
 
  glBindTexture(_type, handle);
}

TextureObject::~TextureObject() {
	glDeleteTextures(unitSlot, &handle);
}