// Interpolated values from the vertex shaders
// in vec2 UV;
in vec3 Position_worldspace;
in vec3 Normal_cameraspace;
in vec3 EyeDirection_cameraspace;
in vec3 LightDirection_cameraspace;

//obj materials

uniform vec3 obj_ambient;
uniform vec3 obj_specular;
uniform vec3 obj_diffuse;

void mainImage(out vec4 fragColor, in vec2 fragCoord){

	// Light emission properties
	// You probably want to put them as uniforms
	vec3 LightColor = vec3(1.0, 1.0, 1.0);
	float LightPower = 150.0f;
	vec3 LightPosition_worldspace = vec3(4.0f, 4.0f, 4.0f);

	// Material properties
	vec3 MaterialDiffuseColor = texture(iChannel0, fragCoord ).rgb;
	vec3 MaterialAmbientColor = obj_ambient * MaterialDiffuseColor;
	vec3 MaterialSpecularColor = obj_specular;

	// Distance to the light
	float distance = length( LightPosition_worldspace - Position_worldspace );

	// Normal of the computed fragment, in camera space
	vec3 n = normalize( Normal_cameraspace );
	// Direction of the light (from the fragment to the light)
	vec3 l = normalize( LightDirection_cameraspace );
	// Cosine of the angle between the normal and the light direction,
	// clamped above 0
	//  - light is at the vertical of the triangle -> 1
	//  - light is perpendicular to the triangle -> 0
	//  - light is behind the triangle -> 0
	float cosTheta = clamp( dot( n,l ), 0.0f, 1.0f );

	// Eye vector (towards the camera)
	vec3 E = normalize(EyeDirection_cameraspace);
	// Direction in which the triangle reflects the light
	vec3 R = reflect(-l,n);
	// Cosine of the angle between the Eye vector and the Reflect vector,
	// clamped to 0
	//  - Looking into the reflection -> 1
	//  - Looking elsewhere -> < 1
	float cosAlpha = clamp( dot( E,R ), 0.0f, 1.0f);

	fragColor =
		// Ambient : simulates indirect lighting
		vec4(MaterialAmbientColor +
		// Diffuse : "color" of the object
		MaterialDiffuseColor * LightColor * LightPower * cosTheta / (distance*distance) +
		// Specular : reflective highlight, like a mirror
		MaterialSpecularColor * LightColor * LightPower * pow(cosAlpha,5.0f) / (distance*distance), 1.0);

}
