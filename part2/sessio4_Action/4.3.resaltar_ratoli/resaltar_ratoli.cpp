#include "resaltar_ratoli.h"
#include "glwidget.h"

void Resaltar_ratoli::onPluginLoad()
{
	vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
	vs->compileSourceFile("vertex.vert");

	fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
	fs->compileSourceFile("fragment.frag");

	program = new QOpenGLShaderProgram(this);
	program->addShader(vs);
	program->addShader(fs);
	program->link();
}


void Resaltar_ratoli::mousePressEvent(QMouseEvent *e)
{
	if (! (e->button() & Qt::RightButton)) return;
	if ( e->modifiers() & (Qt::ShiftModifier)) return;
	if (! (e->modifiers() & Qt::ControlModifier)) return;

	glClearColor(0,0,0,0);
	glClear(GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT);

	program->bind();
	const vector<Object> &objs = scene()->objects();
	for (uint i = 0; i < objs.size(); ++i) {
		GLubyte color[3];
		encodeID(i,color);
		program->setUniformValue("modelViewProjectionMatrix", camera()->projectionMatrix()*camera()->viewMatrix());
		program->setUniformValue("color", QVector4D(color[0]/255.0, color[1]/255., color[2]/255., 1.0));
		drawPlugin()->drawObject(i);
	}
	program->release();

	int x = e->x();
	int y = glwidget()->height() - e->y();
	GLubyte read[4];
	glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, read);
	int ID = decodeID(read);

	cout << "ID1: " << ID << endl;

	scene()->setSelectedObject(ID);

	glwidget()->update();
}

void Resaltar_ratoli::encodeID(uint ID, GLubyte *color)
{
	ID += 1;
	color[0] = ID & 0xFF;
	color[1] = (ID >> 8) & 0xFF;
	color[2] = (ID >> 16) & 0xFF;
}

uint Resaltar_ratoli::decodeID(GLubyte *color)
{
	int ID = color[0] | (color[1] << 8) | (color[2] << 16);
	return ID - 1;
}

void Resaltar_ratoli::cleanUp()
{
	GLWidget &g = *glwidget();
	g.glDeleteBuffers(m_size, &m_coordBufferID);
	g.glDeleteVertexArrays(1, &m_VAO);
  
  delete program;
  delete vs;
  delete fs;
}
