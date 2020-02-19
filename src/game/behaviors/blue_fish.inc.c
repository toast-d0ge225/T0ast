/**
 * @file blue_fish.inc.c
 * Implements behaviour and spawning for blue_fish located in the aquarium outside of SA.
 *
 */

/**
 * 
 * 
 * 
 */
void bhv_blue_fish_loop(void) {
    f32 sp24;
    switch (o->oAction) {
        case 0:
            func_8029ED98(0, 1.0f);
            
            // If oTimer then assign random values to floats and rotate fish.
            if (o->oTimer == 0) {
                o->oBlueFishRandomAngle = RandomSign() << 11;
                o->oBlueFishRandomVel = RandomFloat() * 2;
                o->oBlueFishRandomTime = (s32)(RandomFloat() * 30) & 0xFE;
                sp24 = RandomFloat() * 5;
                if (sp24 < 2.0f) {
                    o->oAngleVelPitch = random_f32_around_zero(128);
                } else {
                    o->oAngleVelPitch = 0;
                }
            }
            // Set forward velocity
            o->oForwardVel = o->oBlueFishRandomVel + 3.0f;
            if (o->oTimer >= o->oBlueFishRandomTime + 60) {
                o->oAction++;
            }
            if (o->oTimer < (o->oBlueFishRandomTime + 60) / 2) {
                o->oFaceAnglePitch += o->oAngleVelPitch;
            } else {
                o->oFaceAnglePitch -= o->oAngleVelPitch;
            }
            o->oVelY = -sins(o->oFaceAnglePitch) * o->oForwardVel;
            break;
        case 1:
            func_8029ED98(0, 2.0f);
            o->oMoveAngleYaw = (s32)(o->oBlueFishRandomAngle + o->oMoveAngleYaw);
            if (o->oTimer == 15) {
                o->oAction++;
            }
            break;
        case 2:
            func_8029ED98(0, 1.0f);
            if (o->oTimer >= o->oBlueFishRandomTime + 60) {
                o->oAction++;
            }
            if (o->oTimer < (o->oBlueFishRandomTime + 60) / 2) {
                o->oFaceAnglePitch -= o->oAngleVelPitch;
            } else {
                o->oFaceAnglePitch += o->oAngleVelPitch;
            }
            break;
        case 3:
            func_8029ED98(0, 2.0f);
            o->oMoveAngleYaw = (s32)(o->oBlueFishRandomAngle + o->oMoveAngleYaw);
            if (o->oTimer == 15) {
                o->oAction = 0;
            }
            break;
    }
    o->oVelY = -sins(o->oFaceAnglePitch) * o->oForwardVel;
    obj_move_using_fvel_and_gravity();
    if (o->parentObj->oAction == 2) {
        mark_object_for_deletion(o);
    }
}

/*
 * Spawns fish 
 *
 */
void bhv_tank_fish_group_loop(void) {
    struct Object *fish;
    s32 i;
    switch (o->oAction) {
        case 0:
            if (gMarioCurrentRoom == 15 || gMarioCurrentRoom == 7) {
                for (i = 0; i < 15; i++) {
                    fish = spawn_object_relative(0, 300, 0, -200, o, MODEL_FISH, bhvBlueFish);
                    translate_object_xyz_random(fish, 200.0f);
                }
                o->oAction++;
            }
            break;
        case 1:
            if (gMarioCurrentRoom != 15 && gMarioCurrentRoom != 7) {
                o->oAction++;
            }
            break;
        case 2:
            o->oAction = 0;
            break;
    }
}
