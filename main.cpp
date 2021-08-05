#define CAC_PROJ_NAME "Grouping"
#include <CacKit>

union {
    int v;
    char s[4];
} a999, a1000, a1001, a1100, a1101, a1102, a4404, a8808, f2000, c1000000, cn1000000;

static const int GROUP = 10000;

inline void write(int offset, char* data) {
	m->registerWrite(getBase()+offset, 4, data);
}

inline void writeClamp999(int offset1000) {
	m->registerWrite(getBase()+offset1000, 4, a1000.s);
	m->registerWrite(getBase()+offset1000 + 5, 4, a999.s);
}

inline void writeClamp1101(int offset1101, int offset1102) {
	m->registerWrite(getBase()+offset1101, 4, a1101.s);
	m->registerWrite(getBase()+offset1102, 4, a1102.s);
}

inline void writeClamp999x2(int offset1000) {
	m->registerWrite(getBase()+offset1000, 4, a1000.s);
	m->registerWrite(getBase()+offset1000 + 5, 4, a999.s);
	m->registerWrite(getBase()+offset1000 + 10, 4, a999.s);
	m->registerWrite(getBase()+offset1000 + 26, 4, a1000.s);
}

inline void nopArray(int offset) {
	m->registerWrite(getBase()+offset, 9, (char*)"\x90\x90\x90\x90\x90\x90\x90\x90\x90");
}

