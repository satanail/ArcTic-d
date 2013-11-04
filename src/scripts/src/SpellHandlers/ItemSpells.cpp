/*
 */

#include "StdAfx.h"
#include "Setup.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////
// How to add a new item spell to the dummy spell handler:
//
// 1) Add a new function to handle the spell at the end of this file but before the
//   SetupItemSpells() function. SetupItemSpells() must always be the last function.
//
// 2) Register the dummy spell by adding a new line to the end of the list in the
//   SetupItemSpells() function.
//
// Please look at how the other spells are handled and try to use the
// same variable names and formatting style in your new spell handler.
///////////////////////////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------

bool GnomishTransporter(uint32 i, Spell *pSpell)
{
	if(!pSpell->p_caster) return true;

	pSpell->p_caster->EventAttackStop();
	pSpell->p_caster->SafeTeleport(1, 0, LocationVector(-7169.41f, -3838.63f, 8.72f));
	return true;
}

// -----------------------------------------------------------------------------

bool NoggenFoggerElixr(uint32 i, Spell *pSpell)
{
	if(!pSpell->p_caster) return true;

	uint32 chance = RandomUInt(2);

	switch(chance)
	{
	case 0:
		pSpell->p_caster->CastSpell(pSpell->p_caster, dbcSpell.LookupEntry(16591), true);
		break;
	case 1:
		pSpell->p_caster->CastSpell(pSpell->p_caster, dbcSpell.LookupEntry(16593), true);
		break;
	case 2:
		pSpell->p_caster->CastSpell(pSpell->p_caster, dbcSpell.LookupEntry(16595), true);
		break;
	}
	return true;
}

// -----------------------------------------------------------------------------

bool HallowsEndCandy(uint32 i, Spell *pSpell)
{
	if(!pSpell->p_caster) return true;

	int newspell = 24924 + RandomUInt(3);

	SpellEntry *spInfo = dbcSpell.LookupEntry(newspell);
	if(!spInfo) return true;

	pSpell->p_caster->CastSpell(pSpell->p_caster, spInfo, true);
	return true;
}

// -----------------------------------------------------------------------------

bool DeviateFish(uint32 i, Spell *pSpell)
{
	if(!pSpell->p_caster) return true;

	int newspell = 8064 + RandomUInt(4);

	SpellEntry *spInfo = dbcSpell.LookupEntry(newspell);
	if(!spInfo) return true;

	pSpell->p_caster->CastSpell(pSpell->p_caster, spInfo, true);
	return true;
}

// -----------------------------------------------------------------------------

bool CookedDeviateFish(uint32 i, Spell *pSpell)
{
	if(!pSpell->p_caster) return true;

	int chance = 0;
	int newspell = 0;

	chance = RandomUInt(1);

	switch(chance)
	{
	case 0:
		newspell = 8219; // Flip Out (60 min) (turns you into a ninja)
		break;
	case 1:
		newspell = 8221; // Yaaarrrr (60 min) (turns you into a pirate)
		break;
	}

	if(newspell)
	{
		SpellEntry *spInfo = dbcSpell.LookupEntry(newspell);
		if(!spInfo) return true;

		pSpell->p_caster->CastSpell(pSpell->p_caster, spInfo, true);
	}
	return true;
}

// -----------------------------------------------------------------------------

bool HolidayCheer(uint32 i, Spell *pSpell)
{
	if(!pSpell->m_caster) return true;

	Unit *target;
	float dist = pSpell->GetDBCCastTime(i);

	for(ObjectSet::iterator itr = pSpell->m_caster->GetInRangeSetBegin(); itr != pSpell->m_caster->GetInRangeSetEnd(); ++itr)
	{
		if((*itr)->IsUnit())
			target = TO_UNIT(*itr);
		else
			continue;

		if(pSpell->m_caster->CalcDistance(target) > dist || isAttackable(pSpell->m_caster, target))
			continue;

		target->Emote(EMOTE_ONESHOT_LAUGH);
	}
	return true;
}

