#version 460 core

layout(location = 0) uniform sampler2D u_texture;

in vec2 uv;

layout(location = 0) out vec4 out_color;

void main() {
    out_color = texture(u_texture, uv);
    out_color.rgb = mix(vec3(1.0), out_color.rgb, out_color.a);
}