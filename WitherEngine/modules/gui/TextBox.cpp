#include "TextBox.h"

#include "../../engine/App.h"

we::TextBox::TextBox(App* app)
    : m_app(app)
{
    // Setup text
    m_text.setFont(ResourceManager::get().getFont());
    m_text.setFillColor(sf::Color::White);
    m_text.setOutlineColor(sf::Color::Black);
    m_text.setOutlineThickness(5.0f);
    m_text.setCharacterSize(64);
}

void we::TextBox::Draw(sf::RenderWindow & window)
{
    window.draw(m_text);
}

void we::TextBox::setString(std::string String)
{
    m_text.setString(String);
    centerText();
}

void we::TextBox::setCharachterSize(int size)
{
    m_text.setCharacterSize(size);
    centerText();
}

void we::TextBox::setFillColour(sf::Color c)
{
    m_text.setFillColor(c);
}

void we::TextBox::setOutlinecolour(sf::Color c)
{
    m_text.setOutlineColor(c);
}

void we::TextBox::setOutlineThickness(int thickness)
{
    m_text.setOutlineThickness(thickness);
}

void we::TextBox::setPosition(float x, float y)
{
    m_text.setPosition(x, y);
}

bool we::TextBox::MouseHover()
{
    if (m_text.getGlobalBounds().contains(sf::Mouse::getPosition(m_app->getWindow()).x, sf::Mouse::getPosition(m_app->getWindow()).y))
    {
        return true;
    }
    else return false;
}

sf::Text & we::TextBox::getText()
{
    return m_text;
}

void we::TextBox::centerText()
{
    sf::FloatRect textRect = m_text.getLocalBounds();
    m_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
}
