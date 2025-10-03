#include "EventStep.h"

df::EventStep::EventStep()
{
	setType(STEP_EVENT);
	setStepCount(0);
}

df::EventStep::EventStep(int init_step_count)
{
	setType(STEP_EVENT);
	setStepCount(init_step_count);
}

void df::EventStep::setStepCount(int new_step_count)
{
	m_step_count = new_step_count;
}

int df::EventStep::getStepCount() const {
	return m_step_count;
}