#include <ctime>

namespace Tools
{
    struct Time
    {
        float deltaTime;
        float gameTime;
    
        Time();
    
        void Update();
    
    private:
        float previousTime;
    };
    
    inline Time::Time()
                : deltaTime(0), gameTime(0)
    {}
    
    inline void Time::Update()
    {
        previousTime = gameTime;
        
        //CPU "ticks" since the program started.
        clock_t programTickCount = clock();
    
        //Conversion rate between ticks and millaseconds.
        float msMultiplyer = 1000.0f / CLOCKS_PER_SEC;
    
        //Convert from ticks to seconds.
        gameTime = (programTickCount * msMultiplyer) / 10.f;
    
    
        deltaTime = gameTime - previousTime;
    }
}
