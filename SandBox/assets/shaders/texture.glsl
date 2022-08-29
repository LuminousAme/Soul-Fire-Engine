#type vertex
#version 420
			
layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inUv;
layout(location = 0) out vec3 outPosition;
layout(location = 1) out vec2 outUv;

uniform mat4 u_ViewProjection;
uniform mat4 u_Model;

void main() {
	outUv = inUv;
	outPosition = inPosition;
	gl_Position = u_ViewProjection * u_Model * vec4(inPosition, 1.0);
}

#type fragment
#version 420
			
layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inUv;
layout(location = 0) out vec4 outColor;
			
layout(binding = 0) uniform sampler2D s_Texture;

void main() {
	outColor = texture(s_Texture, inUv);
}