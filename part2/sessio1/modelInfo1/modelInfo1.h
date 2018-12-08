#ifndef _MODELINFO1_H
#define _MODELINFO1_Hs

#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <vector>
#include "plugin.h"
#include "glwidget.h"

class ModelInfo1 : public QObject, Plugin
{
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "Plugin")   
  Q_INTERFACES(Plugin)

  public:
  	void postFrame() Q_DECL_OVERRIDE;
    void onPluginLoad() Q_DECL_OVERRIDE;
    
  private:
  
};
#endif
