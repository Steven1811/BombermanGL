#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;

uniform float ambientStrength;
uniform float specularStrength;
uniform int shininess;

uniform vec3 objectColor;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 viewPos;

void main() {
    //General Calculations
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);

    //Ambient Calculation
    vec3 ambient = ambientStrength * lightColor;

    //Specular Calculation
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = specularStrength * spec * lightColor;

    //Difuse Calculation
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    FragColor = vec4((ambient + diffuse + specular) * objectColor, 1.0f);
}