void inject() {
	a999.v = GROUP - 1;                 // 9999     | oh girl
	a1000.v = GROUP;                    // 10000    | oh girl
	a1001.v = GROUP + 1;                // 10001    | Next group id - ends at 1000 for some reason
	a1100.v = GROUP + 100;              // 10100    | LevelEditorLayer be like
	a1101.v = GROUP + 101;              // 10101    | Container loops and quite a lot of other stuff
	a1102.v = GROUP + 102;              // 10102    | Quite a lot of other stuff
	a4404.v = 4 * GROUP + 404;          // 40404    | float vector lmao
	a8808.v = 8 * GROUP + 808;          // 80808    | Containers mostly
	f2000.v = GROUP;                    // 10000    | Follow key
	c1000000.v = GROUP * 1000;          // 10000000 | Collision key
	cn1000000.v = GROUP * -1000;        // -10000000| Collision key

	// EditorUI::updateObjectInfoLabel()
	write(0x1d037 + 3, a1000.s);
	write(0x1d089 + 3, a1000.s);

	// LevelEditorLayer::addSpecial(GameObject*)
	write(0x9514d + 3, a1000.s);
	

	// GJEffectManager::updateEffects(float)
	nopArray(0x181f17);
	nopArray(0x181ee1);

	// GJEffectManager::updateOpacityEffects(float)
	nopArray(0x1824b7);
	nopArray(0x1824e7);

	// GJEffectManager::updateOpacityAction(OpacityEffectAction*) not this
	nopArray(0x1847ab);
	nopArray(0x1847c5);

	// GJEffectManager::updateActiveOpacityEffects()
	nopArray(0x184847);
	nopArray(0x18486f);

	// GJEffectManager::updatePulseEffects(float)
	nopArray(0x18228e);

	// GJEffectManager::runPulseEffect(int, bool, float, float, float, PulseEffectType, cocos2d::_ccColor3B, cocos2d::_ccHSVValue, int, bool, bool, bool, int)
	nopArray(0x184bc4);

	// GJEffectManager::addGroupPulseEffect(PulseEffectAction*)
	nopArray(0x184c70);

	// GJEffectManager::colorForGroupID(int, cocos2d::_ccColor3B const&, bool)
	m->registerWrite(getBase()+0x184fb9, 11, (char*)"\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90");

	// GJEffectManager::loadState(std::basic_string<char, std::char_traits<char>, std::allocator<char>>)
	m->registerWrite(getBase()+0x189393, 8, (char*)"\x90\x90\x90\x90\x90\x90\x90\x90");

	// LevelEditorLayer::getNextFreeGroupID(cocos2d::CCArray*)
	write(0x9a377 + 2, a1001.s);

	// GJBaseGameLayer::init()
	write(0xafe74 + 3, a1102.s);
	write(0xafece + 3, a1102.s);
	write(0xaff21 + 3, a1102.s);

	write(0xafe93 + 1, a1101.s);
	write(0xafee6 + 1, a1101.s);
	write(0xaff39 + 1, a1101.s);

	write(0xafe7d + 2, a8808.s);
	write(0xafed7 + 2, a8808.s);
	write(0xaff2a + 2, a8808.s);
	write(0xaffc0 + 2, a8808.s);

	// GJBaseGameLayer::getGroup(int)
	writeClamp999(0xb6f2d + 2);

	// GJBaseGameLayer::getMoveDeltaForObjects(int, int)
	writeClamp999(0xb6ddb + 2);
	writeClamp999(0xb6e3b + 3);

	// GJBaseGameLayer::spawnGroup(int)
	writeClamp999(0xb70a5 + 2);

	// GJBaseGameLayer::toggleGroup(int, bool)
	writeClamp999(0xb761e + 3);

	// GJBaseGameLayer::addToGroup(GameObject*, int, bool)
	write(0xb7806 + 2, a1100.s);

	writeClamp999(0xb7815 + 2);

	// GJBaseGameLayer::removeFromGroup(GameObject*, int)
	writeClamp999(0xb7a77 + 3);

	// GJBaseGameLayer::processRotationActions()
	writeClamp999(0xb804b + 1);

	// GJBaseGameLayer::processPlayerFollowActions(float)
	writeClamp999(0xb8bdc + 1);

	// GJBaseGameLayer::processFollowActions()
	write(0xb901e + 1, a999.s);
	write(0xb904c + 1, a1000.s);
	write(0xb90ab + 2, a1000.s);

	// GJBaseGameLayer::optimizeMoveGroups()
	writeClamp999(0xb9780 + 1);

	// GJEffectManager::init()
	write(0x1804aa + 2, a1102.s);
	write(0x180501 + 2, a1102.s);
	write(0x180558 + 3, a1102.s);
	write(0x1805bb + 2, a1102.s);

	write(0x1804d0 + 1, a1101.s);
	write(0x180520 + 1, a1101.s);
	write(0x18058b + 1, a1101.s);
	write(0x180561 + 2, a1101.s);
	write(0x1805da + 1, a1101.s);

	write(0x1804b2 + 3, a8808.s);
	write(0x180509 + 3, a8808.s);
	write(0x1805c3 + 3, a8808.s);


	// GJEffectManager::setFollowing(int, int, bool)
	write(0x185e0a + 2, f2000.s);

	// GJEffectManager::wasFollowing(int, int)
	write(0x185e6b + 2, f2000.s);
	
	// // GJEffectManager::postCollisionCheck()
	// write(0x1827c3 + 4, cn1000000.s);
	// write(0x1827e9 + 4, cn1000000.s);

	// // GJEffectManager::objectsCollided(int, int)
	// write(0x182a36 + 4, c1000000.s);
	// write(0x182a1f + 2, a999.s);
	// write(0x182a27 + 2, a999.s);

	// GJEffectManager::reset()
	write(0x180722 + 2, a8808.s);

	//GJEffectManager::getCurrentStateString()
	write(0x187375 + 2, a1101.s);

	// GJEffectManager::removeAllPulseActions() | already inlined

	// GJEffectManager::resetEffects() | not related to groups

	// GJEffectManager::resetToggledGroups() | unused


	// PlayLayer::loadFromCheckpoint(CheckpointObject*)
	write(0x7f2a3 + 3, a999.s);

	// LevelEditorLayer::init(GJGameLevel*)
	write(0x912b6 + 3, a1102.s);
	write(0x91311 + 3, a1102.s);
	write(0x9136c + 3, a1102.s);
	write(0x913cb + 3, a1102.s);
	write(0x9142a + 3, a1102.s);
	write(0x91498 + 3, a1102.s);
	write(0x914fe + 3, a1102.s);
	write(0x91558 + 3, a1102.s);
	write(0x915bd + 3, a1102.s);

	write(0x912d9 + 1, a1101.s);
	write(0x9132d + 1, a1101.s);
	write(0x9139c + 1, a1101.s);
	write(0x91379 + 2, a1101.s);
	write(0x913eb + 1, a1101.s);
	write(0x913dc + 2, a1101.s);
	write(0x9145a + 1, a1101.s);
	write(0x91437 + 2, a1101.s);
	write(0x914c4 + 1, a1101.s);
	write(0x914a1 + 2, a1101.s);
	write(0x91516 + 1, a1101.s);
	write(0x91584 + 1, a1101.s);
	write(0x91561 + 2, a1101.s);
	write(0x915dc + 1, a1101.s);
	write(0x91674 + 3, a1101.s);

	write(0x915cd + 2, a4404.s);

	write(0x912c3 + 2, a8808.s);
	write(0x9131e + 2, a8808.s);
	write(0x91507 + 2, a8808.s);

	// LevelEditorLayer::updateGameObjectsNew()
	write(0x9ae5f + 2, a1101.s);

	// LevelEditorLayer::updateToggledGroups()
	write(0x9bc3e + 3, a1101.s);

	// LevelEditorLayer::updateBlendValues() | idk anymore honestly
	write(0x9bcf1 + 3, a1101.s);

	// LevelEditorLayer::resetToggledGroupsAndObjects()
	write(0x9c475 + 2, a1100.s);

	// LevelEditorLayer::updateEditorMode()
	write(0x93d65 + 2, a1100.s);

	// LevelEditorLayer::addToGroup(GameObject*, int, bool)
	write(0x9dac9 + 2, a1100.s);

	// LevelEditorLayer::recreateGroups()
	write(0x9dc95 + 3, a1101.s);

	// LevelEditorLayer::onPlaytest()
	write(0xa0ab5 + 2, a1100.s);

	// LevelEditorLayer::onStopPlaytest()
	write(0xa19e5 + 2, a1100.s);


	// EffectGameObject::triggerObject(GJBaseGameLayer*)
	writeClamp999(0xb71dd + 2);


	// GJMoveCommandLayer::onUpdateGroupID(cocos2d::CCObject*)
	writeClamp999x2(0x373383 + 1);

	// GJMoveCommandLayer::onUpdateGroupID2(cocos2d::CCObject*)
	writeClamp999x2(0x3734f3 + 1);

	// GJMoveCommandLayer::textChanged(CCTextInputNode*)
	writeClamp999(0x37460b + 1);
	writeClamp999(0x3746e6 + 1);

	write(0x37472f + 2, a1101.s);
	write(0x374840 + 2, a1101.s);
	write(0x37475b + 2, a1102.s);
	write(0x37486b + 2, a1102.s);


	// SetGroupIDLayer::textChanged(CCTextInputNode*)
	writeClamp999(0x197b4c + 1);

	// non-virtual thunk to SetGroupIDLayer::textChanged(CCTextInputNode*)
	writeClamp999(0x197be3 + 1);


	// SetupOpacityPopup::onTargetIDArrow(cocos2d::CCObject*)
	writeClamp999(0x340d8 + 2);
	writeClamp1101(0x34134 + 2, 0x3415b + 2);

	// SetupOpacityPopup::textChanged(CCTextInputNode*)
	writeClamp999(0x34abc + 2);
	writeClamp1101(0x34b15 + 2, 0x34b3b + 2);


	// SetupPulsePopup::onSelectTargetMode(cocos2d::CCObject*)
	write(0x1eadb4 + 7, a1000.s);
	writeClamp1101(0x1eae8f + 2, 0x1eaebb + 2);

	// SetupPulsePopup::onUpdateCustomColor(cocos2d::CCObject*)
	write(0x1eaefe + 7, a1000.s);
	writeClamp999(0x1eaf3b + 2);
	writeClamp1101(0x1eaf98 + 2, 0x1eafbb + 2);

	// SetupPulsePopup::updateCopyColorTextInputLabel() | idk
	write(0x1ebf38 + 3, a1000.s);
	writeClamp1101(0x1ec15e + 2, 0x1ec18b + 2);
	writeClamp1101(0x1ec0c5 + 1, 0x1ec0bf + 2);

	// SetupPulsePopup::textChanged(CCTextInputNode*)
	writeClamp999(0x1ec9e9 + 1);
	writeClamp1101(0x1ecc75 + 2, 0x1ecc9b + 2);

	// SetupPulsePopup::updateEditorLabel()
	write(0x1ec41b + 2, a1000.s);
	write(0x1ec377 + 2, a1000.s);

	// SetupPulsePopup::updateTextInputLabel()
	write(0x1eb901 + 2, a999.s);

	//TODO: Fix SetupPulsePopup interface


	// SetupSpawnPopup::onTargetIDArrow(cocos2d::CCObject*)
	writeClamp999(0x13adb8 + 2);
	writeClamp1101(0x13ae14 + 2, 0x13ae3b + 2);

	// SetupSpawnPopup::textChanged(CCTextInputNode*)
	writeClamp999(0x13ba08 + 2);
	writeClamp1101(0x13bae4 + 2, 0x13bb0b + 2);

	// SetupObjectTogglePopup::onTargetIDArrow(cocos2d::CCObject*)
	writeClamp999(0x1c1c78 + 2);
	writeClamp1101(0x1c1cd4 + 2, 0x1c1cfb + 2);

	// SetupObjectTogglePopup::textChanged(CCTextInputNode*)
	writeClamp999(0x1c26bc + 2);
	writeClamp1101(0x1c2715 + 2, 0x1c273b + 2);


	// GJRotateCommandLayer::onUpdateGroupID(cocos2d::CCObject*)
	writeClamp999x2(0x4be3 + 1);
	writeClamp1101(0x4c38 + 2, 0x4c5b + 2);

	// GJRotateCommandLayer::onUpdateGroupID2(cocos2d::CCObject*)
	writeClamp999x2(0x4cd3 + 2);
	writeClamp1101(0x4d22 + 2, 0x4d4b + 2);

	// GJRotateCommandLayer::textChanged(CCTextInputNode*)
	writeClamp999(0x59ed + 1);
	writeClamp999(0x5aca + 2);
	writeClamp1101(0x5bf5 + 2, 0x5c1b + 2);
	writeClamp1101(0x5d04 + 2, 0x5d2b + 2);


	// GJPFollowCommandLayer::onTargetIDArrow(cocos2d::CCObject*)
	writeClamp999x2(0x1b1363 + 1);
	writeClamp1101(0x1b13b8 + 2, 0x1b13db + 2);

	// GJPFollowCommandLayer::textChanged(CCTextInputNode*)
	writeClamp999(0x1b1f1e + 1);
	writeClamp1101(0x1b21d4 + 2, 0x1b21fb + 2);


	// GJFollowCommandLayer::onUpdateGroupID(cocos2d::CCObject*)
	writeClamp999x2(0x16c923 + 1);
	writeClamp1101(0x16c978 + 2, 0x16c99b + 2);

	// GJFollowCommandLayer::onUpdateGroupID2(cocos2d::CCObject*)
	writeClamp999(0x16ca13 + 2);
	write(0x16ca26 + 2, a1000.s);
	writeClamp1101(0x16ca62 + 2, 0x16ca8b + 2);

	// GJFollowCommandLayer::textChanged(CCTextInputNode*)
	writeClamp999(0x16d5d9 + 1);
	writeClamp999(0x16d6b6 + 2);
	writeClamp1101(0x16d7c5 + 2, 0x16d7eb + 2);
	writeClamp1101(0x16d8d4 + 2, 0x16d8fb + 2);


	// SetTargetIDLayer::onTargetIDArrow(cocos2d::CCObject*)
	writeClamp999(0x15af08 + 2);
	writeClamp1101(0x15af64 + 2, 0x15af8b + 2);

	// SetTargetIDLayer::textChanged(CCTextInputNode*)
	writeClamp999(0x15b71c + 2);
	writeClamp1101(0x15b775 + 2, 0x15b79b + 2);


	// SetupAnimationPopup::onTargetIDArrow(cocos2d::CCObject*)
	writeClamp999(0x209ff8 + 2);
	writeClamp1101(0x20a054 + 2, 0x20a07b + 2);

	// SetupAnimationPopup::textChanged(CCTextInputNode*)
	writeClamp999(0x20ac1a + 2);
	writeClamp1101(0x20acce + 2, 0x20acfb + 2);


	// SetupCollisionTriggerPopup::onTargetIDArrow(cocos2d::CCObject*)
	writeClamp999(0x1d77e8 + 2);
	writeClamp1101(0x1d7844 + 2, 0x1d786b + 2);

	// SetupCollisionTriggerPopup::textChanged(CCTextInputNode*)
	writeClamp999(0x1d863e + 2);
	writeClamp1101(0x1d8752 + 2, 0x1d877b + 2);


	// SetupCountTriggerPopup::updateTargetID() | not inlined updateTargetID wtffffff
	writeClamp999(0x15e8c1 + 2);
	writeClamp1101(0x15e915 + 2, 0x15e93b + 2);

	
	// SetupInstantCountPopup::onTargetIDArrow(cocos2d::CCObject*)
	writeClamp999(0x354558 + 2);
	writeClamp1101(0x3545ac + 2, 0x3545db + 2);

	// SetupInstantCountPopup::textChanged(CCTextInputNode*)
	writeClamp999(0x3553c3 + 2);
	writeClamp1101(0x3554d2 + 2, 0x3554fb + 2);


	// SetupInteractObjectPopup::onTargetIDArrow(cocos2d::CCObject*)
	writeClamp999(0x29bbf8 + 2);
	writeClamp1101(0x29bc4c + 2, 0x29bc7b + 2);

	// SetupInteractObjectPopup::textChanged(CCTextInputNode*)
	writeClamp999(0x29c397 + 2);
	writeClamp1101(0x29c442 + 2, 0x29c46b + 2);


	// SetupTouchTogglePopup::onTargetIDArrow(cocos2d::CCObject*)
	writeClamp999(0x158b98 + 2);
	writeClamp1101(0x158bf4 + 2, 0x158c1b + 2);

	// SetupTouchTogglePopup::textChanged(CCTextInputNode*)
	writeClamp999(0x159714 + 2);
	writeClamp1101(0x15976d + 2, 0x15979b + 2);
}

