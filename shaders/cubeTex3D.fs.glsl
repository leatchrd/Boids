#version 330 core

in vec3 vPosition_vs;  // in View Space
in vec3 vNormal_vs;    // in View Space
in vec2 vTexCoords;

out vec4 fFragTexture;

uniform sampler2D uTextureGlass;

void main() {
  // fFragTexture = vec4((texture(uTextureGlass, vTexCoords)).xyz, 0.25);
  fFragTexture = texture(uTextureGlass, vTexCoords);
}