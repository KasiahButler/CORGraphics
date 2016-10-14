#version 330

in vec3 gPosition;
in vec3 gNormal;
in vec2 gUV;

layout(location = 3) uniform sampler2D diffuseMap;
layout(location = 4) uniform sampler2D normalMap;
layout(location = 5) uniform sampler2D specularMap;

mat3 cotangent_frame(in vec3 N, in vec3 p, in vec2 uv);

layout(location = 0) out vec4 albedo;
layout(location = 1) out vec4 normal;
layout(location = 2) out vec4 specular;
layout(location = 3) out vec4 position;

void main()
{
	mat3 TBN = cotangent_frame(gNormal, gPosition, gUV);
	vec3 N = TBN * (texture(normalMap, gUV).xyz * 2 - 1);

	albedo   = texture(diffuseMap, gUV);
	normal   = vec4(N,0);
	specular = texture(specularMap, gUV);
	position = vec4(gPosition,1);
}

mat3 cotangent_frame( in vec3 N, in vec3 p, in vec2 uv )
{
	// rate of change of position is velocity, which is a direction!
    vec3 dp1  = dFdx( p );
    vec3 dp2  = dFdy( p );
    vec2 duv1 = dFdx( uv );
    vec2 duv2 = dFdy( uv );

	// get right angles for all of our directions!
    vec3 dp2perp = cross( dp2, N ); // determine right
    vec3 dp1perp = cross( N, dp1 ); // determine up

	// roll the right to line up with the texture's tangent
    vec3 T = dp2perp * duv1.x + dp1perp * duv2.x;
    vec3 B = dp2perp * duv1.y + dp1perp * duv2.y;

	// normalization of the Tangent and Bitangent
    float invmax = inversesqrt( max( dot(T,T), dot(B,B) ) );
    return mat3( T * invmax, B * invmax, N );
}