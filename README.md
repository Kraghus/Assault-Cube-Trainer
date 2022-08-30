# Assault Cube Trainer
Works for v1.2.0.2

Includes toggles for:

[NUMPAD 1] Max Stats + Invincibility

[NUMPAD 2] Infinite Ammo

[NUMPAD 3] No Recoil

[NUMPAD 4] 2x Player Speed (BUGGY)

[NUMPAD 5] Super Jump

[NUMPAD 6] No Clip/Ghost Mode

[NUMPAD 7] Set Coorinates (BUGGY)

[NUMPAD 8] Teleport to Coordinates

[NUMPAD 9] 1 Shot Kills (Coming Soon)

[INSERT]   Triggerbot

Press [END] to exit the trainer.

Will add a command line interface after all functionality has been implemented.

This is my first attempt at developing a basic trainer. I chose assault cube because it's an old game that is relatively easy to reverse engineer.

*KNOWN BUGS*
- With 2x Player Speed toggled on AND 2 keys pressed at once, the main loop stops iterating and therefore continous writes stop writing.
    - Need to clean up loop structure.
- With 2x Player Speed toggled on, movement will sometimes "stick" and require an addition keystroke to stop the player.
- After setting coordinates for teleport, player is unable to toggle additional features until the coordinates are cleared.
    - Need to clean up loop structure.
