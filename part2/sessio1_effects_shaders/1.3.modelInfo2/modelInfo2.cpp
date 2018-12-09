#include "modelInfo2.h"
#include "glwidget.h"

void ModelInfo2::onPluginLoad()
{
	glwidget()->makeCurrent();
    nObjectes    = 0;
    nPoligons    = 0;
    nVertexs     = 0;
    nTriangles   = 0;

    // tractament de l'escena
    Scene* scn = scene();
    nObjectes  = scn->objects().size();
    for (int i = 0; i < nObjectes; i++){
        Object& obj = scn->objects()[i];
        int nPolObj = obj.faces().size();
        nPoligons   = nPoligons + nPolObj;
        for (int j = 0; j < nPolObj; j++){ 
            Face cara     = obj.faces()[j];
            int nVertices = cara.numVertices();
            nVertexs      = nVertexs + nVertices;
            if (nVertexs == 3) nTriangles = nTriangles + 1;
        }
    }
    propTriangles = nTriangles / nPoligons * 200;
}

void ModelInfo2::preFrame()
{
	
}

void ModelInfo2::postFrame()
{
	QFont f;
	f.setPixelSize(32);
	painter.begin(glwidget());
	painter.setFont(f);
	int x = 15; int y = 40;
	painter.drawText(x, y-10, nobj.arg(nObjectes));
	painter.drawText(x, y+10, npol.arg(nPoligons));
	painter.drawText(x, y+20, nver.arg(nVertexs));
	painter.drawText(x, y+30, nper.arg(propTriangles));
	painter.end();
}
