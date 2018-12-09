#ifndef _DRAW_SMOOTH_H
#define _DRAW_SMOOTH_H

#include "plugin.h" 

class Draw_smooth: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

	public:

		void onPluginLoad();
		void onObjectAdd();
		void onSceneClear();
		bool drawScene();
		bool drawObject(int);

	private:

		void cleanUp();
		void addVBO(unsigned int currentObject);

		vector<GLuint> VAOs;          // ID of VAOs
		vector<GLuint> coordBuffers;  // ID of vertex coordinates buffer 
		vector<GLuint> normalBuffers; // ID of normal components buffer 
		vector<GLuint> stBuffers;     // ID of (s,t) buffer 
		vector<GLuint> colorBuffers;  // ID of color buffer  
		vector<GLuint> indexBuffers;  // ID of index buffer
		vector<GLuint> numIndices;    // Size (number of indices) in each index buffer

};

#endif
