﻿#pragma once

// 当たり判定属性
const unsigned short COLLISION_ATTR_GROUND = 0b1 << 0; // 地面
const unsigned short COLLISION_ATTR_LANDSHAPE = 0b1 << 1; // 地形
const unsigned short COLLISION_ATTR_ALLIES = 0b1 << 1; // 味方陣営
const unsigned short COLLISION_ATTR_ENEMYS= 0b1 << 2; // 敵陣営