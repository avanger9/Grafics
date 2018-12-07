#include "draw_smooth.h"
#include "glwidget.h"
#include <cmath>

void draw_smooth::cleanUp() {
	glDeleteBuffers(coordBuffers.size(),  &coordBuffers[0]);
	glDeleteBuffers(normalBuffers.size(), &normalBuffers[0]);
	glDeleteBuffers(indexBuffers.size(),  &indexBuffers[0]);
	glDeleteBuffers(stBuffers.size(),  &stBuffers[0]);
	glDeleteBuffers(colorBuffers.size(),  &colorBuffers[0]);

	glDeleteVertexArrays(VAOs.size(), &VAOs[0]);

	coordBuffers.clear();
	normalBuffers.clear();
	indexBuffers.clear();
	stBuffers.clear();
	colorBuffers.clear();
	VAOs.clear();

	numIndices.clear(); 
}

void draw_smooth::onSceneClear() {
	cleanUp();
}


void Draw_smooth::onPluginLoad()
{
	
}

void Draw_smooth::preFrame()
{
	
}

void Draw_smooth::postFrame()
{
	
}

void Draw_smooth::onObjectAdd()
{
	
}

bool Draw_smooth::drawScene()
{
	return false; // return true only if implemented
}

bool Draw_smooth::drawObject(int)
{
	return false; // return true only if implemented
}

