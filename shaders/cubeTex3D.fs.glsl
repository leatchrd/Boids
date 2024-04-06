#version 330 core

in vec3 vPosition_vs;  // in View Space
in vec3 vNormal_vs;    // in View Space
in vec2 vTexCoords;

out vec3 fFragTexture;

uniform sampler2D uTextureGlass;

void main() {
  fFragTexture = vec3(texture(uTextureGlass, vTexCoords)).xyz;
}