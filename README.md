# Assault Cube Trainer
Works for v1.2.0.2

Includes:

1) Max Stats + Invincibility
2) Infinite Ammo
3) No Recoil
4) 2x Player Speed (BUGGY)
5) Super Jump
6) No Clip/Ghost Mode
7) Set Coorinates (BUGGY)
8) Teleport to Coordinates
9) 1 Shot Kills (Coming Soon)

Will add a command line interface after all functionality has been implemented.

This is my first attempt at developing a basic trainer. I chose assault cube because it's an old game that is relatively easy to reverse engineer.

*KNOWN BUGS*
- With 2x Player Speed toggled on AND 2 keys pressed at once, the main loop stops iterating and therefore continous writes stop writing.
    - Need to clean up loop structure.
- With 2x Player Speed toggled on, movement will sometimes "stick" and require an addition keystroke to stop the player.
- After setting coordinates for teleport, player is unable to toggle additional features until the coordinates are cleared.
    - Need to clean up loop structure.
