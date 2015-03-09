attribute vec4 Vertex;
attribute vec4 Texture;
uniform mat4 MatrixPos;
uniform mat4 MatrixTex;
varying vec4 TexCoord;

void main(void)
{
    gl_Position = MatrixPos * Vertex;
    TexCoord = MatrixTex * Texture;
}
