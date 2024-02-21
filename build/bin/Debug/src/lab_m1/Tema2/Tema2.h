#pragma once

#include <vector>

#include "components/simple_scene.h"
#include "lab_camera.h"

namespace m1
{
    class Tema2 : public gfxc::SimpleScene
    {
    public:

        struct GameObject
        {
			GameObject() : mesh(nullptr), position(glm::vec3(0)), forward(glm::vec3(0)), modelMatrix(glm::mat4(1)) {}
			GameObject(Mesh* mesh, glm::vec3 position, glm::vec3 forward)
				: mesh(mesh), position(position), forward(forward), modelMatrix(glm::mat4(1)) {}
            GameObject(Mesh* mesh, glm::vec3 position, glm::vec3 forward, glm::mat4 modelMatrix)
				: mesh(mesh), position(position), forward(forward), modelMatrix(modelMatrix) {}
            GameObject(Mesh* mesh, glm::vec3 position, glm::vec3 forward, glm::mat4 modelMatrix, float timeCreated, std::string id)
                : mesh(mesh), position(position), forward(forward), modelMatrix(modelMatrix), timeCreated(timeCreated), id(id) {}

			Mesh* mesh;
			glm::vec3 position;
            glm::vec3 forward;
            glm::mat4 modelMatrix;
            float timeCreated = 0; // used for projectiles to store the time they were created
            std::string id = ""; // used for projectiles to store the tank id that shot it
		};

        struct Tank
        {
			Tank() : tank_rails(), tank_body(), tank_turret(), tank_gun() {}
			Tank(GameObject tank_rails, GameObject tank_body, GameObject tank_turret, GameObject tank_gun)
				: tank_rails(tank_rails), tank_body(tank_body), tank_turret(tank_turret), tank_gun(tank_gun) {}

            GameObject tank_rails;
			GameObject tank_body;
			GameObject tank_turret;
			GameObject tank_gun;
            int damage = 0;
            int moveType = 0;
            float timeMoveGenerated = 0;
		};

        struct Building
        {
			Building() : mesh(nullptr), position(glm::vec3(0)) {}
			Building(Mesh* mesh, glm::vec3 position)
				: mesh(mesh), position(position) {}
			Building(Mesh* mesh, glm::vec3 position, float dimOx, float dimOz)
				: mesh(mesh), position(position), dimOx(dimOx), dimOz(dimOz) {}

			Mesh* mesh;
			glm::vec3 position;
            float dimOz = 0;
            float dimOx = 0;
		};  

        struct ViewportArea
        {
            ViewportArea() : x(0), y(0), width(1), height(1) {}
            ViewportArea(int x, int y, int width, int height)
                : x(x), y(y), width(width), height(height) {}
            int x;
            int y;
            int width;
            int height;
        };

        Tema2();
        ~Tema2();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;

        void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, bool isMyTank = false, int damage = 0);

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void Tema2::CheckTanksCollision(Tank& tank1, Tank& tank2);
        void Tema2::MoveTankForward(Tank& tank, glm::vec3 forward, float distance);
        void Tema2::RotateTank(Tank& tank, float angle);
        void Tema2::RotateObject(glm::mat4& modelMatrix, glm::vec3& position, glm::vec3& forward, float angle);
        bool Tema2::CheckTankProjectileCollision(Tank& tank, GameObject& projectile);
        void Tema2::CheckTankBuildingCollision(Tank& tank, Building building);
        void Tema2::DetectTank(Tank& enemy);
        void Tema2::Shoot(Tank& tank);
        void Tema2::GenerateRandomMove(Tank& tank, float deltaTimeSeconds);
        void Tema2::SetCamera();
        void Tema2::RenderScene(float deltaTimeSeconds);
        void Tema2::RenderObjects();
    protected:

        // Camera
        implemented::MyCamera* camera;

        // buildings map
        std::unordered_map<std::string, Building> buildings;

        // projectiles maps
        std::unordered_map<std::string, GameObject> projectiles;
        std::unordered_map<std::string, GameObject> projectilesToBeRemoved;

        // tanks maps
        Tank tank;
        std::unordered_map<std::string, Tank> enemies;
        std::unordered_map<std::string, Tank> enemiesToBeRemoved;

        int score = 0;

        float old_angle_mouse = 0;
        float angle_mouse = 0;

        int projectileID = 0;
        int enemyID = 0;
        float lastEnemyShot = 0;

        // Viewport variables
        glm::mat4 projectionMatrix;
        glm::mat4 viewMatrix;
        float FoV = RADIANS(60);
        float left = -10.0f;
        float right = 10.0f;
        float bottom = -10.0f;
        float top = 10.0f;

