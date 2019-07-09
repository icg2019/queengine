in vec3 frag_loc;

struct Luz {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Luz light;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

void mainImage(out vec4 fragColor, in vec2 fragCoord)
{

    Material material;

    // ambient
    vec3 ambient = light.ambient * material.ambient;
    
  
    // diffuse
    vec3 norm = texture(iChannel0, fragCoord).rgb;
    norm = normalize( norm* 2.0 - 1.0);
    // vec3 lightDir = normalize(light.position - frag_loc);
    vec3 lightDir = normalize(light.position);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (diff*material.diffuse);

  
    // specular
    // vec3 viewVector = normalize(vec3(0.0,0.0,0.0) - frag_loc);
    vec3 viewVector = normalize(vec3(0.0,0.0,0.0));
    vec3 reflectVetor = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewVector, reflectVetor), 0.0), material.shininess);
    vec3 specular = light.specular * (spec*material.specular);

    vec3 result = (ambient + diffuse + specular);

    fragColor = vec4(result, 1.0);
}