#version 300 es

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 colorUV;
layout (location = 2) in vec3 vertexNormal;

out mediump vec2    pos;
uniform vec3 offset;
uniform mat4 model_m;
uniform mat4 view_m;
uniform mat4 projection_m;
                                         
   void main()                           
   {   
      vec3 newposition = position + offset;                           
      gl_Position = projection_m * view_m * model_m * vec4(newposition.x, newposition.y, newposition.z, 1.0);   
      pos = position.xy;                 
   }   