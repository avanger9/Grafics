#ifndef _ANIMATED_VERTICES_H
#define _ANIMATED_VERTICES_H

#include "plugin.h"
#include <QElapsedTimer>

class Animated_vertices: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

  public:
	 void onPluginLoad();
	 void preFrame();
	 void postFrame();

  private:
  	QOpenGLShaderProgram *program;
  	QOpenGLShader *fs, *vs;
  	QElapsedTimer et; 
};

#endif
