/*
//////////////////////////////////////
     Mihael Petričević 26.5.2020.
    Contact: miha53cevic@gmail.com
//////////////////////////////////////

#include "simpleSDL.h"

class demo : public ssdl::simpleSDL
{
public:
    demo() {}

private:
    virtual void Event(const SDL_Event &e)
    {}

    virtual bool Setup()
    {
        return true;
    }

    virtual bool Loop(float elapsed)
    {
        Clear();
        drawRect(ScreenWidth() / 2 - 100, ScreenHeight() / 2 - 100, 200, 200);
        return true;
    }
};

int main(int argc, char* argv[])
{
    demo app;
    app.Construct("Demo app", 1280, 720);
    app.Start();
    return 0;
}

*/

#pragma once

#ifdef _WIN32
    #include <SDL.h>
#endif
#ifdef __linux__
    #include <SDL2/SDL.h>
#endif

#include <iostream>
#include <string>
#include <cstdint>
#include <vector>
#include <random>

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t   i8;
typedef int16_t  i16;
typedef int32_t  i32;
typedef int64_t  i64;

namespace ssdl
{
    /*-----------------------------------------------------------------------------*/

    // Random number generator in given range
    float fRandom(float first, float second)
    {
        std::random_device rd;
        std::default_random_engine generator(rd()); // rd() provides a random seed
        std::uniform_real_distribution<float> distribution(first, second);

        return distribution(generator);
    }

    int iRandom(int first, int second)
    {
        std::random_device rd;
        std::default_random_engine generator(rd()); // rd() provides a random seed
        std::uniform_int_distribution<int> distribution(first, second);

        return distribution(generator);
    }

    // PI CONSTANT
    const float PI = 3.141592f;

    // Converts degress to radians
    float toRadian(float deg)
    {
        return deg * (PI / 180);
    }

    // Maps values from one range to another
    float map(float s, float a1, float a2, float b1, float b2)
    {
        return b1 + ((s - a1) * (b2 - b1)) / (a2 - a1);
    }

    /*-----------------------------------------------------------------------------*/

    template<class T>
    struct vec2
    {
        vec2()
            : x(0)
            , y(0)
        {}

        vec2(T x, T y)
        {
            this->x = x;
            this->y = y;
        }

        float magnitude()
        {
            return sqrtf(x*x + y*y);
        }

        vec2<T> unitVector()
        {
            float c = magnitude();
            return { x / c, y / c };
        }

        T x, y;
    };

    typedef vec2<int>           ivec2;
    typedef vec2<unsigned int>  uvec2;
    typedef vec2<float> 		fvec2;
    typedef vec2<double> 		dvec2;

    /*-----------------------------------------------------------------------------*/

    class simpleSDL
    {
    public:
        simpleSDL()
        {
            if (SDL_Init(SDL_INIT_VIDEO) != 0)
            {
                SDLError("Initialize error: ");
                SDL_Quit();
            }

            m_window   = nullptr;
            m_renderer = nullptr;
            m_bAlive   = false;

            m_keystates = SDL_GetKeyboardState(nullptr);
        }
        virtual ~simpleSDL()
        {
            SDL_DestroyWindow(m_window);
            SDL_DestroyRenderer(m_renderer);
            SDL_Quit();
        }

        void Construct(std::string title, unsigned int w, unsigned int h)
        {
            m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);
            if (m_window == nullptr)
            {
                SDLError("Window creation error: ");
                SDL_DestroyWindow(m_window);
                SDL_Quit();
            }

            m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (m_renderer == nullptr)
            {
                SDLError("Renderer creation error: ");
                SDL_DestroyWindow(m_window);
                SDL_DestroyRenderer(m_renderer);
                SDL_Quit();
            }

            m_title = title;
            m_windowSize = uvec2(w, h);
            m_bAlive = true;
        }

    protected:
        virtual void Event(const SDL_Event& e) {}
        virtual bool Setup() = 0;
        virtual bool Loop (float elapsed) = 0;

    private:
        SDL_Window*   m_window;
        SDL_Renderer* m_renderer;

        std::string   m_title;
        uvec2 	      m_windowSize;

        bool 		  m_bAlive;

        int			  m_NOW;
        int		      m_LAST;
        float		  m_deltaTime;

        const u8* 	  m_keystates;

        void SDLError(std::string text) { std::cout << text << SDL_GetError() << std::endl; }

    protected:
        int ScreenWidth () { return m_windowSize.x; }
        int ScreenHeight() { return m_windowSize.y; }

        SDL_Renderer* getRenderer() { return m_renderer; }
        SDL_Window*   getWindow() 	{ return m_window; 	 }

        ivec2 getMousePos()
        {
            int x, y;
            SDL_GetMouseState(&x, &y);
            return { x, y };
        }

        //	Param Key must be a SDL_SCANCODE_%
        bool getKeystate(u8 key = SDL_SCANCODE_RETURN)
        {
            if (m_keystates[key])
                return true;
            else return false;
        }

        // Texture operations
        SDL_Texture* createTexture(u32 format, int access, int w, int h)
        {
            return SDL_CreateTexture(m_renderer, format, access, w, h); 
        }
        void destroyTexture	(SDL_Texture* texture) { SDL_DestroyTexture(texture); }

        void renderTexture(SDL_Texture* texture, SDL_Rect* srcRect = nullptr, SDL_Rect* dsRect = nullptr)
        {
            SDL_RenderCopy(m_renderer, texture, srcRect, dsRect);
        }

