/*
 */

#include "StdAfx.h"
#include "Setup.h"
#define SKIP_ALLOCATOR_SHARING 1
#include <ScriptSetup.h>

extern "C" SCRIPT_DECL uint32 _exp_get_script_type()
{
	return SCRIPT_TYPE_MISC;
}

extern "C" SCRIPT_DECL void _exp_script_register(ScriptMgr* mgr)
{
//	###		Classes Quests	###
	//SetupDruid(mgr);
	SetupMage(mgr);
	SetupPaladin(mgr);
	SetupWarrior(mgr);

//	###		Proffessions Quests	###
	SetupFirstAid(mgr);

//	###		Zones Quests	###
	SetupArathiHighlands(mgr);
	SetupAzshara(mgr);
	SetupAzuremystIsle(mgr);
	SetupBladeEdgeMountains(mgr);
	SetupBlastedLands(mgr);
	SetupBloodmystIsle(mgr);
	//SetupDarkshore(mgr);
	SetupDeathKnight(mgr);
	SetupDesolace(mgr);
	SetupDragonblight(mgr);
	SetupDuskwood(mgr);
	SetupDustwallowMarsh(mgr);
	SetupEasternPlaguelands(mgr);
	SetupEversongWoods(mgr);
	SetupGhostlands(mgr);
	SetupHellfirePeninsula(mgr);
	SetupHillsbradFoothills(mgr);
	SetupHowlingFjord(mgr);
	SetupIsleOfQuelDanas(mgr);
	SetupLochModan(mgr);
	SetupMulgore(mgr);
	SetupNagrand(mgr);
	SetupNetherstorm(mgr);
	SetupOldHillsbrad(mgr);
	SetupRedrigeMountains(mgr);
	SetupShadowmoon(mgr);
	SetupSilvermoonCity(mgr);
	SetupSilverpineForest(mgr);
	SetupStormwind(mgr);
	SetupStranglethornVale(mgr);
	SetupTanaris(mgr);
	SetupTeldrassil(mgr);
	SetupTerrokarForest(mgr);
	SetupThousandNeedles(mgr);
	SetupTirisfalGlades(mgr);
	SetupUndercity(mgr);
	SetupUnGoro(mgr);
	SetupWestfall(mgr);
	SetupZangarmarsh(mgr);
	SetupBarrens(mgr);
	SetupSholazarBasin(mgr);
//	###		Misc		###
//	SetupQuestGossip(mgr);
//	SetupQuestHooks(mgr);
//	SetupUnsorted(mgr);
}

#ifdef WIN32

BOOL APIENTRY DllMain( HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved )
{
    return TRUE;
}

#endif
