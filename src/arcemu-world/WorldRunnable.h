/*

 */

#pragma once

class WorldRunnable : public ThreadContext
{
public:
	WorldRunnable();
	bool run();
};