        bool rectContains(ivec2 leftUpperCorner, ivec2 size, ivec2 point)
        {
            ivec2 rightDownCorner = { leftUpperCorner.x + size.x, leftUpperCorner.y + size.y };
            if (point.x <= rightDownCorner.x && 
                point.x >= leftUpperCorner.x &&
                point.y <= rightDownCorner.y &&
                point.y >= leftUpperCorner.y
            ) return true;

            return false;
        }

        void Clear(int r = 0, int g = 0, int b = 0, int a = 255)
        {
            SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
            SDL_RenderClear(m_renderer);
        }

        // Draw routines
        void drawFillRect(int x, int y, int w, int h, SDL_Color c = { 255, 255, 255, 255 })
        {
            SDL_Rect rect = { x, y, w, h };
            SDL_SetRenderDrawColor(m_renderer, c.r, c.g, c.b, c.a);
            SDL_RenderFillRect(m_renderer, &rect);
        }

        void drawRect(int x, int y, int w, int h, SDL_Color c = { 255, 255, 255, 255 })
        {
            SDL_Rect rect = { x, y, w, h };
            SDL_SetRenderDrawColor(m_renderer, c.r, c.g, c.b, c.a);
            SDL_RenderDrawRect(m_renderer, &rect);
        }

        void drawLine(int x1, int y1, int x2, int y2, SDL_Color c = { 255, 255, 255, 255 })
        {
            SDL_SetRenderDrawColor(m_renderer, c.r, c.g, c.b, c.a);
            SDL_RenderDrawLine(m_renderer, x1, y1, x2, y2);
        }

        void drawPoint(int x, int y, SDL_Color c = { 255, 255, 255, 255 })
        {
            SDL_SetRenderDrawColor(m_renderer, c.r, c.g, c.b, c.a);
            SDL_RenderDrawPoint(m_renderer, x, y);
        }

    public:
        void Start()
        {
            if (m_window == nullptr && m_renderer == nullptr)
            {
                std::cout << "Start error: Construct() was never called!" << std::endl;
                return;
            }

            if (!Setup())
                m_bAlive = false;

            m_NOW = SDL_GetPerformanceCounter();
            m_LAST = 0;
            m_deltaTime = 0.0f;
            while (m_bAlive)
            {
                m_LAST = m_NOW;
                m_NOW = SDL_GetPerformanceCounter();
                m_deltaTime = (float)((m_NOW - m_LAST) / (float)SDL_GetPerformanceFrequency());

                SDL_Event e;
                while (SDL_PollEvent(&e))
                {
                    if (e.type == SDL_QUIT)
                        m_bAlive = false;

                    Event(e);
                }

                if (!Loop(m_deltaTime))
                    m_bAlive = false;

                SDL_RenderPresent(m_renderer);
            }
        }
    };

    /*-----------------------------------------------------------------------------*/

    namespace matrix
    {
        template<typename T>
        class mat
        {
        public:
            mat(int rows, int cols)
            {
                m_rows = rows;
                m_cols = cols;
                m_data.resize(rows * cols);

                identity();
            }

            void dump()
            {
                for (int i = 0; i < m_rows; i++)
                {
                    std::cout << "[";
                    for (int j = 0; j < m_cols; j++)
                    {
                        std::cout << m_data[index(j, i)];
                        if (j != m_cols - 1) std::cout << " ";
                    }
                    std::cout << "]\n";
                }
                std::cout << "\n";
            }

            void identity()
            {
                for (int i = 0; i < m_rows; i++)
                {
                    for (int j = 0; j < m_cols; j++)
                    {
                        if (i == j) m_data[index(j, i)] = 1;
                        else        m_data[index(j, i)] = 0;
                    }
                }
            }

            void set(std::vector<T> array)  { m_data = std::move(array);   }
            void set(int x, int y, T value) { m_data[index(x, y)] = value; }
            T    get(int x, int y)          { return m_data[index(x, y)];  }

            void mult(T scalar)
            {
                for (int i = 0; i < m_rows; i++)
                {
                    for (int j = 0; j < m_cols; j++)
                    {
                        m_data[index(j, i)] *= scalar;
                    }
                }
            }

            mat<T> mult(mat<T> rb)
            {
                if (m_cols != rb.m_rows)
                    std::cout << "Columns of the 1st matrix must equal the number of rows of the 2nd matrix!\n";
                else
                {
                    // the result will have the same number of rows as the 1st matrix,
                    // and the same number of columns as the 2nd matrix.
                    mat<T> result(m_rows, rb.m_cols);
                    
                    // Korišten algoritam od coding train-a za množenje matrica
                    // https://github.com/CodingTrain/website/blob/master/CodingChallenges/CC_112_3D_Rendering/Processing/CC_112_3D_Rendering/matrix.pde
                    // Remember that 2DArray[y][x] dok je index(x, y)
                    for (int i = 0; i < m_rows; i++)
                    {
                        for (int j = 0; j < rb.m_cols; j++)
                        {
                            T sum = 0;
                            for (int k = 0; k < m_cols; k++)
                            {
                                sum += get(k, i) * rb.get(j, k);
                            }
                            result.set(j, i, sum);
                        }
                    }

                    return result;
                }
                // If error return identity matrix
                return mat<T>(m_rows, rb.m_cols);
            }

            mat<T> operator*(const mat<T>& rb) { return mult(rb);    }
            void operator=  (const mat<T>& rb) { m_data = rb.m_data; }

        private:
            int m_rows;
            int m_cols;
            std::vector<T> m_data;

        private:
            int index(int x, int y) { return (m_cols * y) + x;     }
        };

        typedef mat<int>    imat;
        typedef mat<float>  fmat;
        typedef mat<double> dmat;

    };

    /*-----------------------------------------------------------------------------*/
};