#pragma once

#include <libtcod.hpp>
#include <memory>
#include <vector>

class Actor; typedef std::shared_ptr<Actor> ActorPtr;

class TargetSelector
{
public:
	enum SelectorType {
        CLOSEST_MONSTER,
        SELECTED_MONSTER,
        WEARER_RANGE,
        SELECTED_RANGE      
    };

	TargetSelector(SelectorType type, float range);
	~TargetSelector();

	std::vector<ActorPtr> selectTargets(const ActorPtr &wearer);

private:
	SelectorType type;
    float range;
};

typedef std::shared_ptr<TargetSelector> TargetSelectorPtr;