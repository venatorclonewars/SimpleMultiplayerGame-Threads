#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "math.h"
#include "baseTerrain.h"
#include "3DOBjects/cube.h"
#include "3DOBjects/lightweightCube.h"
#include "3DOBjects/plane.h"
#include "game.h"
#include <enet/enet.h>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>

class InternetPacket
{
	vector<Cube*> staticObjects;

	void addPacketData(Cube* cube)
	{
		staticObjects.push_back(cube);
	}
};

class Game
{
public:
	Game();
	~Game();

	void run();
	static void renderScene();

	void initializeBulletPhysics();
	// Terrain stuff
	void initTerrainTextureGenerator();

	void setEnet();
	void runEnet();
	void sendPacketCube(ENetPeer* peer, const char* data);
	const char* encodeInternetData(Vector3f* _data);
	void decodeInternetData(const char* data);

	// Freeglut stuff
    static void displayNewFrame(int deltaTime);  
    static void keyboardListener(unsigned char key, int mouse_x, int mouse_y);
	static void specialKeyboardListener(int key, int mouse_x, int mouse_y);
	static void mouseListener(int x, int y);
	static void glutCallbacks();

	vector<Cube*> getInternetData();
	
	InternetPacket* packet = new InternetPacket();

};

