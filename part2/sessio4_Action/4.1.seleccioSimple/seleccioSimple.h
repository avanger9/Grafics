#ifndef _SELECCIO_SIMPLE_H
#define _SELECCIO_SIMPLE_H

#include "plugin.h"

#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLWidget>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <vector>
#include "glwidget.h"
/*
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
*/

class SeleccioSimple : public QObject, Plugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "Plugin")   
    Q_INTERFACES(Plugin)

    public:
        void postFrame();
        void onPluginLoad();

    protected:
        virtual void keyPressEvent (QKeyEvent *event);
      
    private:
        QOpenGLShaderProgram* program;
        QOpenGLShader* vs;
        QOpenGLShader* fs;

        void creaCaixaUnitaria();
        void ompleVAO();

        float cu_xmin, cu_xmax;
        float cu_ymin, cu_ymax;
        float cu_zmin, cu_zmax;
        float ccu_x, ccu_y, ccu_z;

        GLuint VAO;
        GLuint VBO_coord, VBO_normals, VBO_indexs;

        int objSeleccionat; 

        vector<float> vertices;
        vector<float> normals;
        vector<unsigned int> indices;
};
#endif
