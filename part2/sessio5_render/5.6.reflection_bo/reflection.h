#ifndef _REFLECTION_H
#define _REFLECTION_H

#include "plugin.h" 

class Reflection: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)
	
	public:
		void onPluginLoad();
		bool paintGL();
		void resizeEvent(QResizeEvent *e);

	private:
		QOpenGLShaderProgram* program;
		QOpenGLShader* vs;
		QOpenGLShader* fs;  
		GLuint textureId;

		void drawQuad(const Point& p0, const Point& p1, const Point& p2, const Point& p3);
};

#endif
