#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
//#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
//using namespace geode::node_ids;

class $modify(MyPlayLayer, PlayLayer) {
    struct Fields {
        int theTimeUDed = 0;
        CCSprite* spongebob; // ts can be anything actaully
    };

    void delayedResetLevel() {
        PlayLayer::delayedResetLevel();
        auto maxDeath  = Mod::get()->getSettingValue<int>("max-death");
        m_fields->theTimeUDed++;
        float opacity = (int)(maxDeath <= 0 ? 255 : m_fields->theTimeUDed / maxDeath * 255);
        m_player1->setOpacity(255 - opacity);
        m_fields->spongebob->setOpacity(opacity);
    }

    bool init(GJGameLevel* level, bool dontCreateObjects) {
        if (!PlayLayer::init(level, dontCreateObjects)) {
            return false;
        }

        auto spongebobPath = Mod::get()->getSettingValue<asp::fs::Path>("custom-image");
        if (spongebobPath.empty()) spongebobPath = "sad_sponboob.png"_spr;
        
        m_fields->spongebob = CCSprite::create(spongebobPath.string().c_str());
        auto batchLayer = this->getChildByIndex(0)->getChildByIndex(2);
        batchLayer->addChild(m_fields->spongebob);

        return true;
    }

    void update(float dt) {
        PlayLayer::update(dt);

        m_fields->spongebob->setPosition(m_player1->getPosition());
        m_fields->spongebob->setRotation(m_player1->getRotation());
        m_fields->spongebob->setScale(m_player1->getScale());
    }
};