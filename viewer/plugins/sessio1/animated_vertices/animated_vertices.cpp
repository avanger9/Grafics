#include "animated_vertices.h"
#include "glwidget.h"

void Animated_vertices::onPluginLoad()
{
	vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
	vs->compileSourceFile("vertex.vert");
	cout << "VS log:" << vs->log().toStdString() << endl;

	fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
	fs->compileSourceFile("fragment.frag");
	cout << "FS log:" << fs->log().toStdString() << endl;

	program = new QOpenGLShaderProgram(this);
	program->addShader(vs);
	program->addShader(fs);
	program->link();

	et.start();
	/* timers de Qt */
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), glwidget(), SLOT(updateGL()));
	timer->start();
}

void Animated_vertices::preFrame()
{
	program->bind();
	program->setUniformValue("time", float(et.elapsed()/1000.0f));
	QMatrix3x3 nm = camera()->viewMatrix().normalMatrix();
	program->setUniformValue("normalMatrix", nm); 
	QMatrix4x4 mvp = camera()->projectionMatrix()*camera()->viewMatrix();
	program->setUniformValue("modelViewProjectionMatrix", mvp);
}

void Animated_vertices::postFrame()
{
	program->release();
}
