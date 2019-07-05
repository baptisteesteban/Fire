#version 450 core

layout (points) in;
layout (points, max_vertices=20) out;

void main()
{
  for (float i = -0.5; i < 0.5; i += 1 / 20.0f)
  {
    gl_Position = gl_in[0].gl_Position + vec4(i, 0.0f, 0.0f, 0.0f);
    gl_PointSize = abs(i) * 40;;
    EmitVertex();
  }
  EndPrimitive();

}
