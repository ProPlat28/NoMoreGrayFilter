#include <Geode/Geode.hpp>
#include <Geode/modify/CreatorLayer.hpp>
#include <Geode/binding/CCMenuItemSpriteExtra.hpp>
#include <Geode/modify/LevelBrowserLayer.hpp>
#include <Geode/binding/GJSearchObject.hpp>
#include <Geode/binding/LevelBrowserLayer.hpp>

using namespace geode::prelude;

class $modify(CreatorLayer) {
    void onMapPacks(CCObject*) {
        auto search = GJSearchObject::create(SearchType::HallOfFame);
        CCDirector::get()->pushScene(CCTransitionFade::create(0.5f, LevelBrowserLayer::scene(search)));
    }
};

class $modify(LevelBrowserLayer) {
    bool init(GJSearchObject* search) {
        if (!LevelBrowserLayer::init(search)) return false;
        if (search && search->m_searchType == SearchType::HallOfFame) {
            if (auto label = this->getChildByType<CCLabelBMFont>(0)) label->setVisible(false);
            auto title = CCSprite::create("HallTitle.png");
            if (title) {
                auto winSize = CCDirector::get()->getWinSize();
                title->setPosition({winSize.width / 2.f, winSize.height - 25.f});
                this->addChild(title, 10);
            }
        }
        return true;
    }
};

	bool init() {

		if (!CreatorLayer::init()) {
			return false;
		};

		auto menu = this->getChildByID("creator-buttons-menu");

		auto sprmappacks = CCSprite::create("featured.png"_spr);

		std::map<std::string, CCSprite*> idsToBtns = {
			{ "map-packs-button", sprmappacks }
		};
		
		for (auto pair = idsToBtns.begin(); pair != idsToBtns.end(); pair++) {
			auto id = pair->first.c_str();
			auto superExpertLoaded = ((strcmp("map-packs-button", id) == 0) && (Loader::get()->isModLoaded("xanii.super_expert")));

			if (!menu->getChildByID(id)) continue;
			if (!pair->second) continue;

			auto btn = typeinfo_cast<CCMenuItemSpriteExtra*>(menu->getChildByID(id));
			auto contentSize = btn->getContentSize();
			auto existingSprite = btn->getChildByType<CCSprite*>(0);

			if (!existingSprite) continue;

			auto scale = existingSprite->getScale();
			pair->second->setScale(scale);

			if (!superExpertLoaded) {
				btn->setNormalImage(pair->second);
			};

			btn->setContentSize(contentSize);

		};

		return true;
	};
};
