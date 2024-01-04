#pragma once

#include <vector>
#include "Math.h"

class DotObjModel
{
private:
	std::vector<Vec3f> verts_;
	std::vector<std::vector<int> > faces_;

public:
	DotObjModel(const char* filename);
	~DotObjModel();
	int nverts();
	int nfaces();
	Vec3f vert(int i);
	std::vector<int> face(int idx);
};

