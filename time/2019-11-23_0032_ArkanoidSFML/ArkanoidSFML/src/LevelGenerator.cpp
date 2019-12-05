#include "LevelGenerator.h"
#include "IDestructible.h"
#include "IBonusOwner.h"
#include "HelperFunctions.h"

std::vector<Level> LevelGenerator::getSymbolLevels()
{
    std::vector<Level> levels
    {
        {
            "................",
            "0000000000000000",
            "MMMMMMMMMMMMMMMM",
            "................",
            "................",
            "................",
            "................",
            "................",
            "................",
            "................",
            "................",
        },
        {
            "................",
            ".MMMMMMMMMMMMMM.",
            ".MMMMMMMMMMMMMM.",
            ".MMMMMMMMMMMMMM.",
            ".MMMMMMMMMMMMMM.",
            ".MMMMMMMMMMMMMM.",
            ".MMMMMMMMMMMMMM.",
        },
        {
            "................",
            ".11111111111111.",
            ".11111111111111.",
            ".111111MM111111.",
            ".11111111111111.",
            ".11MM111111MM11.",
            ".11111111111111.",
        },
        {
            "................",
            "...31M1111M13...",
            "...3111111113...",
            "...3111111113...",
            "...3111111113...",
            "...311M11M113...",
            "...3111111113...",
            "...3111111113...",
            "...3111111113...",
            "...3111111113...",
            "...3111111113...",
        },
        {
            "........MM........",
            ".0002000000002000.",
            ".0111111111111110.",
            ".0111111111111110.",
            ".0111111111111110.",
            ".0111111111111110.",
            ".0111111111111110.",
            ".0000000000000000.",
        },
    };

    return levels;
}

LevelGenerator::LevelGenerator(std::shared_ptr<IObjectFactory> objectFactory, sf::Vector2f worldSize)
{
    m_objectFactory = objectFactory;
    m_worldSize = worldSize;
    m_brickZoneSize = {m_worldSize.x * 0.8f, m_worldSize.y * 0.6f};
    m_brickZoneLeftTopPos = {m_worldSize.x * 0.1f, m_worldSize.y * 0.1f};
    m_brickGap = 8;
    m_currentLevelNumber = 0;
    m_levels = getSymbolLevels();
}

void LevelGenerator::changeLevel()
{
    m_currentLevelNumber++;
}

std::vector<std::shared_ptr<IObject>> LevelGenerator::getLevelBricks()
{
    auto levelNumber = m_currentLevelNumber % m_levels.size();
    auto currentLevel = m_levels.at(levelNumber);
    sf::Vector2i resolutionInBricks;
    resolutionInBricks.x = currentLevel.front().size();
    resolutionInBricks.y = currentLevel.size();
    std::vector<std::shared_ptr<IObject>> bricks;
    sf::Vector2f brickSize = {
        m_brickZoneSize.x / resolutionInBricks.x,
        m_brickZoneSize.y / resolutionInBricks.y
    };
    for (auto brickCol = 0; brickCol < resolutionInBricks.x; ++brickCol)
    {
        for (auto brickRow = 0; brickRow < resolutionInBricks.y; ++brickRow)
        {
            char symbol = currentLevel[brickRow][brickCol];
            if (symbol == '.')
                continue;
            auto obj = m_objectFactory->createObject(ObjectType::Brick);
            sf::Vector2f brickPos = {
                brickSize.x / 2 + brickCol * brickSize.x + m_brickZoneLeftTopPos.x,
                brickSize.y / 2 + brickRow * brickSize.y + m_brickZoneLeftTopPos.y
            };
            obj->state().setPos(brickPos);
            obj->state().setSize({brickSize.x - m_brickGap, brickSize.y - m_brickGap});
            auto brick = std::dynamic_pointer_cast<IDestructible>(obj);
            auto bonus = std::dynamic_pointer_cast<IBonusOwner>(obj);
            if (std::isdigit(symbol))
            {
                int number = hf::charToInt(symbol);
                if (number == 0)
                    brick->lives() = {};
                else
                    brick->lives() = number;
                brick->setAppearance(number + 1);
                bonus->setBonusType({});
            }
            else
            {
                brick->lives() = 1;
                auto bonusType = getBonusTypeFromChar(symbol);
                brick->setAppearance(0);
                bonus->setBonusType(bonusType);
            }
            bricks.push_back(obj);
        }
    }

    return bricks;
}
