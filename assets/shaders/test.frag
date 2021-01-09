#version 410 core

out vec4 fragColor;

float specular(vec3 L, vec3 N, vec3 H)
{
	float result = 0.0;
	if(dot(N, L) > 0.0)
	{
		return pow(clamp(dot(H, N), 0.0, 1.0), 64);
	}
	return result;
}

in VS_OUT
{
	vec3 normal;
	vec3 lightVector;
	vec3 viewVector;
}fs_in;

void main()
{
	vec3 eye = normalize(-fs_in.viewVector);
	vec3 reflected = normalize(reflect(-fs_in.lightVector, fs_in.normal)); 
 	vec3 halfVector = fs_in.lightVector + fs_in.viewVector;

	vec4 ambient = vec4(0.2, 0.2, 0.2, 1.0);
	float diff = clamp(dot(fs_in.normal, fs_in.lightVector), 0.0, 1.0);
	vec4 diffuse = vec4(0.3, 0.3, 0.3, 1.0f) 
		* max(dot(fs_in.normal, fs_in.lightVector), 0.0);
   	float spec = specular(fs_in.lightVector, fs_in.normal, halfVector);
	float shininess = 0.75;
   	float intensity = 0.1 + diff + spec;
    vec4 specular = vec4(0.5, 0.5, 0.5, 1.0) 
		* pow(max(dot(reflected, eye), 0.0), 2.0) * shininess; 
   
	vec3 inColor = vec3(0.5, 0.5, 0.5);
	fragColor = vec4((ambient + diffuse) * vec4(inColor, 1.0) + specular);
//     fragColor = IDiffuse;
}