// -----------------------------------------------------------------------------

bool NetOMatic(uint32 i, Spell *pSpell)
{
	Unit *target = pSpell->GetUnitTarget();
	if(!pSpell->p_caster || !target) return true;

	SpellEntry *spInfo = dbcSpell.LookupEntry(13099);
	if(!spInfo) return true;

	int chance = RandomUInt(99)+1;

	if(chance < 51) // nets target: 50%
		pSpell->p_caster->CastSpell(target, spInfo, true);

	else if(chance < 76) // nets you instead: 25%
		pSpell->p_caster->CastSpell(pSpell->p_caster, spInfo, true);

	else // nets you and target: 25%
	{
		pSpell->p_caster->CastSpell(pSpell->p_caster, spInfo, true);
		pSpell->p_caster->CastSpell(target, spInfo, true);
	}
	return true;
}

// -----------------------------------------------------------------------------

bool BanishExile(uint32 i, Spell *pSpell)
{
	Unit * target = pSpell->GetUnitTarget();
	if(!pSpell->p_caster || !target) return true;

	pSpell->p_caster->SpellNonMeleeDamageLog(target, pSpell->m_spellInfo->Id, target->GetUInt32Value(UNIT_FIELD_HEALTH), true);
	return true;
}

// -----------------------------------------------------------------------------

bool ForemansBlackjack(uint32 i, Spell *pSpell)
{
	Unit * target = pSpell->GetUnitTarget();
	if(!pSpell->p_caster || !target || target->GetTypeId() != TYPEID_UNIT) 
		return true;
	
	// check to see that we have the correct creature
	Creature *c_target = TO_CREATURE(target);
	if(!c_target || c_target->GetEntry() != 10556 || !c_target->HasAura(18795)) 
		return true;

	// Start moving again
	if(target->GetAIInterface())
		target->GetAIInterface()->StopMovement(0);

	// Remove Zzz aura
	c_target->RemoveAllAuras();

	// send chat message
	char msg[100];
	sprintf(msg, "Ow! Ok, I'll get back to work, %s", pSpell->p_caster->GetName());
	target->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, msg);

	// Increment the quest log
	sQuestMgr.OnPlayerKill( pSpell->p_caster, c_target );

	// Add timed event to return lazy peon to Zzz after 5-10 minutes (spell 18795)
	SpellEntry * pSpellEntry = dbcSpell.LookupEntry(18795);
	sEventMgr.AddEvent( target ,&Unit::EventCastSpell , target , pSpellEntry , EVENT_UNK, 300000 + RandomUInt( 300000 ) , 1, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT );

	return true;
}

// -----------------------------------------------------------------------------

bool NetherWraithBeacon(uint32 i, Spell *pSpell)
{
	if(!pSpell->p_caster) return true;

	float SSX = pSpell->p_caster->GetPositionX();
	float SSY = pSpell->p_caster->GetPositionY();
	float SSZ = pSpell->p_caster->GetPositionZ();
	float SSO = pSpell->p_caster->GetOrientation();

	pSpell->p_caster->GetMapMgr()->GetInterface()->SpawnCreature(22408, SSX, SSY, SSZ, SSO, true, false, 0, 0);
	return true;
}

// -----------------------------------------------------------------------------

bool SymbolOfLife(uint32 i, Spell *pSpell)
{
	return true;
}

// -----------------------------------------------------------------------------

bool NighInvulnBelt(uint32 i, Spell *pSpell)
{
	if(!pSpell->p_caster) return true;

	int chance = RandomUInt(99)+1;

	if(chance > 10) // Buff - Nigh-Invulnerability - 30456
		pSpell->p_caster->CastSpell(pSpell->p_caster, dbcSpell.LookupEntry(30456), true);
	else // Malfunction - Complete Vulnerability - 30457
		pSpell->p_caster->CastSpell(pSpell->p_caster, dbcSpell.LookupEntry(30457), true);

	return true;
}

