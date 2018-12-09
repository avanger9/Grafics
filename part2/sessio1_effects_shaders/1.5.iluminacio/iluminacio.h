#ifndef _ILUMINACIO_H
#define _ILUMINACIO_H

#include "plugin.h" 

class Iluminacio: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

  public:
	 void onPluginLoad();
	 void preFrame();
	 void postFrame();
  private:
	QOpenGLShaderProgram* program;
    QOpenGLShader *fs, *vs;
};

#endif
