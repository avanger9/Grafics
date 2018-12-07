#ifndef _RESALTAT_OBJECTE_SELECCIONAT_H
#define _RESALTAT_OBJECTE_SELECCIONAT_H

#include "plugin.h" 

class Resaltat_objecte_seleccionat: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

  public:
	 void onPluginLoad();
	 void preFrame();
	 void postFrame();
	 
  private:
	void createBuffers();
	void generate_vbo(GLuint &vbo_id, GLsizeiptr size, const GLfloat *data, GLuint 				  attribute_id, GLint attribute_size);
	void drawBoxes();

	GLuint textureID;
	QOpenGLShaderProgram* program;
	QOpenGLShader* vs;
	QOpenGLShader* fs;

	bool created;
	GLuint cubeVAO;
	GLuint verticesVBO;
	GLuint colorVBO;
};

#endif
