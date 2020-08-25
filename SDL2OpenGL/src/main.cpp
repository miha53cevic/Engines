#include "app.h"

class Evade : public App
{
public:
    Evade(const char* title, int width, int height)
        : App(title, width, height)
    {}

private:
    virtual bool Event(SDL_Event& e) override
    {

        return true;
    }
    virtual bool Setup() override
    {

        return true;
    }
    virtual bool Loop(float elapsed) override
    {

        return true;
    }

private:
};

int main(int argc, char* argv[])
{
    Evade game("Evade", 1280, 720);
    game.Run();
    return 0;
}