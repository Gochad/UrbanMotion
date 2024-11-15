#pragma once
#include <unordered_map>
#include "../texture/Manager.h"
#include "../components/Fields.h"

extern std::unordered_map<char, std::function<std::shared_ptr<Field>()>> FromFileToFields;