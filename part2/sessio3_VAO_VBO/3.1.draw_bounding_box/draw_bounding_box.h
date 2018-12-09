#ifndef _DRAW_BOUNDING_BOX_H
#define _DRAW_BOUNDING_BOX_H

#include "plugin.h" 

class Draw_bounding_box: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

	public:
		void onPluginLoad();
		void postFrame();
		void onSceneClear();

	private:
		void createBuffers();

		QOpenGLShaderProgram *program;
  		QOpenGLShader *fs, *vs;

  		GLuint vao;
  		GLuint corrdBuffer;

  		vector<float> vertices;
};

#endif