// -----------------------------------------------------------------------------

bool ReindeerTransformation(uint32 i, Spell *pSpell)
{
	if(!pSpell->p_caster) return true;

	if(pSpell->p_caster->GetUInt32Value(UNIT_FIELD_MOUNTDISPLAYID) != 0)
	{
		if(pSpell->p_caster->m_setflycheat)
			pSpell->p_caster->SetUInt32Value(UNIT_FIELD_MOUNTDISPLAYID, 22724);
		else
			pSpell->p_caster->SetUInt32Value(UNIT_FIELD_MOUNTDISPLAYID, 15902);
	}
	return true;
}

// -----------------------------------------------------------------------------

bool SummonCritterDummy(uint32 i, Spell *pSpell)
{
	// the reason these spells have to be scripted is because they require a
	// reagent to summon the critter pet, but don't require one to dismiss it

	if(!pSpell->p_caster) return true;

	return true;
}

// -----------------------------------------------------------------------------

bool WinterWondervolt(uint32 i, Spell *pSpell)
{
	Unit * target = pSpell->GetUnitTarget();

	if(!target || target->GetTypeId() != TYPEID_PLAYER) return true;

	target->CastSpell(target, dbcSpell.LookupEntry(26274), true);

	return true;
}

// -----------------------------------------------------------------------------
bool DeadlyThrowDummyEffect(uint32 i, Spell* pSpell)
{
	Unit* target = pSpell->GetUnitTarget();
	if(!target) return true;

	if(pSpell->m_caster->IsPlayer() && TO_PLAYER(pSpell->m_caster)->HasAura(32748))
		pSpell->SpellEffectInterruptCast(i);

	return true;
}

// -----------------------------------------------------------------------------

bool WinterWondervoltAura(uint32 i, Aura *pAura, bool apply)
{
	Unit *u_caster = pAura->GetUnitCaster();

	if(!u_caster || !u_caster->IsPlayer()) return true;

	if(apply)
	{
		uint32 displayId;
		uint32 chance = RandomUInt(7);

		if(u_caster->getGender() == 1)	displayId = 15795 + chance;	// female	0-7
		else if(chance == 0)			displayId = 15687;			// male		0
		else							displayId = 15802 + chance;	// male		1-7

		u_caster->SetUInt32Value(UNIT_FIELD_DISPLAYID, displayId);
	}
	else
		u_caster->SetUInt32Value(UNIT_FIELD_DISPLAYID, u_caster->GetUInt32Value(UNIT_FIELD_NATIVEDISPLAYID));

	return true;
}

// -----------------------------------------------------------------------------

bool ScryingCrystal(uint32 i, Spell *pSpell)
{
	QuestLogEntry *en = pSpell->p_caster->GetQuestLogForEntry(9824);
	if(pSpell->p_caster->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(pSpell->p_caster->GetPositionX(), 
		pSpell->p_caster->GetPositionY(), pSpell->p_caster->GetPositionZ(), 300078) && en)
	{
		
		if(en->GetMobCount(0) < en->GetQuest()->required_mobcount[0])
		{
			en->SetMobCount(0, 1);
			en->SendUpdateAddKill(0);
			en->UpdatePlayerFields();
			return false;
		}
	}
	else if(pSpell->p_caster->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(pSpell->p_caster->GetPositionX(), 
		pSpell->p_caster->GetPositionY(), pSpell->p_caster->GetPositionZ(), 300142) && en)
	{
		if(en->GetMobCount(1) < en->GetQuest()->required_mobcount[1])
		{
			en->SetMobCount(1, 1);
			en->SendUpdateAddKill(1);
			en->UpdatePlayerFields();
			return false;
		}
	}
	return true;
}

