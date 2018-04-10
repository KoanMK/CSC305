R"(
#version 330 core
in vec3 vposition;
in vec2 vtexcoord;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

out vec2 uv;

void main() {
    uv = vtexcoord;
    // TODO: Calculate vertical displacement h given uv
    float h = 0;
    h = 0.05*sin(8*uv.x) + 0.05*cos(8*uv.y);
    // TODO: Apply displacement to vposition
    vec3 v = vposition + vec3(0,0,h);
    // DO THIS STEP FIRST:
    // TODO: Multiply model, view, and projection matrices in the correct order
    gl_Position = P*V*M*vec4(v, 1.0);
}
)"
