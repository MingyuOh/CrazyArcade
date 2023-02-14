#pragma once

// Login scene
static const wchar_t*	kIPAdreess				= L"192.168.0.45";

// Object
static const int	kObjectWidthSize			= 40;
static const int	kObjectHeightSize			= 40;
static const int    kObjectSailWidthPixelCount	= 3;
static const int    kObjectSailHeightPixelCount	= 1;

// Hero
static const float	kHeroBazziSpeed				= 150.0f;
static const float  kHeroAnimLifeTime			= 0.5f;
static const float  kHeroTrapLifeTime			= 7.0f;
static const float  kHeroTrapAnimLifeTime		= 3.5f;
static const float  kHeroDeadAnimLifeTime		= 1.5f;
static const int	kHeroMaxWaterBombCount		= 7;
static const int	kHeroMaxWaterPowerCount		= 7;
static const int	kHeroMaxSpeedCount			= 7;

// Sprite
static const int	kSpriteMaxNameLength		= 80;

// Map
static const int	kMapPixelCount				= 256;
static const int	kMapTotalTileCount			= 195;
static const int	kQuadTreeSize				= 4;
static const LONG	kMapMinWidthSize			= 20;
static const LONG	kMapMinHeightSize			= 40;
static const LONG	kMapMaxWidthSize			= 660;
static const LONG	kMapMaxHeightSize			= 680;
static const int	kQuadtreeMaxDepthLimit		= 4;
static const LONG	kQuadtreeMinDivideSize		= 0;
static const int	kMapStartPosX				= 20;
static const int	kMapStartPosY				= 40;
static const int	kMapMaxRowLength			= 16;
static const int	kMapMaxColumnLength			= 16;
static const int	kMapRealRowLength			= 13;
static const int	kMapRealColumnLength		= 15;
static const int	kMapBreakableTileCount		= 138;

// Item
static const int	kItemTotalCount				= 45;
static const int	kItemMaxWaterBalloonCount	= 14;
static const int	kItemMaxWaterPowerCount		= 14;
static const int	kItemMaxSkateCount			= 14;
static const int	kItemMaxWaterMaxPowerCount	= 3;