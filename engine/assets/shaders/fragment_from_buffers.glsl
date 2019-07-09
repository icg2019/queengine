struct Luz {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

void mainImage(out vec4 fragColor, in vec2 fragCoord)
{

    Material material;
    material.ambient = vec3(1.0f, 0.5f, 0.31f);
    material.diffuse = vec3(1.0f, 0.5f, 0.31f);
    material.specular = vec3(0.5f, 0.5f, 0.5f);
    material.shininess = 32.0f;

    Luz light;
    light.position = vec3(1.2f, 1.0f, 1.0f);
    light.ambient = vec3(0.2f, 0.2f, 0.2f);
    light.diffuse = vec3(0.5f, 0.5f, 0.5f);
    light.specular = vec3(1.0f, 1.0f, 1.0f);

    // ambient
    vec3 ambient = light.ambient * material.ambient;
    
  
    // diffuse
    vec3 norm = texture(iChannel0, texCoord).rgb;
    norm = normalize( norm* 2.0 - 1.0);
    // vec3 lightDir = normalize(light.position - frag_loc);
    vec3 lightDir = normalize(light.position - frag_loc);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (diff*material.diffuse);

  
    // specular
    // vec3 viewVector = normalize(vec3(0.0,0.0,0.0) - frag_loc);
    vec3 viewVector = normalize(vec3(0.0,0.0,0.0) - frag_loc);
    vec3 reflectVetor = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewVector, reflectVetor), 0.0), material.shininess);
    vec3 specular = light.specular * (spec*material.specular);

    vec3 result = (ambient + diffuse + specular);

    fragColor = vec4(result, 1.0);
}