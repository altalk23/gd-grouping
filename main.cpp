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

inline void writeClamp999x2(int offset1000) {
	m->registerWrite(getBase()+offset1000, 4, a1000.s);
	m->registerWrite(getBase()+offset1000 + 5, 4, a999.s);
	m->registerWrite(getBase()+offset1000 + 10, 4, a999.s);
	m->registerWrite(getBase()+offset1000 + 26, 4, a1000.s);
}

class: public $MenuLayer {
	void onMoreGames(CCObject* ob) override {
		FLAlertLayer::create("Cacao", "Hello from custom mod!", "OK")->show();
	} 
} MyMenuLayerHook;

class: public $GJEffectManager {
    bool init() override {
        if ($GJEffectManager::init()) {
            for (int i = 0; i <= GROUP; ++i) {
                cac_this->m_colorActionsForGroup[i] = nullptr;
                cac_this->m_colorSpritesForGroup[i] = nullptr;
                cac_this->m_inheritanceNodesForGroup[i] = nullptr;
                cac_this->m_groupToggled[i] = 1;
            }
            return true;
        }
        else return false;
    }
} GJEffectManagerHook;

void patches() {
	std::cout << "aaaaa" << std::endl;
	a999.v = GROUP - 1; 			// 9999     | oh girl
	a1000.v = GROUP; 				// 10000    | oh girl
	a1001.v = GROUP + 1; 			// 10001	| Next group id - ends at 1000 for some reason
	a1100.v = GROUP + 100;			// 10100	| LevelEditorLayer be like
	a1101.v = GROUP + 101;			// 10101	| Container loops and quite a lot of other stuff
	a1102.v = GROUP + 102;			// 10102	| Quite a lot of other stuff
	a4404.v = 4 * GROUP + 404;		// 40404	| float vector lmao
	a8808.v = 8 * GROUP + 808;		// 80808	| Containers mostly
	f2000.v = GROUP;				// 10000    | Follow key
	c1000000.v = GROUP * 1000;		// 10000000 | Collision key
	cn1000000.v = GROUP * -1000;	// -10000000| Collision key

	
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

	// LevelEditorLayer::resetToggledGroups() | inlined smh

	// LevelEditorLayer::resetObjectVector() | unused


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
}

static int const patc = (patches(), 0);
APPLY_HOOKS();