bool MinionsOfGurok(uint32 i, Spell *pSpell)
{
	Unit * target = pSpell->GetUnitTarget();
	if(!pSpell->p_caster || !target || target->GetTypeId() != TYPEID_UNIT || target->GetEntry() != 17157) return true;

	TO_CREATURE(target)->Despawn(500, 360000);

	float SSX = target->GetPositionX();
	float SSY = target->GetPositionY();
	float SSZ = target->GetPositionZ();
	float SSO = target->GetOrientation();

	pSpell->p_caster->GetMapMgr()->GetInterface()->SpawnCreature(18181, SSX+rand()%8-4, SSY+rand()%8-4, SSZ, SSO, true, false, 0, 0);
	pSpell->p_caster->GetMapMgr()->GetInterface()->SpawnCreature(18181, SSX+rand()%8-4, SSY+rand()%8-4, SSZ, SSO, true, false, 0, 0);
	pSpell->p_caster->GetMapMgr()->GetInterface()->SpawnCreature(18181, SSX+rand()%8-4, SSY+rand()%8-4, SSZ, SSO, true, false, 0, 0);

	return true;
}

bool PurifyBoarMeat(uint32 i, Spell *pSpell)
{
	uint32 bormeat = RandomUInt(2);
	switch(bormeat)
	{
	case 0:
		{
			pSpell->p_caster->CastSpell(pSpell->p_caster, 29277, true);
		}break;
	case 1:
		{
			pSpell->p_caster->CastSpell(pSpell->p_caster, 29278, true);
		}break;
	}
	
	return true;
}

bool WarpRiftGenerator(uint32 i, Spell *pSpell)
{
	if(!pSpell->p_caster) return true;

	float SSX = pSpell->p_caster->GetPositionX();
	float SSY = pSpell->p_caster->GetPositionY();
	float SSZ = pSpell->p_caster->GetPositionZ();
	float SSO = pSpell->p_caster->GetOrientation();

	pSpell->p_caster->GetMapMgr()->GetInterface()->SpawnCreature(16939,SSX,SSY,SSZ,SSO,true,false,0,0);

	return true;
}

bool MountMustFly(Player *pPlayer, AreaTable *pArea)
{
	if (!pPlayer || !pArea)
		return false;
	else
	{
		bool hasHighEnoughRiding = pPlayer->_GetSkillLineCurrent(SKILL_RIDING) >= 225;
		bool isInOutlands = pArea->AreaFlags & 1024 && pPlayer->GetMapId() != 571;
		bool isInNorthrend = pArea->AreaFlags & 1024 && pPlayer->GetMapId() == 571;
		bool canFlyInNorthrend = pPlayer->HasSpell(54197);
		return hasHighEnoughRiding && (isInOutlands || (isInNorthrend && canFlyInNorthrend));
	}
}

uint32 GetNewScalingMountSpellId(Aura *pAura, bool mountCanFly, uint32 regularGround, uint32 epicGround, uint32 regularFlying = 0, uint32 epicFlying = 0)
{
	uint32 newspell = 0;
	Player *pPlayer = TO_PLAYER(pAura->GetTarget());
	AreaTable *pArea = dbcArea.LookupEntry(pPlayer->GetAreaID());

	uint32 ridingSkill = pPlayer->_GetSkillLineCurrent(SKILL_RIDING);
	if(mountCanFly && MountMustFly(pPlayer, pArea))
		if(ridingSkill >= 300)
			newspell = epicFlying;
		else // if (ridingSkill >= 225)
			newspell = regularFlying;
	else if(ridingSkill >= 150)
		newspell = epicGround;
	else // if (ridingSkill >= 75)
		newspell = regularGround;

	return newspell;
}

bool BigBlizzardBear(uint32 i, Aura *pAura, bool apply)
{
	return true;
}

bool WingedSteed(uint32 i, Aura *pAura, bool apply)
{
	return true;
}

bool HeadlessHorsemanMount(uint32 i, Aura *pAura, bool apply)
{
	return true;
}

