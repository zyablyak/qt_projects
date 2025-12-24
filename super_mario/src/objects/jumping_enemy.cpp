#include "jumping_enemy.hpp"

using biv::JumpingEnemy;

JumpingEnemy::JumpingEnemy(const Coord& top_left, const int width, const int height)
	: Enemy(top_left, width, height) {
	hspeed = 0.0f;
	vspeed = 0.0f;

	jump_hspeed = 0.25f;
	jump_cooldown = 10;
}

float JumpingEnemy::predict_jump_dx() const noexcept {
	
	const float JUMP_SPEED = -1.0f;
	const float V_ACCELERATION = 0.05f;
	const float MAX_V_SPEED = 0.98f;

	float v = JUMP_SPEED;
	int ticks = 0;

	float y = 0.0f;
	const int MAX_TICKS = 200;

	while (ticks < MAX_TICKS) {
		if (v < MAX_V_SPEED) v += V_ACCELERATION;
		y += v;
		ticks++;

		if (ticks > 1 && y >= 0.0f) {
			break;
		}
	}

	return jump_hspeed * static_cast<float>(ticks);
}

bool JumpingEnemy::will_land_on_platform(Rect* platform, float dx) const noexcept {
	const float future_center_x = (top_left.x + dx) + width * 0.5f;

	const float eps = 0.01f;

	return future_center_x > platform->get_left() + eps
		&& future_center_x < platform->get_right() - eps;
}

void JumpingEnemy::process_vertical_static_collision(Rect* platform) noexcept {
	if (vspeed > 0) {
		top_left.y -= vspeed;
		vspeed = 0;
	}

	hspeed = 0.0f;

	if (jump_cooldown > 0) {
		--jump_cooldown;
		return;
	}

	const float dx = predict_jump_dx();

	if (!will_land_on_platform(platform, dx)) {
		jump_hspeed = -jump_hspeed;
		const float dx2 = predict_jump_dx();

		if (!will_land_on_platform(platform, dx2)) {
			jump_cooldown = JUMP_COOLDOWN_TICKS;
			return;
		}
	}

	hspeed = jump_hspeed;
	jump();

	jump_cooldown = JUMP_COOLDOWN_TICKS;
}