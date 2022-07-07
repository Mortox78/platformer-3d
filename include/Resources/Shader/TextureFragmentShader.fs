#version 330 core
out vec4 FragColor;
  
in vec3 Position;
in vec2 TexCoord;
in vec3 Normal;
in vec4 Color;

in mat4 copyCameraTransform;

struct Light
{
  vec3 position;
  vec3 direction;
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float constant;
  float linear;
  float quadratic;
  float spotAngle;
};

#define NB_MAX_LIGHT 16
uniform float nbLights;
uniform Light lights[NB_MAX_LIGHT];

uniform sampler2D ourTexture;

vec3 GetColorAfterLight(Light light, vec3 position, vec3 normal, vec4 color)
{
  //light.position = vec3(copyCameraTransform * vec4(light.position, 1.0f));
  //light.direction = vec3(copyCameraTransform * vec4(light.direction, 0.0f));

  float length = length(light.position - position);
  float attenuation = 1.0f / (light.constant + light.linear * length + 
    		    light.quadratic * (length * length)); ;

    if (light.spotAngle != 0 && (light.direction.x != 0 || light.direction.y != 0 || light.direction.z != 0))
    {
        float lightToSurfaceAngle = degrees(acos(dot(normalize((light.position - position)), normalize(-light.direction))));
        if(lightToSurfaceAngle > light.spotAngle)
          attenuation = 0.0f;
    }
    vec3 reflected = vec3(0,0,0);
    if (attenuation != 0.0f)
    {   
        //ambient
        vec3 ambient = light.ambient;

        //diffuse
        vec3 lightDir;
        if (light.direction.x == 0 && light.direction.y == 0 && light.direction.z == 0)
          lightDir = normalize((light.position - position)); 
        else
          lightDir = normalize(-light.direction);

        float lightNor = max(dot(lightDir, normal), 0.0);
        vec3 diffuse = light.diffuse * lightNor;

        //specular phong

        vec3 eye = vec3(0.f, 0.f, 0.f);

        vec3 refl = reflect(-lightDir, normal);
        vec3 view = normalize(eye - position);
        float specCoef = pow(max(0.f, dot(view, refl)), 256);
        vec3 specular = light.specular * specCoef;

        reflected = ambient + diffuse + specular;
        reflected *= attenuation;
    }
    return vec3(reflected * vec3(color));
}


void main()
{
    vec3 fragmentColor = vec3(GetColorAfterLight(lights[0], vec3(Position), normalize(vec3(Normal)), vec4(1.f, 1.f, 1.f, 1.f)));

    for (int i = 1 ; i < nbLights && i < NB_MAX_LIGHT ; i++)
    {
      fragmentColor += vec3(GetColorAfterLight(lights[i], vec3(Position), normalize(vec3(Normal)), vec4(1.f, 1.f, 1.f, 1.f)));
    }

    FragColor = texture(ourTexture, TexCoord) * vec4(fragmentColor, 1.f) * Color;
}