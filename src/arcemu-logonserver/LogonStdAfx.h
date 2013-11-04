/*

*/

#pragma once

#include <list>
#include <vector>
#include <map>
#include <sstream>
#include <string>
//#include <fstream>

#include "Common.h"
#include <Network/Network.h>

#include "../arcemu-shared/Log.h"
#include "../arcemu-shared/Util.h"
#include "../arcemu-shared/ByteBuffer.h"
#include "../arcemu-shared/Config/ConfigEnv.h"
#include <zlib.h>

#include "../arcemu-shared/Database/DatabaseEnv.h"
#include "../arcemu-shared/Database/DBCStores.h"
#include "../arcemu-shared/Database/dbcfile.h"

#include "../arcemu-shared/Auth/BigNumber.h"
#include "../arcemu-shared/Auth/Sha1.h"
#include "../arcemu-shared/Auth/WowCrypt.h"
#include "../arcemu-shared/CrashHandler.h"

#include "LogonOpcodes.h"
#include "../arcemu-logonserver/Main.h"
#include "../arcemu-world/NameTables.h"
#include "AccountCache.h"
#include "PeriodicFunctionCall_Thread.h"
#include "../arcemu-logonserver/AutoPatcher.h"
#include "../arcemu-logonserver/AuthSocket.h"
#include "../arcemu-logonserver/AuthStructs.h"
#include "../arcemu-logonserver/LogonOpcodes.h"
#include "../arcemu-logonserver/LogonCommServer.h"
#include "../arcemu-logonserver/LogonConsole.h"
#include "../arcemu-shared/WorldPacket.h"

// database decl
extern Database* sLogonSQL;
