/*
Author: Mihael Petricevic
Contact: miha53cevic@gmail.com

Description:
        Simple SFML wrapper for easier usage

------------------------------
|      Example usage:        |
------------------------------
#include "simpleSFML.h"

class demo : public ssf::simpleSFML
{
public:
	demo() {}

private:

protected:
    void Event(sf::Event e) override
    {
    }

protected:
	bool OnUserCreate() override
	{
		return true;
	}

	bool OnUserUpdate(sf::Time elapsed) override
	{
		ClearDraw(sf::Color::Black);
		return true;
	}

};

int main()
{
	demo app;
	app.Construct(1280, 720, L"demo app");
	app.Start();

	return 0;
}
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <random>

namespace ssf 
{
	
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

	class simpleSFML
	{
	public:
		simpleSFML()
		{
			m_sAppName = L"Default";
			m_nScreenWidth = 640;
			m_nScreenHeight = 480;

			m_bVSync    = false;
			m_bDone     = false;
			m_bDrawFPS  = false;
		}
		~simpleSFML() { m_window.close(); }

		//Must override these
		virtual bool OnUserCreate() = 0;
		virtual bool OnUserUpdate(sf::Time elapsed) = 0;

		//Can override this
		virtual void Event(sf::Event e) {}

		int ScreenWidth() { return m_nScreenWidth; }
		int ScreenHeight() { return m_nScreenHeight; }

		void EnableVSync(bool l_vsync) { m_bVSync = l_vsync; m_window.setVerticalSyncEnabled(m_bVSync); }
		bool IsVSyncOn() { return m_bVSync; }

		void EnableFPSCounter(bool l_fps) { m_bDrawFPS = l_fps; }

		sf::RenderWindow* getWindow() { return &m_window; }

		void Draw(sf::Drawable& l_drawable) { m_window.draw(l_drawable); }
		void Draw(sf::Drawable& l_drawable, sf::Transform& l_transform) { m_window.draw(l_drawable, l_transform); }
		void Draw(sf::VertexArray l_vertexArray) { m_window.draw(l_vertexArray); }

		void ClearDraw(sf::Color l_color) { m_window.clear(l_color); }

	private:
		sf::RenderWindow m_window;

		int m_nScreenWidth;
		int m_nScreenHeight;

		std::wstring m_sAppName;

		bool m_bVSync;
		bool m_bDone;
		bool m_bDrawFPS;

		sf::Clock m_clock;
		sf::Time m_elapsed;

		void DisplayDraw() { m_window.display(); }

	public:
		void Construct(int l_nScreenWidth, int l_nScreenHeight, std::wstring l_title)
		{
			m_nScreenWidth = l_nScreenWidth;
			m_nScreenHeight = l_nScreenHeight;

			m_sAppName = l_title;
		}

		void Start()
		{
			m_window.create(sf::VideoMode(m_nScreenWidth, m_nScreenHeight), m_sAppName);

			if (!OnUserCreate())
				m_bDone = true;

			//Main Game Loop
			while (!m_bDone)
			{
				sf::Event event;

				while (m_window.pollEvent(event))
				{
					if (event.type == sf::Event::Closed)
						m_bDone = true;

					Event(event);
				}

				if (!OnUserUpdate(m_elapsed))
					m_bDone = true;

				DisplayDraw();

				m_elapsed = m_clock.restart();

				if (m_bDrawFPS)
					m_window.setTitle(m_sAppName + L" - FPS: " + std::to_wstring(1.0f / m_elapsed.asSeconds()));
			}
		}
	};
};

/*//////////////////////////////
	Matrix Library Module
*///////////////////////////////


#include <iostream>
#include <vector>

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

