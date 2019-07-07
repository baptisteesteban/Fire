#version 450 core

layout (points) in;
layout (points, max_vertices=2) out;

in vec4 vert_color[];
out vec4 frag_color;

void main()
{
  
  frag_color = vert_color[0];
  gl_Position = gl_in[0].gl_Position;
  gl_PointSize = 5;
  EmitVertex();
  gl_Position = gl_in[0].gl_Position * vec4(-1.0f, 1.0f, 1.0f, 1.0f);
  gl_PointSize = 5;
  EmitVertex();
  EndPrimitive();
}
