#include "resaltar_teclat.h"
#include "glwidget.h"

void Resaltar_teclat::keyPressEvent(QKeyEvent *e)
{
	int key = e->key();
	if (key < (int)(Qt::Key_0) || key > (int)(Qt::Key_9)) return;
	key -= Qt::Key_0;

	if (int(scene()->objects().size()) < key) key = -1;
	scene()->setSelectedObject(key);

	glwidget()->update();
}


