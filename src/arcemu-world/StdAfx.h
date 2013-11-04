/*

 */

#pragma once

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

#define _GAME

#include <list>
#include <vector>
#include <map>
#include <sstream>
#include <string>
//#include <fstream>

#include "../arcemu-shared/AuthCodes.h"
#include "../arcemu-shared/Common.h"
#include "../arcemu-shared/MersenneTwister.h"
#include "../arcemu-shared/WorldPacket.h"
#include "../arcemu-shared/Log.h"
#include "../arcemu-shared/NGLog.h"
#include "../arcemu-shared/ByteBuffer.h"
#include "../arcemu-shared/StackBuffer.h"
#include "../arcemu-shared/Config/ConfigEnv.h"
#include "../arcemu-shared/crc32.h"
#include "../arcemu-shared/LocationVector.h"
#include "../arcemu-shared/hashmap.h"

#include "../arcemu-shared/Collision/vmap/IVMapManager.h"
#include "../arcemu-shared/Collision/vmap/VMapManager.h"

#include <zlib.h>

#include "../arcemu-shared/Database/DatabaseEnv.h"
#include "../arcemu-shared/Database/DBCStores.h"
#include "../arcemu-shared/Database/dbcfile.h"

#include <Network/Network.h>

#include "../arcemu-shared/Auth/MD5.h"
#include "../arcemu-shared/Auth/BigNumber.h"
#include "../arcemu-shared/Auth/Sha1.h"
#include "../arcemu-shared/Auth/WowCrypt.h"
#include "../arcemu-shared/CrashHandler.h"
#include "../arcemu-shared/FastQueue.h"
#include "../arcemu-shared/CircularQueue.h"
#include "../arcemu-shared/Threading/RWLock.h"
#include "../arcemu-shared/Threading/Condition.h"
#include "../arcemu-shared/arcemu_getopt.h"
#include "../arcemu-shared/BufferPool.h"

#include "Const.h"
#include "NameTables.h"
#include "UpdateFields.h"
#include "UpdateMask.h"
#include "Opcodes.h"
#include "WorldStates.h"

#ifdef CLUSTERING
	#include "../arcemu-logonserver/WorkerOpcodes.h"
#endif

#include "Packets.h"

#include "../arcemu-shared/CallBack.h"
#include "WordFilter.h"
#include "EventMgr.h"
#include "EventableObject.h"
#include "Object.h"
#include "LootMgr.h"
#include "Unit.h"

//#include "../arcemu-shared/arcemuConfig.h"

#include "AddonMgr.h"
#include "AIInterface.h"
#include "AreaTrigger.h"
#include "BattlegroundMgr.h"
#include "AlteracValley.h"
#include "ArathiBasin.h"
#include "EyeOfTheStorm.h"
#include "Arenas.h"
#include "CellHandler.h"
#include "Chat.h"
#include "Corpse.h"
#include "Quest.h"
#include "QuestMgr.h"
#include "Creature.h"
#include "DynamicObject.h"
#include "GameObject.h"
#include "Group.h"
#include "Guild.h"
#include "HonorHandler.h"
#include "ItemPrototype.h"
#include "Item.h"
#include "Container.h"
#include "AuctionHouse.h"
#include "AuctionMgr.h"
#include "LfgMgr.h"
#include "MailSystem.h"
#include "Map.h"
#include "MapCell.h"
#include "TerrainMgr.h"
#include "MiscHandler.h"
#include "NPCHandler.h"
#include "Pet.h"
#include "WorldSocket.h"
#include "World.h"
#include "WorldSession.h"
#include "WorldStateManager.h"
#include "MapMgr.h"
#include "MapScriptInterface.h"
#include "WintergraspInternal.h"
#include "Wintergrasp.h"
#include "Player.h"
#include "faction.h"
#include "Skill.h"
#include "SkillNameMgr.h"
#include "SpellNameHashes.h"
#include "SpellDefines.h"
#include "Spell.h"
#include "SpellAuras.h"
#include "TaxiMgr.h"
#include "TransporterHandler.h"
#include "WarsongGulch.h"
#include "WeatherMgr.h"
#include "ItemInterface.h"
#include "Stats.h"
#include "ObjectMgr.h"
#include "GuildDefines.h"
#include "WorldCreator.h"
#include "ScriptMgr.h"
#include "Channel.h"
#include "ChannelMgr.h"
#include "ArenaTeam.h"
#include "LogonCommClient.h"
#include "LogonCommHandler.h"
#include "MainServerDefines.h"
#include "WorldRunnable.h"
#include "../arcemu-shared/Storage.h"
#include "ObjectStorage.h"
#include "DayWatcherThread.h"
#include "Vehicle.h"
#include "AchievementInterface.h"
#include "AchievementDefines.h"
#include "ChainAggroEntity.h"
#include "StrandOfTheAncients.h"
#include "IsleOfConquest.h"
#include "Wintergrasp.h"

#ifdef CLUSTERING
	#include "WorkerServerClient.h"
	#include "ClusterInterface.h"
#endif

#include "CollideInterface.h"

#include "Master.h"
#include "BaseConsole.h"

