#version 450 core

in vec4 frag_color;
out vec4 color;

void main()
{
  //color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
  color = frag_color;
}
