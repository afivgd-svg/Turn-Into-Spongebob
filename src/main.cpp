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
        m_fields->theTimeUDed += 1; // idk++
        auto opacity = maxDeath <= 0
            ? 255
            : std::clamp(m_fields->theTimeUDed * 255 / maxDeath, 0, 255);

        m_fields->spongebob->setOpacity(static_cast<GLubyte>(opacity));
    }

    bool init(GJGameLevel* level, bool dontCreateObjects) {
        if (!PlayLayer::init(level, dontCreateObjects)) {
            return false;
        }

        auto spongebobPath = Mod::get()->getSettingValue<asp::fs::Path>("custom-image");
        if (spongebobPath.empty()) spongebobPath = "sad_sponboob.png"_spr;
        
        auto spongebob = m_fields->spongebob;
        spongebob = CCSprite::create(spongebobPath.string().c_str());
        if (!spongebob) {
            spongebob = CCSprite::create("sad_sponboob.png"_spr);
        }
        spongebob->setScaleY(spongebob->getContentSize().height / 30);
        spongebob->setOpacity(255);
        //auto batchLayer = this->getChildByIndex(0)->getChildByIndex(2);
        m_player1->addChild(spongebob);

        return true;
    }
};