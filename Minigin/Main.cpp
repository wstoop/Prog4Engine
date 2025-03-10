#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextObject.h"
#include "Scene.h"
#include "GameObject.h"
#include "AllComponents.h"
#include "iostream"

void CreateBackground(dae::Scene& scene);
void CreateLogo(dae::Scene& scene);
void CreateTextObjects(dae::Scene& scene, const std::shared_ptr<dae::Font>& font);
void CreateFPSObject(dae::Scene& scene, const std::shared_ptr<dae::Font>& font);
void CreateSpriteObjects(dae::Scene& scene);
void CreateRotatingAnimatedObjects(dae::Scene& scene);

void load()
{
    auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
    auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

    CreateBackground(scene);
    CreateLogo(scene);
    CreateTextObjects(scene, font);
    CreateFPSObject(scene, font);
	CreateSpriteObjects(scene);
    CreateRotatingAnimatedObjects(scene);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}

void CreateBackground(dae::Scene& scene)
{
    auto background = std::make_shared<dae::GameObject>();
    background->AddComponent<dae::TextureComponent>(background.get(), "background.tga");
    scene.Add(background);
}

void CreateLogo(dae::Scene& scene)
{
    auto logo = std::make_shared<dae::GameObject>();
    logo->AddComponent<dae::TextureComponent>(logo.get(), "logo.tga");
    logo->SetLocalPosition(glm::vec3(216, 180, 0));
    scene.Add(logo);
}

void CreateTextObjects(dae::Scene& scene, const std::shared_ptr<dae::Font>& font)
{
    auto topText = std::make_shared<dae::GameObject>();
    topText->AddComponent<dae::TextComponent>(topText.get(), "Programming 4 Assignment", font);
    topText->SetLocalPosition(glm::vec3(180, 20, 0));
    scene.Add(topText);
}

void CreateFPSObject(dae::Scene& scene, const std::shared_ptr<dae::Font>& font)
{
    auto FPS = std::make_shared<dae::GameObject>();
    FPS->AddComponent<dae::FPSComponent>(FPS.get());
    FPS->AddComponent<dae::TextComponent>(
        FPS.get(),
        std::to_string(FPS->GetComponent<dae::FPSComponent>()->GetFPS()),
        font
    );
    FPS->SetLocalPosition(glm::vec3(10, 20, 0));
    scene.Add(FPS);
}

void CreateSpriteObjects(dae::Scene& scene)
{
    auto Sprite1Center = std::make_shared<dae::GameObject>();
    Sprite1Center->SetLocalPosition(glm::vec3(300, 300, 0));
    scene.Add(Sprite1Center);
    auto Sprite1 = std::make_shared<dae::GameObject>();
    Sprite1->AddComponent<dae::TextureComponent>(Sprite1.get(), "Sprite_1.png");
    Sprite1->SetLocalPosition(glm::vec3(280, 300, 0));
    Sprite1->SetParent(Sprite1Center.get(), false);
    scene.Add(Sprite1);
    Sprite1->AddComponent<dae::RotateComponent>(Sprite1.get(), 5.f, 20.f);

    auto Sprite2 = std::make_shared<dae::GameObject>();
    Sprite2->AddComponent<dae::TextureComponent>(Sprite2.get(), "Sprite_2.png");
    scene.Add(Sprite2);
    Sprite2->SetLocalPosition(glm::vec3(0, 40, 0));
    Sprite2->SetParent(Sprite1.get(), false);

    Sprite2->AddComponent<dae::RotateComponent>(Sprite2.get(), -4.f, 20.f);

    auto Sprite3 = std::make_shared<dae::GameObject>();
    Sprite3->AddComponent<dae::TextureComponent>(Sprite3.get(), "Sprite_1.png");
    scene.Add(Sprite3);
    Sprite3->SetLocalPosition(glm::vec3(0, 40, 0));
    Sprite3->SetParent(Sprite2.get(), false);

    Sprite3->AddComponent<dae::RotateComponent>(Sprite3.get(), 2.f, 20.f);

    auto Sprite4 = std::make_shared<dae::GameObject>();
    Sprite4->AddComponent<dae::TextureComponent>(Sprite4.get(), "Sprite_2.png");
    scene.Add(Sprite4);
    Sprite4->SetLocalPosition(glm::vec3(0, 40, 0));
    Sprite4->SetParent(Sprite3.get(), false);

    Sprite4->AddComponent<dae::RotateComponent>(Sprite4.get(), -1.f, 20.f);
}

void CreateRotatingAnimatedObjects(dae::Scene& scene)
{
    auto parentSprite = std::make_shared<dae::GameObject>();
    parentSprite->AddComponent<dae::SpriteSheetComponent>(parentSprite.get(), "SpriteSheet_Player.png", 0.13f, 2, 15);
    parentSprite->SetLocalPosition(glm::vec3(400, 300, 0));
    scene.Add(parentSprite);

    auto parentSpriteSheet = parentSprite->GetComponent<dae::SpriteSheetComponent>();
    parentSpriteSheet->NewAnimation(4, 1, 0, 0.13f, true);

    auto childSprite = std::make_shared<dae::GameObject>();
    childSprite->AddComponent<dae::SpriteSheetComponent>(childSprite.get(), "SpriteSheet_Player.png", 0.13f, 2, 15);
    childSprite->SetLocalPosition(glm::vec3(0, 40, 0));
    childSprite->SetParent(parentSprite.get(), false);
    scene.Add(childSprite);

    auto childSpriteSheet = childSprite->GetComponent<dae::SpriteSheetComponent>();
    childSpriteSheet->NewAnimation(5, 11, 1, 0.13f, true);

    childSprite->AddComponent<dae::RotateComponent>(childSprite.get(), -2.f, 40.f);
}