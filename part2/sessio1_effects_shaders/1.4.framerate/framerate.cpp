#include "framerate.h"
#include "glwidget.h"

void Framerate::onPluginLoad()
{
	fps = fcnt = 0;
	QTimer *frameTimer=new QTimer(this);
	connect(frameTimer, SIGNAL(timeout()), this, SLOT(updateFPS()));
	frameTimer->start(1000);
}

void Framerate::updateFPS()
{
	fps=fcnt;
	fcnt=0;
	glwidget()->update();
}


void Framerate::preFrame()
{
	
}

void Framerate::postFrame()
{
	QPainter painter;
	QFont font;
	font.setPixelSize(32);
	painter.begin(glwidget());
	painter.setFont(font);
	int x=15;
	int y=50;
	painter.drawText(x, y, QString("FPS: %1").arg(fps));
	painter.end();
	fcnt++;
}