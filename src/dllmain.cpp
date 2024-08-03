#include "dllmain.hpp"
#include <minecraft/src/common/world/level/dimension/HeightRange.hpp>

SafetyHookInline _dimensionDimension;

void* dimensionDimension(void* self, void* a2, int dimensionID, HeightRange HeightRange, void* a5, std::string& dimName)
{
	// Set max height to 2048 blocks
	HeightRange.mMaxHeight = 2048;
	return _dimensionDimension.fastcall<void*>(self, a2, dimensionID, HeightRange, a5, dimName);
}

// Ran when the mod is loaded into the game by AmethystRuntime
ModFunction void Initialize(AmethystContext& ctx)
{
	// Initialize Amethyst mod backend
	Amethyst::InitializeAmethystMod(ctx);

	// Hook dim ctor
	Amethyst::GetHookManager().RegisterFunction<&dimensionDimension>("48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 55 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 41 8B F9 41 8B D8");
	Amethyst::GetHookManager().CreateHook<&dimensionDimension>(_dimensionDimension, &dimensionDimension);
}
