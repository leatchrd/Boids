#version 330 core

in vec3 vPosition_vs;  // in View Space
in vec3 vNormal_vs;    // in View Space
in vec2 vTexCoords;

out vec4 fFragColor;

uniform sampler2D uTexture; // texture
uniform float uDetailLevel;

uniform vec3 uKd;         // diffuse property
uniform vec3 uKs;         // specularity
uniform float uShininess; // shininess

uniform vec3 uLightPos_vs; // light info
uniform vec3 uLightIntensity;

vec3 blinnPhong() {
    vec3 L = uLightIntensity / (distance(vPosition_vs, uLightPos_vs) * distance(vPosition_vs, uLightPos_vs));
    return L * (uKd * (dot(normalize(uLightPos_vs - vPosition_vs), vNormal_vs)) + uKs * pow((dot(normalize(-vPosition_vs), vNormal_vs)), uShininess));
}

void main() {
    vec4 fragTexture = textureLod(uTexture, vTexCoords, uDetailLevel);
    vec3 fragLighting = blinnPhong();
    fFragColor = vec4(fragTexture.rgb * fragLighting.rgb, fragTexture.a);
}