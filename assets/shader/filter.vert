uniform float percent;

void main()
{
    vec4 pixel = vec4(1.0, 1.0, 1.0, 1.0);

    if(percent <= 1.0)
    {
        if(gl_Color.r > 0.1
            && gl_Color.g > 0.1
            && gl_Color.b > 0.1)
        {
            pixel *= vec4(1.0, 1.0 - percent, 1.0 - percent, 1.0);
        }
    }
    else
    {
        pixel *= vec4(1.0, 0.0, 0.0, 1.0);
    }

    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
    gl_FrontColor = gl_Color * pixel;
}

