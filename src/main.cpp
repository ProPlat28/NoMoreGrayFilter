#include <Geode/Geode.hpp>
#include <Geode/modify/CreatorLayer.hpp>
#include <Geode/binding/CCMenuItemSpriteExtra.hpp>

using namespace geode::prelude;

class $modify(CreatorLayer) {

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
