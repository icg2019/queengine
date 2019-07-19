#version 300 es

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 uPosition;
layout(location = 1) in vec2 tex_coords;
layout(location = 2) in vec3 normal;

// Output data ; will be interpolated for each fragment.
out vec2 fragCoord;
out vec3 Position_worldspace;
out vec3 Normal_cameraspace;
out vec3 EyeDirection_cameraspace;
out vec3 LightDirection_cameraspace;

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;
uniform mat4 transform;

uniform vec3 LightPosition_worldspace;

void main(){
	// Our ModelViewProjection : multiplication of our 3 matrices
	// mat4 MVP        = Projection * View * Model; // Remember, matrix multiplication is the other way around
    // This part needs to be extracted later to a scene or whatever

	// Output position of the vertex, in clip space : MVP * position
	gl_Position = transform * vec4(uPosition,1);

	// Position of the vertex, in worldspace : M * position
	Position_worldspace = (Model * vec4(uPosition,1)).xyz;

	// Vector that goes from the vertex to the camera, in camera space.
	// In camera space, the camera is at the origin (0,0,0).
	vec3 vertexPosition_cameraspace = ( View * Model * vec4(uPosition,1)).xyz;
	EyeDirection_cameraspace = vec3(4,3,3);

	// Vector that goes from the vertex to the light, in camera space. M is ommited because it's identity.
	vec3 LightPosition_cameraspace = ( View * vec4(LightPosition_worldspace,1)).xyz;
	LightDirection_cameraspace = LightPosition_cameraspace + EyeDirection_cameraspace;

	// Normal of the the vertex, in camera space
	Normal_cameraspace = ( View * Model * vec4(normal,0)).xyz; // Only correct if ModelMatrix does not scale the model ! Use its inverse transpose if not.

	// fragCoord of the vertex. No special space for this one.
	fragCoord = (tex_coords - vec2(-1, -1)) / vec2(2, 2);
}
