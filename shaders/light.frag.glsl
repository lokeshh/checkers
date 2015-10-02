# version 120

/* This is the fragment shader for reading in a scene description, including
   lighting.  Uniform lights are specified from the main program, and used in
   the shader.  As well as the material parameters of the object.  */

// Mine is an old machine.  For version 130 or higher, do
// in vec4 color;
// in vec3 mynormal;
// in vec4 myvertex;
// That is certainly more modern

varying vec4 color;
varying vec3 mynormal;
varying vec4 myvertex;

const int numLights = 10;
uniform bool enablelighting; // are we lighting at all (global).
uniform vec4 lightposn[numLights]; // positions of lights
uniform vec4 lightcolor[numLights]; // colors of lights
uniform int numused;               // number of lights used


// Now, set the material parameters.  These could be varying and/or bound to
// a buffer.  But for now, I'll just make them uniform.
// I use ambient, diffuse, specular, shininess as in OpenGL.
// But, the ambient is just additive and doesn't multiply the lights.

uniform vec4 ambient;
uniform vec4 diffuse;
uniform vec4 specular;
uniform vec4 emission;
uniform float shininess;

vec4 ComputeLight (const in vec3 direction, const in vec4 lightcolor, const in vec3 normal, const in vec3 halfvec, const in vec4 mydiffuse, const in vec4 myspecular, const in float myshininess) {

	float nDotL = dot(normal, direction)  ;
	vec4 lambert = mydiffuse * lightcolor * max (nDotL, 0.0) ;

	float nDotH = dot(normal, halfvec) ;
	vec4 phong = myspecular * lightcolor * pow (max(nDotH, 0.0), myshininess) ;

	vec4 retval = lambert + phong ;
	return retval ;
}

void main (void)
{
    //cout << lightposn[4] << endl;
    if (enablelighting) {
        vec4 finalcolor;

        // YOUR CODE FOR HW 2 HERE
        // A key part is implementation of the fragment shader

        const vec3 eyepos = vec3(0,0,0) ;
    		vec4 _mypos = gl_ModelViewMatrix * myvertex ;
    		vec3 mypos = _mypos.xyz / _mypos.w ; // Dehomogenize current location
    		vec3 eyedirn = normalize(eyepos - mypos) ;

    		// Compute normal, needed for shading.
    		// Simpler is vec3 normal = normalize(gl_NormalMatrix * mynormal) ;
    		vec3 _normal = (gl_ModelViewMatrixInverseTranspose*vec4(mynormal,0.0)).xyz ;
    		vec3 normal = normalize(_normal) ;

        vec3 light0dirn = vec3(0.6, 0.0707107, 0.0707107);
        vec4 light0color = vec4(1, 0.5, 0, 1 );

        // Light 0, directional
    		vec3 direction0 = normalize (light0dirn) ;
    		vec3 half0 = normalize (direction0 + eyedirn) ;
    		vec4 col0 = ComputeLight(direction0, light0color, normal, half0, diffuse, specular, shininess) ;

        vec4 light1posn = vec4(0, -0.353553, -2.33345, 1);
        vec4 light1color = vec4(0.5, 0.5, 1, 1);

    		// Light 1, point
    		vec3 position = light1posn.xyz / light1posn.w ;
    		vec3 direction1 = normalize (position - mypos) ; // no attenuation
    		vec3 half1 = normalize (direction1 + eyedirn) ;
    		vec4 col1 = ComputeLight(direction1, light1color, normal, half1, diffuse, specular, shininess) ;

        // Color all pixels black for now, remove this in your implementation!
        //finalcolor = vec4(0,0,0,1);


        gl_FragColor = ambient + col0 + col1 + emission;
    } else {
        gl_FragColor = color;
    }
}
