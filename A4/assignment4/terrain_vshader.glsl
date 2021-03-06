R"(
#version 330 core
uniform sampler2D noiseTex;

in vec3 vposition;
in vec2 vtexcoord;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

out vec2 uv;
out vec3 fragPos;

void main() {
    float h = 0.0;
    uv = vtexcoord;
    h = texture(noiseTex, uv).x;
    if(h < 0) {
        h = 0;
    }
    fragPos = vposition.xyz + vec3(0,0,h);
    gl_Position = P*V*M*vec4(vposition.x, vposition.y, vposition.z + h, 1.0);
}
)"
