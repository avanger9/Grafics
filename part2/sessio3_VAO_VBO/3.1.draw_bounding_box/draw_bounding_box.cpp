#include "draw_bounding_box.h"
#include "glwidget.h"

void Draw_bounding_box::onPluginLoad()
{

	vertices = {
		1, 1, 1,
	    0, 1, 1,
	    1, 0, 1,
	    0, 0, 1,
	    1, 0, 0,
	    0, 0, 0,
	    1, 1, 0,
	    0, 1, 0,
	    1, 1, 1,
	    0, 1, 1,
	    0, 1, 1,
	    0, 1, 0,
	    0, 0, 1,
	    0, 0, 0,
	    1, 0, 1,
	    1, 0, 0,
	    1, 1, 1,
	    1, 1, 0
	};

	GLWidget &g = *glwidget();
	g.glGenVertexArrays(1, &vao);
	g.glBindVertexArray(vao);

	g.glGenBuffers(1, &corrdBuffer);
	g.glBindBuffer(GL_ARRAY_BUFFER, corrdBuffer);
	g.glBufferData(GL_ARRAY_BUFFER, sizeof(float)*vertices.size(), &vertices[0], GL_STATIC_DRAW);
	g.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	g.glEnableVertexAttribArray(0);

	vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
	vs->compileSourceFile("draw_bounding_box.vert");
	//cout << "VS log:" << vs->log().toStdString() << endl;

	fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
	fs->compileSourceFile("draw_bounding_box.frag");
	//cout << "FS log:" << fs->log().toStdString() << endl;

	program = new QOpenGLShaderProgram(this);
	program->addShader(vs);
	program->addShader(fs);
	program->link();
}
void Draw_bounding_box::postFrame()
{
	glEnable(GL_BLEND);
	program->bind();

	QMatrix4x4 mvp = camera()->projectionMatrix() * camera()->viewMatrix();
	program->setUniformValue("modelViewProjectionMatrix", mvp);

	vector<Object> &obj = scene()->objects();
	for (Object &o : obj) {
		const Box &b = o.boundingBox();
		program->setUniformValue("boundingBoxMax", b.max());
		program->setUniformValue("boundingBoxMin", b.min());

		glDrawArrays(GL_TRIANGLES, 0, vertices.size());
	}
	program->release();
	glDisable(GL_BLEND);
}

void Draw_bounding_box::onSceneClear()
{
	delete vs;
	delete fs;
	delete program;
	GLWidget &g = *glwidget();
	g.glDeleteBuffers(1,  corrdBuffer);
//	g.glDeleteBuffers(normalBuffers.size(), &normalBuffers[0]);
//	g.glDeleteBuffers(stBuffers.size(),  &stBuffers[0]);
//	g.glDeleteBuffers(colorBuffers.size(),  &colorBuffers[0]);
//	g.glDeleteVertexArrays(VAOs.size(), &VAOs[0]);
}