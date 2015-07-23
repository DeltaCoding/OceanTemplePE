#include <jni.h>
#include <dlfcn.h>
#include <android/log.h>
#include <stdlib.h>
#include <Substrate.h>

#include <mcpe/tile/Tile.h>
#include <mcpe/tile/material/Material.h>
#include <mcpe/item/TileItem.h>

#define LOG_TAG "oceantemplepe"

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__))

class SeaLantern : public Tile {
public:
	static const int ID = 200;

public:
	SeaLantern() : Tile(ID, "sea_lantern", Material::stone) {
		setNameId("SeaLantern");
		setCategory(2);
		init();
		new TileItem(ID - 256);
	}
};

static void (*Tile$initTiles_real)();
static void Tile$initTiles_hook() {
	Tile$initTiles_real();

	Tile::tiles[SeaLantern::ID] = new SeaLantern();
}

JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved) {
	MSHookFunction((void*) &Tile::initTiles, (void*) &Tile$initTiles_hook, (void**) &Tile$initTiles_real);

	return JNI_VERSION_1_2;
}