        // Sets the resolution of the small viewport
        glm::ivec2 resolution = window->GetResolution();
        ViewportArea miniViewportArea = ViewportArea(50, 50, resolution.x / 5.f, resolution.y / 5.f);

        unsigned int materialShininess = 30;
        float materialKd = 0.5;
        float materialKs = 0.5;

        bool gameOver = false;

        // colors
        glm::vec3& olivine = glm::vec3(166 / 255.f, 211 / 255.f, 174 / 255.f); // olivine
        glm::vec3& asparagus = glm::vec3(103 / 255.f, 141 / 255.f, 88 / 255.f); // asparagus
        glm::vec3& celadon = glm::vec3(116 / 255.f, 211 / 255.f, 174 / 255.f); // celadon
        glm::vec3& champagne = glm::vec3(246 / 255.f, 231 / 255.f, 203 / 255.f); // champagne
        glm::vec3& coralPink = glm::vec3(221 / 255.f, 151 / 255.f, 135 / 255.f); // coral pink
        glm::vec3& roseQuartz = glm::vec3(173 / 255.f, 168 / 255.f, 190 / 255.f); // Rese Quartz
        glm::vec3& darkGreen = glm::vec3(13 / 255.f, 40 / 255.f, 24 / 255.f); // dark green
        glm::vec3& black = glm::vec3(2 / 255.f, 2 / 255.f, 2 / 255.f); // black
        glm::vec3& bondiBlue = glm::vec3(32 / 255.f, 138 / 255.f, 174 / 255.f); // bondi blue
        glm::vec3& ghostWhite = glm::vec3(236 / 255.f, 235 / 255.f, 243 / 255.f); // ghost white
        glm::vec3& lightBlue = glm::vec3(150 / 255.f, 195 / 255.f, 206 / 255.f); // light blue
        glm::vec3& emerald = glm::vec3(105 / 255.f, 220 / 255.f, 158 / 255.f); // emerald
        glm::vec3& kellyGreen = glm::vec3(98 / 255.f, 171 / 255.f, 55 / 255.f); // kelly green
        glm::vec3& darkPurple = glm::vec3(50 / 255.f, 33 / 255.f, 58 / 255.f); // dark purple
        glm::vec3& spaceCadet = glm::vec3(56 / 255.f, 59 / 255.f, 83 / 255.f); // space cadet
        glm::vec3& purplePizzazz = glm::vec3(255 / 255.f, 71 / 255.f, 218 / 255.f); // purple pizzazz
        glm::vec3& redPantone = glm::vec3(239 / 255.f, 35 / 255.f, 60 / 255.f); // red pantone
        glm::vec3& claret = glm::vec3(164 / 255.f, 19 / 255.f, 60 / 255.f); // claret
        glm::vec3& brightPink = glm::vec3(255 / 255.f, 117 / 255.f, 143 / 255.f); // bright pink
        glm::vec3& fandango = glm::vec3(180 / 255.f, 62 / 255.f, 143 / 255.f); // fandango
        glm::vec3& violet = glm::vec3(234 / 255.f, 122 / 255.f, 244 / 255.f); // violet
        glm::vec3& brown = glm::vec3(101 / 255.f, 67 / 255.f, 33 / 255.f); // brown
        glm::vec3& gold = glm::vec3(255 / 255.f, 220 / 255.f, 52 / 255.f); // gold



        glm::vec3& colorPlane = kellyGreen;
        glm::vec3& colorTankRails = roseQuartz;
        glm::vec3& colorTankBody = fandango;
        glm::vec3& colorTankTurret = violet;
        glm::vec3& colorTankGun = roseQuartz;
        glm::vec3& colorProjectile = black;
        glm::vec3& colorEnemyRails = roseQuartz;
        glm::vec3& colorEnemyBody = darkPurple;
        glm::vec3& colorEnemyTurret = spaceCadet;
        glm::vec3& colorEnemyGun = roseQuartz;
        glm::vec3& colorBuilding = ghostWhite;
        glm::vec3& colorSky = lightBlue;
        glm::vec3& colorDecorations = gold;
        glm::vec3& colorBranches = brown;
        glm::vec3& colorLeaves = darkGreen;
        glm::vec3& colorGift = brightPink;

        // lights
        glm::vec3 lightPosition = tank.tank_rails.position + glm::vec3(0.f, 1.f, 0.f);
        glm::vec3 lightPosition2 = glm::vec3(0, 9.7f, 0);

    };
}   // namespace m1