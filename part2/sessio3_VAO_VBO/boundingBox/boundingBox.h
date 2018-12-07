#ifndef _BOUNDINGBOX_H
#define _BOUNDINGBOX_H


#include "plugin.h" 
#include <vector>

class BoundingBox: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

  public:
	 void onPluginLoad();
	 void preFrame();
	 void postFrame();

	 void onObjectAdd();
	 bool drawScene();
	 bool drawObject(int);

	 bool paintGL();

	 void keyPressEvent(QKeyEvent *);
	 void mouseMoveEvent(QMouseEvent *);

 private:
    // add private methods and attributes here

    QOpenGLShaderProgram* program;
    QOpenGLShader* vs;
    QOpenGLShader* fs;

    void createBox();
    void cleanUp();

    vector<float> vertices;
    vector<float> normals;
    vector<unsigned int> indices;
};

#endif
