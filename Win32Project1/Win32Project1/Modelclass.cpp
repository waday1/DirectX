#include"Modelclass.h"

ModelClass::ModelClass()
{
	m_vertexBuffer = 0;
	m_indexBuffer = 0;

	m_Texture = 0;
}

ModelClass::ModelClass(const ModelClass&other)
{

}

ModelClass::~ModelClass()
{

}

bool ModelClass::Initialize(ID3D11Device*device, ID3D11DeviceContext* deviceContext, char* textureFilename)
{
	bool result;

	result = InitializeBuffers(device);
	if (!result)
	{
		return false;
	}

	result = LoadTexture(device, deviceContext, textureFilename);
	if (!result)
	{
		return false;
	}

	return true;
}

void ModelClass::Shutdown()
{
	ReleaseTexture();

	ShutdownBuffers();

	return;
}

void ModelClass::Render(ID3D11DeviceContext* deviceContext)
{
	RenderBuffers(deviceContext);

	return;
}

int ModelClass::GetIndexCount()
{
	return m_indexCount;
}

ID3D11ShaderResourceView*ModelClass::GetTexture()
{
	return m_Texture->GetTexture();
}

bool ModelClass::InitializeBuffers(ID3D11Device*device)
{
	VertexType*vertices;
	unsigned long*indices;
	D3D11_BUFFER_DESC vertexBufferDecs, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	//�O�p�`�\��
	m_vertexCount=6;
	m_indexCount = 6;

	//�܊p�`�\��
  /*m_vertexCount=5;
	m_indexCount = 5;*/

	vertices = new VertexType[m_vertexCount];
	if (!vertices)
	{
		return false;
	}

	indices = new unsigned long[m_indexCount];
	if (!indices)
	{
		return false;
	}


	//�|�C���g��`�悷��ɂ́A���v���̏����Ń|�C���g���쐬���܂��B
	vertices[0].position = XMFLOAT3(-1.0f, 1.0f, 0.0f);
	vertices[0].texture = XMFLOAT2(0.0f, 0.0f);

	vertices[1].position = XMFLOAT3(1.0f, -1.0f, 0.0f);
	vertices[1].texture = XMFLOAT2(1.0f, 1.0f);

	vertices[2].position = XMFLOAT3(-1.0f, -1.0f, 0.0f);
	vertices[2].texture = XMFLOAT2( 0.0f, 1.0f);

	vertices[3].position = XMFLOAT3(-1.0f, 1.0f, 0.0f);
	vertices[3].texture = XMFLOAT2(0.0f, 0.0f);

	vertices[4].position = XMFLOAT3(1.0f, 1.0f, 0.0f);
	vertices[4].texture = XMFLOAT2(1.0f, 0.0f);

	vertices[5].position = XMFLOAT3(1.0f, -1.0f, 0.0f);
	vertices[5].texture = XMFLOAT2(1.0f, 1.0f);

	/*
	vertices[3].position = XMFLOAT3(1.0f, -1.0f, 0.0f);
	vertices[3].color = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);

	vertices[4].position = XMFLOAT3(-1.0f, -1.0f, 0.0f);
	vertices[4].color = XMFLOAT4(1.0f, 1.0f,1.0f, 1.0f);*/


	indices[0] = 0;// �����B
	indices[1] = 1;//�����B
	indices[2] = 2;// �E��B
	indices[3] = 3;// �����B
	indices[4] = 4;//�����B
	indices[5] = 5;// �E��B
	//indices[3] = 3;// �E���B
	//indices[4] = 4;// �E���B


	vertexBufferDecs.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDecs.ByteWidth = sizeof(VertexType)*m_vertexCount;
	vertexBufferDecs.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDecs.CPUAccessFlags = 0;
	vertexBufferDecs.MiscFlags = 0;
	vertexBufferDecs.StructureByteStride = 0;

	vertexData.pSysMem = vertices;
	vertexData.SysMemSlicePitch = 0;
	vertexData.SysMemSlicePitch = 0;

	result = device->CreateBuffer(&vertexBufferDecs, &vertexData, &m_vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long)*m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if (FAILED(result))
	{
		return false;
	}


	delete[]vertices;
	vertices = 0;

	delete[]indices;
	indices = 0;

	return true;
}

void ModelClass::ShutdownBuffers()
{
	if (m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}

	return;
}

void ModelClass::RenderBuffers(ID3D11DeviceContext*deviceContext)
{
	unsigned int stride;
	unsigned int offset;

	stride = sizeof(VertexType);
	offset = 0;

	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	//�O�p�`�̏ꍇ�͂�����
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//���̂ق����p�`�̏ꍇ�͂�����
	//deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	return;
}

bool ModelClass::LoadTexture(ID3D11Device*device, ID3D11DeviceContext*deviceContext, char* filename)
{
	bool result;

	m_Texture = new TextureClass;
	if (!m_Texture)
	{
		return false;
	}


	result = m_Texture->Initialize(device, deviceContext, filename);
	if (!result)
	{
		return false;
	}

	return true;
}

void ModelClass::ReleaseTexture()
{
	if (m_Texture)
	{
		m_Texture->Shutdown();
		delete m_Texture;
		m_Texture = 0;
	}

	return;
}