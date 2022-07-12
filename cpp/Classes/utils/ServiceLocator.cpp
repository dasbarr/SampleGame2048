#include "ServiceLocator.h"

cocos2d::Map<std::type_index, cocos2d::Ref*> sample_game::utils::ServiceLocator::s_services;

void sample_game::utils::ServiceLocator::clear() {
    s_services.clear();
}
