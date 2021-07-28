#define CAC_PROJ_NAME "Grouping"
#include <CacKit>

union {
    int v;
    char s[4];
} a999, a1000, a1001, a1101, a1102, a8008, a2000, a1000000;

void inject() {

}

class: public $MenuLayer {
	void onMoreGames(CCObject* ob) override {
		FLAlertLayer::create("Cacao", "Hello from custom mod!", "OK")->show();
	} 
} MyMenuLayerHook;

APPLY_HOOKS();
