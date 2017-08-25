cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

struct VertexInputType
{
	float4 position:POSITION;
	float4 color:COLOR;
};

struct PixelInputType
{
	float4 position:SV_POSITION;
	float4 color:COLOR;
}

PixelInputType ColorVertexShader(VertexInputType input)
{
	PixelInputType output;

	input.position.w=1.0f;

	output.position=mu(input.position,worldMatrix);
	output.position=mu(input.position,viewMatrix);
	output.position=mu(input.position,projectionMatrix);

	output.color=input.color;

	return output;
}