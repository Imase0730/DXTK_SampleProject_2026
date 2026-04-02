#pragma once

#include "../ImaseLib/Task.h"

class Player : public Imase::Task
{
public:
	Player();

	~Player();

	bool Update(float elapsedTime) override;

	void Render() override;

};