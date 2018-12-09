#ifndef _RESALTAR_RATOLI_H
#define _RESALTAR_RATOLI_H

#include "plugin.h" 

class Resaltar_ratoli: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

	private:
		int     pxClick, pyClick;
		int     m_size;

		GLuint m_VAO;           // IDs of VAOs
		GLuint m_coordBufferID; // ID of vertex coordinates buffer

		QOpenGLShader *vs, *fs;
		QOpenGLShaderProgram *program;

		void encodeID(uint ID, GLubyte *color);
		uint decodeID(GLubyte *color);

		void cleanUp();
	public:
	    inline      ~Resaltar_ratoli() { cleanUp(); }
	    
	    void        onPluginLoad();
	    inline void onSceneClear() { cleanUp(); }
	    
	    void        mousePressEvent ( QMouseEvent * event );
};

#endif