bool MagicBroomMount(uint32 i, Aura *pAura, bool apply)
{
	return true;
}

bool MagicRoosterMount(uint32 i, Aura *pAura, bool apply)
{
	return true;
}

bool InvincibleMount(uint32 i, Aura *pAura, bool apply)
{
	return true;
}

// Add new functions above this line
// -----------------------------------------------------------------------------

void SetupItemSpells_1(ScriptMgr * mgr)
{
	mgr->register_dummy_spell(23453, &GnomishTransporter);		// Gnomish Transporter
	mgr->register_dummy_spell(16589, &NoggenFoggerElixr);		// Noggenfogger
	mgr->register_dummy_spell(24430, &HallowsEndCandy);			// Hallows End Candy
	mgr->register_dummy_spell( 8063, &DeviateFish);				// Deviate Fish
	mgr->register_dummy_spell( 8213, &CookedDeviateFish);		// Savory Deviate Delight
	mgr->register_dummy_spell(26074, &HolidayCheer);			// Holiday Cheer
	mgr->register_dummy_spell(13120, &NetOMatic);				// Net-o-Matic
	mgr->register_dummy_spell( 4130, &BanishExile);				// Essence of the Exile Quest
	mgr->register_dummy_spell( 4131, &BanishExile);				// Essence of the Exile Quest
	mgr->register_dummy_spell( 4132, &BanishExile);				// Essence of the Exile Quest
	mgr->register_dummy_spell(19938, &ForemansBlackjack);		// Lazy Peons Quest
	mgr->register_dummy_spell(39105, &NetherWraithBeacon);		// Spellfire Tailor Quest
	mgr->register_dummy_spell( 8593, &SymbolOfLife);			// Paladin's Redemption QuestLine
	mgr->register_dummy_spell(30458, &NighInvulnBelt);			// Nigh Invulnerability Belt
	mgr->register_dummy_spell(25860, &ReindeerTransformation);	// Fresh Holly & Preserved Holly
	mgr->register_dummy_spell(26469, &SummonCritterDummy);		// Snowman Kit
	mgr->register_dummy_spell(26528, &SummonCritterDummy);		// Jingling Bell
	mgr->register_dummy_spell(26532, &SummonCritterDummy);		// Green Helper Box
	mgr->register_dummy_spell(26541, &SummonCritterDummy);		// Red Helper Box
	mgr->register_dummy_spell(26275, &WinterWondervolt);		// PX-238 Winter Wondervolt Trap
	mgr->register_dummy_aura( 26274, &WinterWondervoltAura);	// PX-238 Winter Wondervolt Transform Aura
	mgr->register_dummy_spell(32042, &ScryingCrystal);			// Violet Scrying Crystal (Quest)
	mgr->register_dummy_spell(32001, &MinionsOfGurok);			// Minions of gurok
	mgr->register_dummy_spell(29200, &PurifyBoarMeat);			// Purify Boar meat spell
	mgr->register_dummy_spell(35036, &WarpRiftGenerator);		// Summon a Warp Rift in Void Ridge
	mgr->register_dummy_aura( 58983, &BigBlizzardBear);			// Big Blizzard Bear mount 
	mgr->register_dummy_aura( 54729, &WingedSteed);				// DK flying mount 
	mgr->register_dummy_aura( 48025, &HeadlessHorsemanMount);	// Headless Horseman Mount 
	mgr->register_dummy_aura( 47977, &MagicBroomMount);			// Magic Broom Mount 
	mgr->register_dummy_aura( 65917, &MagicRoosterMount);		// Magic Rooster Mount
	mgr->register_dummy_aura( 72286, &InvincibleMount);			// Invincible Mount (off of Arthas)
	mgr->register_dummy_spell( 26679, &DeadlyThrowDummyEffect);

// Register new dummy spells above this line
// -----------------------------------------------------------------------------
}
