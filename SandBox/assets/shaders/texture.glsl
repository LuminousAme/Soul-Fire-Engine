#type vertex
#version 420
			
layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec4 inColor;
layout(location = 2) in vec2 inUv;
layout(location = 3) in float inTexIndex;
layout(location = 4) in float inTilingFactor;
layout(location = 0) out vec3 outPosition;
layout(location = 1) out vec4 outColor;
layout(location = 2) out vec2 outUv;
layout(location = 3) out float outTextIndex;
layout(location = 4) out float outTilingFactor;

uniform mat4 u_ViewProjection;

void main() {
	outColor = inColor;
	outUv = inUv;
	outTextIndex = inTexIndex;
	outTilingFactor = inTilingFactor;
	outPosition = inPosition;
	gl_Position = u_ViewProjection * vec4(inPosition, 1.0);
}

#type fragment
#version 420
			
layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec4 inColor;
layout(location = 2) in vec2 inUv;
layout(location = 3) in float inTexIndex;
layout(location = 4) in float inTilingFactor;
layout(location = 0) out vec4 outColor;
			
layout(binding = 0) uniform sampler2D s_Textures[32];

void main() {
	int index = int(inTexIndex);
	outColor = texture(s_Textures[index], inUv * inTilingFactor) * inColor;
}