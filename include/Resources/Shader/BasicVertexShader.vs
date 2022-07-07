#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec2 vertexTexture;
layout(location = 3) in vec4 vertexColor;

out vec3 Position;
out vec2 TexCoord;
out vec3 Normal;
out vec4 Color;

uniform mat4 Transform;
uniform mat4 CameraTransform;
uniform mat4 CameraPerspective;
uniform mat4 Complementary;

out mat4 copyCameraTransform;

  
void main()
{
  gl_Position = CameraPerspective * CameraTransform * Transform * vec4(vertexPosition,1);

  Position = vec3(Transform * Complementary * vec4(vertexPosition,1));
  Normal = vec3(Transform  * vec4(vertexNormal, 0));
  TexCoord = vertexTexture;
  Color = vertexColor;

  copyCameraTransform = CameraTransform ;

  gl_Position = gl_Position;
  gl_Position = gl_Position / gl_Position.w;

}