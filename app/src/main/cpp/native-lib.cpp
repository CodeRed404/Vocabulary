#include "raylib.h"
#include "scripts/Global.h"
#include "scripts/Manager.h"
#include "scripts/AssetManager.h"
//#include "scripts/scenes/SceneManager.h"
#include <jni.h>

extern "C"
JNIEXPORT jstring JNICALL
Java_com_codered404_vocabulary_MainActivity_stringFromJNI(JNIEnv *env, jobject thiz) {
    // TODO: implement stringFromJNI()
    return NULL;
}

// Muss verbessert werden:
// alle inlines wegmachen und eine andere Loesung finden - weil es dann ueberall ist wo es gebraucht wird (mehrmals)

int main() {
    InitWindow(0, 0, "Vocabulary");
    SetTargetFPS(60);
    InitAudioDevice();

    SetExitKey(KEY_NULL);

    AssetManager::LoadAssets();

    SceneManager::Init();

    float delta;

    while (!Global::exitProgram) {
        Global::LoadTemplates();
        delta = GetFrameTime();

        if (GetTouchPointCount() > 0) {
            Global::pressedTimer += delta;
        }
        if (GetTouchPointCount() == 0) {
            Global::pressedTimer = 0.0f;
        }

        Manager::Update(delta);

        BeginDrawing();
        ClearBackground(BLACK);
        DrawRectangleGradientEx(
            {0, 0, (float)GetScreenWidth(),(float)GetScreenHeight()},
            Color{75, 108, 183, 255},
            Color{24, 40, 72},
            Color{24, 40, 72},
            Color{75, 108, 183, 255}
        );
        Manager::Draw();
        EndDrawing();
    }
    Global::exitProgram = false;

    AssetManager::UnloadAssets();

    CloseAudioDevice();
    CloseWindow();

    return 0;
}