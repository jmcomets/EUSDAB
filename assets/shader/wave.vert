uniform float wave_phase;
uniform vec2 wave_amplitude;
uniform float ratio;

void main()
{
    vec4 vertex = gl_Vertex;
    vertex.x += cos(gl_Vertex.y * 0.02 + wave_phase * 3.8) * wave_amplitude.x
        + sin(gl_Vertex.y * 0.02 + wave_phase * 6.3) * wave_amplitude.x * 0.3;
    vertex.y += sin(gl_Vertex.x * 0.02 + wave_phase * 2.4) * wave_amplitude.y
        + cos(gl_Vertex.x * 0.02 + wave_phase * 5.2) * wave_amplitude.y * 0.3;

    vec4 pixel = vec4(ratio, 1.0 - ratio, ratio, 1.0);
    pixel.rgb = pixel.rgb * vec3(vertex.x, vertex.y, vertex.x * vertex.y);

    gl_Position = gl_ModelViewProjectionMatrix * vertex;
    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
    gl_FrontColor = gl_Color * pixel;
}
