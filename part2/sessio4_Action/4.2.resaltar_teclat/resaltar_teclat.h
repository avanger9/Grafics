#ifndef _RESALTAR_TECLAT_H
#define _RESALTAR_TECLAT_H

#include "plugin.h" 

class Resaltar_teclat: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

	public:
		void keyPressEvent(QKeyEvent *);
	private:

};

#endif
