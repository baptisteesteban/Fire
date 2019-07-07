#version 450 core

layout (location=0) in vec3 pos;
layout (location=1) in float life;

out vec4 vert_color;

vec4 color_get(float x)
{
  float r = 1.0f;
  float g = 1.0f;
  float b = 1.0f;
  
  if (x <= 0.8f && x > 0.6f)
    b = (x - 0.6f) / 0.3f;
  else if (x <= 0.6f)
    b = 0.0f;

  if (x <= 0.6f && x > 0.4f)
    g = (x - 0.4f) / 0.3f;
  else if (x <= 0.4f)
    g = 0.0f;

  if (x <= 0.3f && x > 0.2f)
    r = (x - 0.2f) / 0.1f;
  else if (x <= 0.2f)
    r = 0.0f;

  return vec4(r, g, b, 1.0f);
}

void main()
{
  gl_Position = vec4(pos.x, pos.y, pos.z, 1.0f);
  vert_color = color_get(life);
}   