class $redirect(PlayLayer) {
public:
	void pauseGame(bool p0) {
		std::cout << p0 << std::endl;
		std::cout << _effectManager() << std::endl;
		return $PlayLayer::pauseGame(p0);
	} 
} PlayLayerHook;

class $redirect(GJEffectManager) {
public:
    bool init() override {
        if ($GJEffectManager::init()) {
            for (int i = 0; i <= GROUP; ++i) {
                m_colorActionsForGroup[i] = nullptr;
                m_colorSpritesForGroup[i] = nullptr;
                m_inheritanceNodesForGroup[i] = nullptr;
                m_groupToggled[i] = 1;
            }
            return true;
        }
        else return false;
    }

    float opacityModForGroup(int group) {
    	auto action = reinterpret_cast<OpacityEffectAction*>(m_opacityActionsForGroup->objectForKey(group));
    	if (action && (!action->m_finished || action->m_opacity < 1.0)) {
    		return action->m_opacity;
    	}
    	return 1.0;
    }

    OpacityEffectAction* runOpacityActionOnGroup(int group, float time, float targetOpacity, int uuid) {
    	auto mod = opacityModForGroup(group);
    	auto action = OpacityEffectAction::create(time, mod, targetOpacity, group);
    	action->m_uuid = uuid;
    	m_opacityActionsForGroup->setObject(action, group);
    	return action;
    }

    cocos2d::_ccColor3B colorForGroupID(int group, cocos2d::_ccColor3B const& pulseColor, bool baseColor) {
    	if (!m_pulseActionsForGroup->objectForKey(group)) return pulseColor;
    	return $GJEffectManager::colorForGroupID(group, pulseColor, baseColor);
    }
} GJEffectManagerHook;

$apply();
