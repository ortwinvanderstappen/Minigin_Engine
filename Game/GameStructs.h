#pragma once

enum class EntityType
{
	qbert,
	coily,
	slickOrSam,
	sam,
	slick,
	ugg,
	wrongway
};

struct EntityProperty
{
	EntityType entityType;
	float movespeed;
	float minSpawnTime;
	float maxSpawnTime;
	float aiWaitTime;
};
