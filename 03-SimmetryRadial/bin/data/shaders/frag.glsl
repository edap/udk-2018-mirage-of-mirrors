#version 150
const float PI = 3.14159265359;

uniform sampler2DRect tex0;
uniform vec2 uMousePos;
uniform vec2 uResolution;

in vec2 vTexCoord;
out vec4 outputColor;

vec2 Kaleidoscope( vec2 uv, float n) {
    float angle = PI / n;

    float r = length( uv );
    float a = atan( uv.y, uv.x ) / angle;

    a = mix( fract( a ), 1.0 - fract( a ), mod( floor( a ), 2.0 ) ) * angle;

    return vec2( cos( a ), sin( a ) ) * r;
}

void main()
{

    float nSides = 10.0;
    // credits:
    // https://github.com/gcorallo/OF_Experiments/blob/master/Kaleido/bin/data/rotate.frag
    // https://www.shadertoy.com/view/Xs23zm
    vec4 finalColor;

    vec2 coord = vTexCoord;

    vec2 uv = ( gl_FragCoord.xy * 2.0 - uResolution.xy ) /max( uResolution.x, uResolution.y );


    // uncomment this line to have a fix number of sides
    nSides = uResolution.y/uMousePos.y;

    uv = mix( uv, Kaleidoscope( uv, nSides), 1.0 );

    //coord = uv*uResolution.x;
    coord = uv* max(400, uMousePos.x);

    finalColor = texture(tex0, coord);

    outputColor = finalColor;


}
