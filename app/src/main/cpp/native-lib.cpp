#include "raylib.h"
#include "scripts/Global.h"
#include "scripts/Manager.h"
#include "scripts/AssetManager.h"
#include "scripts/vocabs/Templates.h"
#include "curl/curl.h"
#include "thread"
#include "fstream"
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

    srand((unsigned)time(0));

    /*
    // --- ZERTIFIKAT AUS DEN ASSETS EXTRAHIEREN ---
    // Raylib lädt die Datei automatisch aus dem Android "assets"-Ordner
    int dataSize = 0;
    unsigned char *fileData = LoadFileData("cacert.pem", &dataSize);

    if (fileData != NULL && dataSize > 0) {
        // Wir schreiben das Zertifikat in den beschreibbaren lokalen App-Pfad auf dem Handy
        Templates::globalCaCertPath = std::string(GetApplicationDirectory()) + "/cacert.pem";

        std::ofstream  outFile(Templates::globalCaCertPath, std::ios::binary);
        outFile.write((char*)fileData, dataSize);
        outFile.close();

        UnloadFileData(fileData); // Speicher wieder freigeben
    }*/

    // MARKUS: ZERTIFIKATE VON ANDROID SELBST NEHMEN, WEIL DIE AUSLAUFEN

    SetTargetFPS(60);

    curl_global_init(CURL_GLOBAL_DEFAULT);

    SceneManager::Init();
    AssetManager::LoadAssets();

    std::thread nwThread(Templates::LoadTemplates);
    nwThread.detach();

    // Loading animation
    Texture2D loadingCircle = LoadTexture("textures/loading/loading_circle.png");
    float loadingCircleRotation = 0;
    float loadingCircleFactor = 0.75f;
    float loadingCircleSpeed = 350.0f;
    while (Global::isLoading) {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexturePro(loadingCircle, {0, 0, (float)loadingCircle.width, (float)loadingCircle.height}, {(float)GetScreenWidth() / 2.0f, (float)GetScreenHeight() / 2.0f, (float)loadingCircle.width * loadingCircleFactor, (float)loadingCircle.height * loadingCircleFactor}, {loadingCircle.width * loadingCircleFactor / 2.0f, loadingCircle.height * loadingCircleFactor / 2.0f}, loadingCircleRotation, WHITE);
        EndDrawing();
        loadingCircleRotation += loadingCircleSpeed * GetFrameTime();
        if (loadingCircleRotation >= 360) {
            loadingCircleRotation = 0;
        }
    }
    UnloadTexture(loadingCircle);

    float delta;

    while (!Global::exitProgram) {
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
                {0, 0, (float) GetScreenWidth(), (float) GetScreenHeight()},
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

    curl_global_cleanup();

    CloseAudioDevice();
    CloseWindow();

    return 0;
}