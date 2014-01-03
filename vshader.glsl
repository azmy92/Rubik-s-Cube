#version 130

attribute vec3 vPosition;
attribute vec3 vColor;


uniform mat4 view;
uniform mat4 proj;

uniform vec3 faceColor;
uniform vec3 cubeTrans;

out vec4 outColor;
uniform mat4 rotAroundX;
uniform mat4 rotAroundY;
uniform mat4 RotationMat;

uniform vec3 vNormal;

vec4 AmbientProduct, DiffuseProduct, SpecularProduct; 
vec4 LightPosition;
float Shininess = 500.0;

void main()
{
AmbientProduct = vec4(0.2, 0.2, 0.2, 1.0);
DiffuseProduct = vec4(1.0, 0.8, 0.0, 1.0);
SpecularProduct = vec4(1.0, 1.0, 1.0, 1.0);
mat4 transs = mat4( 	     1.0, 0.0, 0.0, cubeTrans.x,
			    			 0.0, 1.0, 0.0, cubeTrans.y,
			            	 0.0, 0.0, 1.0, cubeTrans.z,
				     	 	 0.0, 0.0, 0.0, 1.0 );

			mat4 ModelView = view * RotationMat * transs;

	vec3 pos = (ModelView * vec4(vPosition,1.0)).xyz;
	// Compute viewer vector in eye coordinate 
	vec3 E = normalize( -pos );
	

	// Compute light vector in eye coordinate 
	LightPosition = vec4(00.0,15.0,20.0,1.0);
	vec3 L; 
	if (LightPosition.w == 0.0) 
		L = normalize( (view * LightPosition).xyz ); 
	else L = normalize( (view * LightPosition).xyz - pos );
	// Compute halfway vector in eye coordinate 
	vec3 H = normalize( L + E ); 
	// halfway vector // Transform normal vector into eye coordinates 
	vec3 N = normalize( ModelView * vec4(vNormal, 0.0) ).xyz;
	
	
	// Compute terms in the illumination equation 
	vec4 ambient = AmbientProduct; 
	float Kd = max( dot(L, N), 0.0 ); 
	vec4 diffuse = Kd * DiffuseProduct; 
	float Ks = pow( max(dot(N, H), 0.0), Shininess ); 
	vec4 specular = Ks * SpecularProduct; 
	// discard the specular highlight if the light's behind the vertex 
	if ( dot(L, N) < 0.0 ) 
		specular = vec4(0.0, 0.0, 0.0, 1.0);
	
	gl_Position = proj* view * RotationMat * vec4(vPosition.x + cubeTrans.x,vPosition.y + cubeTrans.y,vPosition.z + cubeTrans.z, 1.0); 
	vec4 fcolor = vec4(faceColor,1.0);
	outColor = (ambient + diffuse + specular) + fcolor;
	outColor.a = 1.0;
	
	//gl_Position = proj * view * RotationMat * vec4(vPosition.x + cubeTrans.x,vPosition.y + cubeTrans.y,vPosition.z + cubeTrans.z, 1.0);	;
	//outColor = vec4(faceColor,1.0);




































/*
AmbientProduct = vec4(0.2, 0.2, 0.2, 1.0);
DiffuseProduct = vec4(1.0, 0.2, 0.0, 1.0);
SpecularProduct = vec4(1.0, 1.0, 1.0, 1.0);

mat4 transs = mat4( 	     1.0, 0.0, 0.0, cubeTrans.x,
			    			 0.0, 1.0, 0.0, cubeTrans.y,
			            	 0.0, 0.0, 1.0, cubeTrans.z,
				     	 	 0.0, 0.0, 0.0, 1.0 );

			mat4 ModelView = view * RotationMat * transs;
	LightPosition = vec4(00.0,15.0,30.0,1.0);


// Transform vertex position into eye coordinates
vec3 pos = (ModelView * vec4(vPosition,1.0)).xyz;
vec3 L = normalize( LightPosition.xyz - pos );
vec3 E = normalize( -pos );
vec3 H = normalize( L + E ); // halfway Vector
// Transform vertex normal into eye coordinates
vec3 N = normalize( ModelView*vec4(vNormal, 0.0) ).xyz;


vec4 ambient = AmbientProduct;
float cos_theta = max( dot(L, N), 0.0 );
vec4 diffuse = cos_theta * DiffuseProduct;
float cos_phi = pow( max(dot(N, H), 0.0), Shininess );
vec4 specular = cos_phi * SpecularProduct;


if( dot(L, N) < 0.0 ) 
	specular = vec4(0.0, 0.0, 0.0, 1.0); 

gl_Position = proj * ModelView * vec4(vPosition,1.0);
vec4 fcolor = vec4(faceColor,1.0);
	
outColor = (ambient + diffuse + specular) + fcolor;
outColor.a = 1.0;

///////////////////////////////////////////////////////////////////////////////
*/	  
}








