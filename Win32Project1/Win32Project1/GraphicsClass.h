
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_

#include "D3dclass.h"
#include"Cameraclass.h"
#include"Modelclass.h"

#include"Lightshaderclass.h"
#include"Lightclass.h"

#include<Windows.h>

const bool FULL_SCREEN = true;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;
class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame();

private:
	bool Render(float);

private:
	D3DClass* m_Direct3D;
	CameraClass*m_Camera;
	ModelClass*m_Model;

	LightShaderClass* m_LightShader;
	LightClass* m_Light;

};

#endif