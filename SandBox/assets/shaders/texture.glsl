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
	vec4 texColor = vec4(1.0, 1.0, 1.0, 1.0);

	switch(int(inTexIndex))
	{
		case 0:  texColor = texture(s_Textures[0], inUv * inTilingFactor); break;
		case 1:  texColor = texture(s_Textures[1], inUv * inTilingFactor); break;
		case 2:  texColor = texture(s_Textures[2], inUv * inTilingFactor); break;
		case 3:  texColor = texture(s_Textures[3], inUv * inTilingFactor); break;
		case 4:  texColor = texture(s_Textures[4], inUv * inTilingFactor); break;
		case 5:  texColor = texture(s_Textures[5], inUv * inTilingFactor); break;
		case 6:  texColor = texture(s_Textures[6], inUv * inTilingFactor); break;
		case 7:  texColor = texture(s_Textures[7], inUv * inTilingFactor); break;
		case 8:  texColor = texture(s_Textures[8], inUv * inTilingFactor); break;
		case 9:  texColor = texture(s_Textures[9], inUv * inTilingFactor); break;
		case 10: texColor = texture(s_Textures[10], inUv * inTilingFactor); break;
		case 11: texColor = texture(s_Textures[11], inUv * inTilingFactor); break;
		case 12: texColor = texture(s_Textures[12], inUv * inTilingFactor); break;
		case 13: texColor = texture(s_Textures[13], inUv * inTilingFactor); break;
		case 14: texColor = texture(s_Textures[14], inUv * inTilingFactor); break;
		case 15: texColor = texture(s_Textures[15], inUv * inTilingFactor); break;
		case 16: texColor = texture(s_Textures[16], inUv * inTilingFactor); break;
		case 17: texColor = texture(s_Textures[17], inUv * inTilingFactor); break;
		case 18: texColor = texture(s_Textures[18], inUv * inTilingFactor); break;
		case 19: texColor = texture(s_Textures[19], inUv * inTilingFactor); break;
		case 20: texColor = texture(s_Textures[20], inUv * inTilingFactor); break;
		case 21: texColor = texture(s_Textures[21], inUv * inTilingFactor); break;
		case 22: texColor = texture(s_Textures[22], inUv * inTilingFactor); break;
		case 23: texColor = texture(s_Textures[23], inUv * inTilingFactor); break;
		case 24: texColor = texture(s_Textures[24], inUv * inTilingFactor); break;
		case 25: texColor = texture(s_Textures[25], inUv * inTilingFactor); break;
		case 26: texColor = texture(s_Textures[26], inUv * inTilingFactor); break;
		case 27: texColor = texture(s_Textures[27], inUv * inTilingFactor); break;
		case 28: texColor = texture(s_Textures[28], inUv * inTilingFactor); break;
		case 29: texColor = texture(s_Textures[29], inUv * inTilingFactor); break;
		case 30: texColor = texture(s_Textures[30], inUv * inTilingFactor); break;
		case 31: texColor = texture(s_Textures[31], inUv * inTilingFactor); break;
	}
	outColor = texColor * inColor;
}