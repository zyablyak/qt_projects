#pragma once

#include "collisionable.hpp"
#include "movable.hpp"
#include "rect.hpp"
#include "rect_map_movable_adapter.hpp"
#include "speed.hpp"

namespace biv {
	
	class FlyingEnemy : public RectMapMovableAdapter, public Movable, public Collisionable {
		private:
			static constexpr float DEFAULT_FLY_RANGE = 10.0f;      
			static constexpr float DEFAULT_VERTICAL_SPEED = 0.15f;  
			
			float initial_y;           
			float fly_range = DEFAULT_FLY_RANGE;
			float vertical_speed = DEFAULT_VERTICAL_SPEED;
			
		public:
			FlyingEnemy(const Coord& top_left, const int width, const int height);

			Rect get_rect() const noexcept override;
			Speed get_speed() const noexcept override;

			void process_horizontal_static_collision(Rect*) noexcept override;
			void process_mario_collision(Collisionable*) noexcept override;
			void process_vertical_static_collision(Rect*) noexcept override;
			
			void move_vertically() noexcept override;
	};
}