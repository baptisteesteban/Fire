#version 450 core

layout (points) in;
layout (points, max_vertices=20) out;

in vec4 color[];
out vec4 color_frag;

void main()
{
  color_frag = color[0];
  gl_Position = gl_in[0].gl_Position;
  gl_PointSize = 10;
  EmitVertex();
  gl_Position = gl_in[0].gl_Position * vec4(-1.0f, 1.0f, 1.0f, 1.0f);
  gl_PointSize = 10;
  EmitVertex();
  EndPrimitive();
}
