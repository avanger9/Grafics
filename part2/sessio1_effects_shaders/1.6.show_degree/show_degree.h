#ifndef _SHOW_DEGREE_H
#define _SHOW_DEGREE_H

#include "plugin.h" 

class Show_degree: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

	public:
		void onPluginLoad();
		void preFrame();
		void postFrame();
		const int SIZE = 1024;

	private:
		void calcGrauMig();
		void drawRect();

		double grau_mig;

		GLuint textureID;
		QOpenGLShaderProgram* program;
		QOpenGLShader *vs, *fs;
		float m_degree;
};

#endif
