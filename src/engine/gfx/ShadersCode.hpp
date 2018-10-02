#pragma once

namespace ari
{
	const char* vsCode =
"$input a_position, a_color0 \
$output v_color0 \
void main() \
	{ \
		gl_Position = mul(u_modelViewProj, vec4(a_position, 1.0)); \
		v_color0 = a_color0; \
	} \
	";

	const char* psCode =
"$input v_color0 \
void main() \
	{ \
		gl_FragColor = v_color0; \
	} \
	";
} // ari
