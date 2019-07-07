#version 450 core

uniform uint dt;
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 dir;

out vec4 color;

vec4 color_get(uint x)
{
  return vec4(1 - float(x) / 20.f, 0.0f, 0.0f, 1.0f);
}

void main()
{
  gl_Position = vec4(pos.x + dt * dir.x, pos.y + dt * dir.y, pos.z + dt * dir.z, 1.0f);
  gl_PointSize = 10;

  color = color_get(dt);
}   
