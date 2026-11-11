#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
//#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
//using namespace geode::node_ids;

class $modify(MyPlayLayer, PlayLayer) {
    struct Fields {
        int theTimeUDed = 0;
    };

    void delayedResetLevel() {
        PlayLayer::delayedResetLevel();
        auto maxDeath  = Mod::get()->getSettingValue<int>("max-death");
        m_fields->theTimeUDed += 1; // idk++
        auto opacity = maxDeath <= 0
            ? 255
            : std::clamp(m_fields->theTimeUDed * 255 / maxDeath, 0, 255);
        //if (m_fields->spongebob) m_fields->spongebob->setOpacity(static_cast<GLubyte>(opacity));

        auto spongebobPath = Mod::get()->getSettingValue<asp::fs::Path>("custom-image");
        if (spongebobPath.empty()) spongebobPath = "sad_sponboob.png"_spr;
        
        CCSprite* spongebob = CCSprite::create(spongebobPath.string().c_str());
        if (!spongebob) {
            spongebob = CCSprite::create("sad_sponboob.png"_spr);
        }
        spongebob->setScaleY(spongebob->getContentSize().height / 30);
        spongebob->setOpacity(opacity);
        m_player1->addChild(spongebob);
    }
};