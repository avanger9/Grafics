#ifndef _MODELINFO2_H
#define _MODELINFO2_H

#include "plugin.h"
#include <QPainter>

class ModelInfo2: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

	public:
		void onPluginLoad();
		void preFrame();
		void postFrame();

	private:
		int nObjectes, nPoligons, nVertexs, nTriangles;
		float propTriangles;

		QString nobj;
		QString npol;
		QString nver;
		QString nper;

		QPainter painter;

};

#endif
