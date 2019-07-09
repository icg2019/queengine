#version 330 core

in vec3 v_color;
in vec2 v_text_coord;

uniform sampler2D ourTexture;

out vec4 fragColor;

    

void main()
{
   // FragColor = vec4(01.0f,0,1.0f,1.0f) ;
 // fragColor = vec4(v_color,1.0);
  fragColor = texture(ourTexture, v_text_coord)*vec4(v_color,0.30);
  

}