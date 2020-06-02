#version 330 core

in struct fragment_data
{
    vec4 position;
    vec4 normal;
    vec4 color;
    vec2 texture_uv;
    vec4 position_from_room_light;
} fragment;

uniform sampler2D texture_sampler;
uniform sampler2D texture_room_shadow;

out vec4 FragColor;

uniform vec3 camera_position;
uniform vec3 color     = vec3(0.51, 0.51, 0.41);
uniform float color_alpha = 1.0;
uniform float ambiant  = 0.2;
uniform float diffuse  = 0.8;
uniform float specular = 0.5;
uniform int specular_exponent = 128;

uniform bool room_light_on = true;
vec3 room_light = vec3(0,0,45);
float diffuse_room  = 0;
float specular_room = 0;

uniform bool truck_light_on = false;
uniform vec3 truck_light = vec3(0,0,0);
uniform vec3 orientation = vec3(1,0,0);
float diffuse_truck  = 0;
float specular_truck = 0;

void calculate_diffuse_specular(out float diffuse_value, out float specular_value, vec3 light, vec3 o, float angle)
{
    vec3 n = normalize(fragment.normal.xyz);
    vec3 u = normalize(light-fragment.position.xyz);
    if(dot(-u, normalize(o)) < angle){
        diffuse_value  = 0;
        specular_value = 0;
    }
    else{
        vec3 r = reflect(u,n);
        vec3 t = normalize(fragment.position.xyz-camera_position);

        diffuse_value  = diffuse * clamp( dot(u,n), 0.0, 1.0);
        specular_value = specular * pow( clamp( dot(r,t), 0.0, 1.0), specular_exponent);
    }
}

float ShadowCalculation(vec4 fragPosLightSpace, sampler2D shadowMap)
{
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r; 
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // check whether current frag pos is in shadow
    float shadow = currentDepth > closestDepth  ? 1.0 : 0.0;

    return shadow;
}  

void main()
{
    if(room_light_on) calculate_diffuse_specular(diffuse_room, specular_room, room_light, vec3(0,0,-1), -1.0);
    if(truck_light_on) calculate_diffuse_specular(diffuse_truck, specular_truck, truck_light, orientation, 0.75);

    vec3 white = vec3(1.0);
    vec4 color_texture = texture(texture_sampler, fragment.texture_uv);
    float room_shadow = ShadowCalculation(fragment.position_from_room_light, texture_room_shadow);
    vec3 c = (ambiant+diffuse_room*(1-room_shadow)+diffuse_truck)*color.rgb*fragment.color.rgb*color_texture.rgb + (specular_room*(1-room_shadow)+specular_truck)*white;

    FragColor = vec4(c, color_texture.a*fragment.color.a*color_alpha);
}
