/*
 * Arc MMORPG Server
 * Copyright (C) 2005-2010 Arc Team <http://www.arcemulator.net/>
 *
 * This software is  under the terms of the EULA License
 * All title, including but not limited to copyrights, in and to the ArcNG Software
 * and any copies there of are owned by ZEDCLANS INC. or its suppliers. All title
 * and intellectual property rights in and to the content which may be accessed through
 * use of the ArcNG is the property of the respective content owner and may be protected
 * by applicable copyright or other intellectual property laws and treaties. This EULA grants
 * you no rights to use such content. All rights not expressly granted are reserved by ZEDCLANS INC.
 *
 */

#ifndef __CConsole_LIB
#define __CConsole_LIB

#include "Common.h"

class ConsoleThread : public ThreadContext
{
protected:
	bool m_isRunning;
public:
	void terminate();
	bool run();
};

#endif
