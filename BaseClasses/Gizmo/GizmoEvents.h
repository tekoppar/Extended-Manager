#pragma once

#include "Tem.h"

class GizmoEvents
{
public:
	bool IsUsingGizmo = false;

	virtual void GizmoMoved(tem::Vector3 position, tem::AxisType axis) = 0;
	virtual void GizmoClicked() = 0;
	virtual void GizmoDone() = 0;
};