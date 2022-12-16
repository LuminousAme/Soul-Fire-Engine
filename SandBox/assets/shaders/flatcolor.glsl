#type vertex
#version 420
			
layout(location = 0) in vec3 inPosition;
layout(location = 0) out vec3 outPosition;

uniform mat4 u_ViewProjection;
uniform mat4 u_Model;

void main() {
	outPosition = inPosition;
	gl_Position = u_ViewProjection * u_Model * vec4(inPosition, 1.0);
}

#type fragment
#version 420
			
layout(location = 0) in vec3 inPosition;
layout(location = 0) out vec4 outColor;
			
uniform vec4 u_color;

void main() {
	outColor = u_color;
}